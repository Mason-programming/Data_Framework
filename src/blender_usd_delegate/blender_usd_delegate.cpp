// Created by Mason Kirby on 6/17/25.

#include "blender_usd_delegate.h"

blender_usd_delegate::blender_usd_delegate(std::string& user)
        : userSession(user), usdFile("False") {
    pthread_mutex_init(&mutex, nullptr);
}

blender_usd_delegate::blender_usd_delegate(std::string& userSession, std::string& file)
        : userSession(userSession), usdFile(std::move(file)) {
    pthread_mutex_init(&mutex, nullptr);
}

blender_usd_delegate::~blender_usd_delegate() {
    pthread_mutex_destroy(&mutex);
}

bool blender_usd_delegate::saveFile() {
    if (currentDirectory.empty()) {
        pthread_mutex_lock(&mutex);
        currentDirectory = saveAs("./saves", userSession);
        pthread_mutex_unlock(&mutex);

        _createFile(currentDirectory);
    }

    if (stage) {
        stage->Save();
        fileSaved = true;
        writeCache();
        return true;
    }

    return false;
}

UsdStageRefPtr blender_usd_delegate::_createFile(std::string directory) {
    if (!stage) {
        std::cerr << "No active stage to create overrides on." << std::endl;
        return nullptr;
    }

    std::string overlay_path = directory + "/index.usda";
    SdfLayerRefPtr overlayLayer = SdfLayer::CreateNew(overlay_path);

    if (!overlayLayer) {
        std::cerr << "Failed to create overlay layer." << std::endl;
        return nullptr;
    }

    UsdStageRefPtr overlayStage = UsdStage::Open(stage->GetRootLayer()->GetIdentifier());
    overlayStage->SetEditTarget(overlayLayer);

    SdfPath cubePath("/World/Cube");
    UsdGeomXform xform(overlayStage->GetPrimAtPath(cubePath));
    if (xform) {
        GfMatrix4d newTransform;
        newTransform.SetTranslate(GfVec3d(1.0, 2.0, 3.0));
        xform.MakeMatrixXform().Set(newTransform);
    }

    overlayLayer->Export(overlay_path);
    std::cout << "Overlay saved to: " << overlay_path << std::endl;
    return overlayStage;
}

std::string blender_usd_delegate::saveAs(std::string base_dir, std::string& user) {
    std::string base_name = user;
    int max_index = 0;

    for (const auto& entry : std::filesystem::directory_iterator(base_dir)) {
        if (std::filesystem::is_directory(entry)) {
            std::string dir_name = entry.path().filename().string();
            std::regex pattern(base_name + "_(\\d{3})");
            std::smatch match;
            if (std::regex_match(dir_name, match, pattern)) {
                int index = std::stoi(match[1]);
                if (index > max_index) max_index = index;
            }
        }
    }

    int new_index = max_index + 1;
    std::ostringstream oss;
    oss << base_name << "_" << std::setw(3) << std::setfill('0') << new_index;
    std::string new_dir_name = oss.str();

    std::filesystem::path new_dir_path = std::filesystem::path(base_dir) / new_dir_name;
    if (!std::filesystem::create_directory(new_dir_path)) {
        std::cerr << "Failed to create directory: " << new_dir_path << std::endl;
        return "";
    }

    std::cout << "Created new directory: " << new_dir_path << std::endl;
    return new_dir_path.string();
}

std::string blender_usd_delegate::loadInFile(std::string& file) {
    if (usdFile != "False")
        usdFile = file;
    try {
        stage = UsdStage::Open(usdFile);
        if (!stage) throw std::runtime_error("Failed to open USD stage.");

        std::cout << "Successfully loaded USD stage: " << stage->GetRootLayer()->GetIdentifier() << std::endl;
        return file;
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
        return "";
    }
}

void blender_usd_delegate::sendToRender() {
    // Create a render directory
    std::filesystem::path render_dir = std::filesystem::path(currentDirectory) / "renders";
    std::filesystem::create_directory(render_dir);

    // Construct command to run usdrecord
    std::string output_usd = (render_dir / "render.usda").string();
    std::string command = "usdrecord --frames=1 --output " + output_usd + " " + usdFile;

    int result = std::system(command.c_str());
    if (result != 0) {
        std::cerr << "usdrecord failed with code: " << result << std::endl;
    } else {
        std::cout << "Render written to: " << output_usd << std::endl;
    }
}

UsdStageRefPtr blender_usd_delegate::updateUsd() {
    if (!fileSaved)
        saveFile();
    return stage;
}

void blender_usd_delegate::writeCache() {
    std::string cachePath = std::string(getenv("HOME")) + "/.usd_delegate_cache.json";
    std::ofstream cache(cachePath);
    if (cache.is_open()) {
        cache << "{ \"last_scene\": \"" << usdFile << "\" }";
        cache.close();
    }
}
