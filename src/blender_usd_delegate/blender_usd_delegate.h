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

#include "../sharedData/sharedData.h"
#include <iostream>
#include <algorithm>
#include <filesystem>
#include <fstream>
#include <string>
#include <regex>
#include <pthread.h>

using namespace pxr;

struct usdFileData {
    std::vector<std::string> objects;
    std::string nameOfFile;

};

class blender_usd_delegate : public SharedData {
public:
    blender_usd_delegate(std::string& user);
    blender_usd_delegate(std::string& userSession, std::string& file);
    ~blender_usd_delegate();

    bool saveFile();
    UsdStageRefPtr _createFile(std::string directory);
    std::string saveAs(std::string base_dir, std::string& user);
    std::string loadInFile(std::string& usdFile);
    void sendToRender();
    UsdStageRefPtr passToBridge(UsdStageRefPtr stge);
    void writeCache(); 
    virtual UsdStageRefPtr updateUsd();

private:
    pthread_mutex_t mutex;
    std::string currentDirectory = "";
    bool fileSaved = false;
    std::string usdFile;
    std::string userSession;
    UsdStageRefPtr stage;
};


#endif //PROCESSBRIDGE_BLENDER_USD_DELEGATE_H
