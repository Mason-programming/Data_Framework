#include "USDImportModule.h"
#include "USDAssestImportData.h"
#include "AssetImportTask.h"
#include "Factories/Factory.h"
#include "Misc/FileHelper.h"
#include "AssetRegistry/AssetRegistryModule.h"


class importUSD{
    
    private: 
    std::string pathToUSDFile = ""; 
    std::string projectPath = ""; 
    UObject* stge = nullptr; 

    public: 
    importUSD(); 
    ~importUSD(); 


    std::string getUsdFile(std::string& pathToUsd, std::string& projectPath); 
    UObject* ImportUSD(stdstring& USDPath, std::string& ProjectPath); 

}