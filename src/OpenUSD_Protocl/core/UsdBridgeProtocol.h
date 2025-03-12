#pragma once 

#include <string>
#include <map>
#include <functional>
#include <vector>
#include <nlohmann/json.hpp>

enum class MessageType{ 

    IMPORT_USD, 
    EXPORT_USD, 
    SYNC_ANIMATION,
    UPDATE_MATERIAL,
    CAD_FILE, 
    FBX_FILE, 
    HEARTBEAT,
    UNKNOWN

}; 

// The usd message structure 
struct UsdBridgeMessage
{ 
    MessageType type;
    std::string source;
    std::string department;
    std::string file_type;
    std::string usd_path;
    std::string timestamp;
    std:string file_path; 

}; 

class UsdBridgeProtocol
{ 
    public: 
    UsdBridgeProtocol();
    ~UsdBridgeProtocol();

    // Deserialize JSON into a usable C++ message
    UsdBridgeMessage parseMessage(const std::string& rawJson);

    // Serialize message to JSON
    std::string toJson(const UsdBridgeMessage& msg) const;

    // Register a handler for a message type
    void registerHandler(MessageType type, std::function<void(const UsdBridgeMessage&)> handler);

    // Dispatch incoming message to appropriate handler
    void dispatch(const UsdBridgeMessage& message);

    private: 
    std::map<MessageType, std::function<void(const UsdBridgeMessage&)>> handlers_;

    // Helper to convert string to MessageType
    MessageType parseType(const std::string& typeStr);

}; 