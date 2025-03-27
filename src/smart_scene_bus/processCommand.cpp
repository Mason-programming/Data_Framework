#include "processCommand.h"


std::queue<ProcessCommand> ProcessCommand::launchedProcesses; // static definition

ProcessCommand::ProcessCommand(const std::string& dccPath, const std::string& usdPath, const std::string& userDept)
    : dccPath(dccPath), usdPath(usdPath), userDept(userDept)
{
    std::cout << dccPath << std::endl; 
    // Extract just the binary name from the dcc path (e.g. "blender", "maya")
    size_t lastSlash = dccPath.find_last_of("/\\");
    dccName = dccPath.substr(lastSlash + 1);
    processID = static_cast<uint8_t>(getpid());
    
}

void ProcessCommand::launch(){

    setEnvVariables();

    pid_t pid = fork(); 

    if(pid == 0)
    {
        std::vector<char*> argv; 
        argv.push_back(const_cast<char*>(dccPath.c_str())); 
        for (const std::string& arg : args){
            argv.push_back(const_cast<char*>(arg.c_str())); 
        } 
        argv.push_back(nullptr); // execvp expects a null-terminated 

        execvp(argv[0], argv.data());

        std::cerr << "Failed to launch DCC Process" << std::endl; 
        exit(0); 
    }
    else if(pid < 0)
    {
        std::cout << "Launched " << dccName << " with PID: " << pid << std::endl;
        launchedProcesses.push(*this);
        
    }
    else {
        std::cerr << "Fork failed" << std::endl; 
    }
}

void ProcessCommand::setArgs(const std::vector<std::string>& arguments) {
    args = arguments;
}

void ProcessCommand::setEnvVariables() {
    setenv("USD_FILE_PATH", usdPath.c_str(), 1);
    setenv("USER_DEPARTMENT", userDept.c_str(), 1);
    setenv("DCC_NAME", dccName.c_str(), 1);
}

std::string ProcessCommand::getProcessInfo() const {
    std::ostringstream oss;
    oss << "Process ID: " << static_cast<int>(processID)
        << ", DCC: " << dccName
        << ", USD File: " << usdPath;
    return oss.str();
}

std::string ProcessCommand::getActiveStage() const {
    return usdPath;
}

std::string ProcessCommand::getDepartment() const {
    return userDept;
}

std::map<std::string, std::string> ProcessCommand::getPresenceMetadata() const {
    return {
        {"dcc", dccName},
        {"usd_path", usdPath},
        {"department", userDept},
        {"process_id", std::to_string(processID)}
    };
}
