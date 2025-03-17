#include "importUSDUnreal.h"


std::string importUSD::getUsdFile(){
    const* char varName = "USD_FILE_PATH"; 

    const char* var_value = std::getenv(varName); 

    if (varVal != nullptr){
        return std::string(var_value)
    }else{ 
        return "Error: There is not USD Found"; 
    }

    return "None"; 
}



UObject* importUSD::ImportUSD(std::string& USDPath, std::string& ProjectPath){


    if(!){
        UE_LOG(LogTemp, Error, Text("USD File does not exists")); 
        return nullptr; 
    }

    UAssetImportTask* ImportTask = NewObject<UAssetImportTask>(); 
    ImportTask->FileName = USDPath; 
    ImportTask->DestinationPath = ProjectPath; 
    ImportTask->bSave = true; 
    ImportTask->bAutomated = false; 

    UFactory* USDImportFactory = nullptr; 
    TArray<UFactory> Factories; 
    FAssetRegistryModule& AssetRegistryModule = FModuleManager::LoadModuleChecked<FAssetRegistryModule>("AssetRegistry");
    IAssetRegistry& AssetRegistry = AssetRegistryModule.Get();
    AssetRegistry.GetAssetFactories(Factories);

    for (UFactory* Factory : Factories)
        {
            if (Factory->SupportsFileExtension("usd") || Factory->SupportsFileExtension("usda") || Factory->SupportsFileExtension("usdc"))
            {
                USDImportFactory = Factory;
                break;
            }
        }
    ImportTask->Factory = USDImportFactory;
    
        // Process the import task
        if (USDImportFactory)
        {
            TArray<UObject*> ImportedAssets = {};
            ImportTask->ProcessImport();
            ImportedAssets.Append(ImportTask->GetImportedObjects());
    
            if (ImportedAssets.Num() > 0)
            {
                return ImportedAssets[0];
            }
            else
            {
                UE_LOG(LogTemp, Warning, TEXT("USD import failed or no assets were imported."));
                return nullptr;
            }
        }

        else
        {
            UE_LOG(LogTemp, Error, TEXT("No USD factory found."));
            return nullptr;
        }

    

}