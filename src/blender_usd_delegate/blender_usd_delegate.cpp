//
// Created by Mason Kirby on 6/17/25.
//

#include "blender_usd_delegate.h"

blender_usd_delegate::blender_usd_delegate(std::string& user) : userSession(user) ,usdFile("False") {};
blender_usd_delegate::blender_usd_delegate(std::string& userSession, std::string& file) : usdFile(std::move(file)) {};
blender_usd_delegate::~blender_usd_delegate() {};

bool blender_usd_delegate::saveFile() {
    _createFile();
    stage->Save();
    return true;
}

UsdStageRefPtr blender_usd_delegate::_createFile() {
    if (!stage) {
        std::cerr << "No active stage to create overrides on." << std::endl;
        return nullptr;
    }

    // Create a new SdfLayer for overrides
    std::string overlay_path = "index.usda";
    SdfLayerRefPtr overlayLayer = SdfLayer::CreateNew(overlay_path);

    if (!overlayLayer) {
        std::cerr << "Failed to create overlay layer." << std::endl;
        return nullptr;
    }

    // Create a new stage that edits the overlay but composes the original stage
    UsdStageRefPtr overlayStage = UsdStage::Open(stage->GetRootLayer()->GetIdentifier());

    // Set the overlay layer as the current edit target
    overlayStage->SetEditTarget(overlayLayer);

    // Example: apply a transform override to /World/Cube

    SdfPath cubePath("/World/Cube");
    UsdGeomXform xform(overlayStage->GetPrimAtPath(cubePath));
    if (xform) {
        GfMatrix4d newTransform;
        newTransform.SetTranslate(GfVec3d(1.0, 2.0, 3.0));
        xform.MakeMatrixXform().Set(newTransform);
    }

    // Save the overlay layer (non-destructive edit)
    overlayLayer->Export(overlay_path);

    std::cout << "Overlay saved to: " << overlay_path << std::endl;
    return overlayStage;
}

std::string blender_usd_delegate::saveAs(std::string base_dir, std::string& user) {
    //std::filesystem::path base_dir = "./";  // You can change this to your base output location
    std::string base_name = user;
    int max_index = 0;
    saveFile();

    for (const auto& entry : std::filesystem::directory_iterator(base_dir)) {
        if (std::filesystem::is_directory(entry)) {
            std::string dir_name = entry.path().filename().string();

            // Match directories like "kirby_001", "kirby_002"
            std::regex pattern(base_name + "_(\\d{3})");
            std::smatch match;
            if (std::regex_match(dir_name, match, pattern)) {
                int index = std::stoi(match[1]);
                if (index > max_index)
                    max_index = index;
            }
        }
    }

    // Compose new directory name
    int new_index = max_index + 1;
    std::ostringstream oss;
    oss << base_name << "_" << std::setw(3) << std::setfill('0') << new_index;
    std::string new_dir_name = oss.str();

    std::filesystem::path new_dir_path = std::filesystem::path(base_dir) / new_dir_name;

    // Create the new directory
    if (!std::filesystem::create_directory(new_dir_path)) {
        std::cerr << "Failed to create directory: " << new_dir_path << std::endl;
        return "";
    }

    std::cout << "Created new directory: " << new_dir_path << std::endl;
    return new_dir_path.string();
}




std::string blender_usd_delegate::loadInFile(std::string &file) {

    if (usdFile != "False")
        usdFile = file;
    try{
        stage = UsdStage::Open(usdFile);

        if (!stage) {
            throw std::runtime_error("Failed to open USD stage.");
        }

        std::cout << "Successfully loaded USD stage: "
                  << stage->GetRootLayer()->GetIdentifier() << std::endl;
        // Send file to Blender
        // Make the structer
        // Pass to blender for actual import
        return file;
    }
    catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
        return nullptr;
    }
}