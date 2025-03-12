#pragma once 

#include <nlohmann/json.hpp>
using json = nlohmann::json;

class BridgeMessage{ 

    public: 
        std::string type; 
        std::string soucre; 
        std::string department; 
        std::string file_type; 
        std::string usd_path; 
        std::string timestamp;

    json to_json(); 
    
    static BridgeMessage from_json(const json& j); 
};  


