#pragma once
#include <string>
#include <vector>
#include <map>
#include <unistd.h>
#include <iostream> 
#include <sstream>
#include <queue>
#include <deque>

class ProcessCommand {
public:
    ProcessCommand();
    ProcessCommand(const std::string& dccPath, const std::string& usdPath, const std::string& userDept);

    void launch();                     // Launch DCC with USD file
    std::string getProcessInfo() const;
    std::string getActiveStage() const;
    std::string getDepartment() const;
    static std::queue<ProcessCommand> launchedProcesses;

    void setArgs(const std::vector<std::string>& arguments);
    void setEnvVariables();           // Write USD path and dept to environment
    std::map<std::string, std::string> getPresenceMetadata() const;

private:
    std::string dccPath;
    std::string usdPath;
    std::string userDept;
    std::vector<std::string> args;

    std::string dccName;
    uint8_t processID;
};
