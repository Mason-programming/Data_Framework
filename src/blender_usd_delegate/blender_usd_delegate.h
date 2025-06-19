//
// Created by Mason Kirby on 6/17/25.
//

#ifndef PROCESSBRIDGE_BLENDER_USD_DELEGATE_H
#define PROCESSBRIDGE_BLENDER_USD_DELEGATE_H

#include <pxr/usd/usd/stage.h>
#include <pxr/base/tf/refPtr.h>
#include <pxr/usd/usdGeom/xform.h>
#include <pxr/usd/sdf/layer.h>
#include <pxr/base/gf/matrix4d.h>
#include <pxr/base/gf/vec3d.h>

#include <iostream>
#include <algorithm>
#include <filesystem>
#include <fstream>
#include <string>
#include <set>
#include <regex>

using namespace pxr;

struct usdFileData{
    std::vector<std::string> objects;
    bool operator<(const usdFileData& other) const {
        return objects < other.objects;
    }
};

class blender_usd_delegate {
public:
    blender_usd_delegate(std::string& user);
    blender_usd_delegate(std::string& userSession, std::string& file);
    ~blender_usd_delegate();

    bool saveFile();
    UsdStageRefPtr _createFile();
    std::string saveAs(std::string base_dir, std::string& user);
    std::string loadInFile(std::string& usdFile);
    UsdStageRefPtr passToBridge(UsdStageRefPtr stge);

private:
    std::string usdFile;
    std::string userSession;
    UsdStageRefPtr stage;
};


#endif //PROCESSBRIDGE_BLENDER_USD_DELEGATE_H
