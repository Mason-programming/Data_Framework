//
// Created by Mason Kirby on 6/14/25.
//
#ifndef PROCESSBRIDGE_SHAREDDATA_H
#define PROCESSBRIDGE_SHAREDDATA_H

/*
 * If there is a process running this class will act as a way to pass
 * data back and forth to different running process
 * This is simulate a light weight V_Look up table
 * So if I have multiple DCC process stared with difrerent USDs
 * the sessionManager command will not cause unepected behavior
 * when it trys to access the current usd loaded into
 * USD_PATH enviorment varible
 * I think I will need to write the unorder_map to a file
 * I need to share the memory between process so I need to use mmap
 */


#include <string>
#include <unordered_map>
#include <pthread.h>
#include <sys/mman.h>
#include <unistd.h>
#include <fcntl.h>
#include <iostream>
#include <map>
#include <fstream>
#include <nlohmann/json.hpp>

using json = nlohmann::json;
#define SHM_NAME "/usd_session_shared_memory"

const size_t MAX_ENTRIES = 64;
const size_t MAX_SESSION_NAME = 64;
const size_t MAX_PATH_LENGTH = 512;

struct SharedEntry {
    char sessionName[MAX_SESSION_NAME];
    char usdPath[MAX_PATH_LENGTH];
};

struct SharedBlock {
    pthread_mutex_t mutex;
    SharedEntry entries[MAX_ENTRIES];
    size_t count;
};

class SharedData {
public:
    SharedData();
    ~SharedData();

    void handleRequest(const std::string& jsonFile);
    void addEntry(const std::string& sessionName, const std::string& usdFile);
    std::string getEntry(const std::string& sessionName);
    void removeEntry(const std::string& sessionName);
    void printAll();

private:
    std::unordered_map<std::string, std::string> session_to_usd_path;
    int shm_fd;
    SharedBlock* block;
    void initSharedMemory();
    void initMutexIfNeeded();
};
#endif //PROCESSBRIDGE_SHAREDDATA_H
