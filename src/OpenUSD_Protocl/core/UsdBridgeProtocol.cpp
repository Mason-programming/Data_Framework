#include "UsdBridgeProtocol.h"


UsdBridgeMessage UsdBridgeProtocol::parseMessage(const std::string& rawJson)
{
    UsdBridgeMessage messageProto; 
    json m = json::parse(rawJson); 

    try{
        messageProto.set_type(m.at("source").get<std::string>()); 
        messageProto.set_source(m.at("department").get<std::string>());  
        messageProto.set_department(m.at("file_type").get<std::string>()); 
        messageProto.set_usd_path(m.at("usd_path").get<std::string>()); 
        messageProto.set_timestamp(m.at("timestamp").get<std::string>()); 
        messageProto.set_file_path(m.at("file_path").get<std::string>()); 
    }
    catch{
        cout << "Could not deserlize the product" << endl; 
        return 1; 
    }

    return messageProto; 

}

void UsdBridgeProtocol::registerHandler(MessageType type,std::function<void(const UsdBridgeMessage&)> handler) {
    handlers_[type] = handler;
}

std::vector<uint8_t> UsdBridgeProtocol::buildPacket(const UsdBridgeMessage& msg){
    std::string jsonStr = toJson(msg); 

    PacketHeader 
    return 
}


void UsdBridgeProtocol::dispatch(const UsdBridgeMessage& message)
{
    std::string type = message.type();
    std::string path = message.usd_path();

    if (type == "IMPORT_USD") {
        importUsd(path);
    } else if (type == "SYNC_ANIMATION") {
        syncAnimation(path);
    } else {
        std::cerr << "⚠️ Unknown message type: " << type << std::endl;
    }
}