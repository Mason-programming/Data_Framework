
#include <map> 
#include <mutex> 

class SmartSceneBus {
public:
    struct ClientInfo {
        std::string dccName;
        std::string usdStage;
        std::string department;
        std::string username;
        std::chrono::steady_clock::time_point lastSeen;
    };

    SmartSceneBus();
    ~SmartSceneBus();

    void registerClient(const std::string& clientId, const ClientInfo& info);
    void unregisterClient(const std::string& clientId);

    void receiveMessage(const std::string& clientId, const std::string& jsonMsg);
    void broadcastUSDUpdate(const std::string& usdPath, const std::string& deptFilter = "");

    void tickPresence();
    void printConnectedClients();

private:
    std::map<std::string, ClientInfo> clients_;
    std::mutex busMutex;
};
