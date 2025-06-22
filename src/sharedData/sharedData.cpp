#include "sharedData.h"
#include <cstring>

SharedData::SharedData() {
    initSharedMemory();
    initMutexIfNeeded();
}

SharedData::~SharedData() {
    munmap(block, sizeof(SharedBlock));
    close(shm_fd);
}

void SharedData::initSharedMemory() {
    shm_fd = shm_open(SHM_NAME, O_CREAT | O_RDWR, 0666);
    if (shm_fd == -1) {
        perror("shm_open");
        exit(EXIT_FAILURE);
    }

    ftruncate(shm_fd, sizeof(SharedBlock));

    void* ptr = mmap(nullptr, sizeof(SharedBlock), PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);
    if (ptr == MAP_FAILED) {
        perror("mmap");
        exit(EXIT_FAILURE);
    }

    block = static_cast<SharedBlock*>(ptr);
}

void SharedData::initMutexIfNeeded() {
    static bool initialized = false;
    if (!initialized) {
        pthread_mutexattr_t attr;
        pthread_mutexattr_init(&attr);
        pthread_mutexattr_setpshared(&attr, PTHREAD_PROCESS_SHARED);
        pthread_mutex_init(&block->mutex, &attr);
        initialized = true;
    }
}

void SharedData::addEntry(const std::string& sessionName, const std::string& usdFile) {
    pthread_mutex_lock(&block->mutex);

    if (block->count >= MAX_ENTRIES) {
        std::cerr << "Too many entries!" << std::endl;
        pthread_mutex_unlock(&block->mutex);
        return;
    }

    // Replace or add
    for (size_t i = 0; i < block->count; ++i) {
        if (strncmp(block->entries[i].sessionName, sessionName.c_str(), MAX_SESSION_NAME) == 0) {
            strncpy(block->entries[i].usdPath, usdFile.c_str(), MAX_PATH_LENGTH);
            pthread_mutex_unlock(&block->mutex);
            return;
        }
    }

    // Add new
    strncpy(block->entries[block->count].sessionName, sessionName.c_str(), MAX_SESSION_NAME);
    strncpy(block->entries[block->count].usdPath, usdFile.c_str(), MAX_PATH_LENGTH);
    block->count++;

    pthread_mutex_unlock(&block->mutex);
}

std::string SharedData::getEntry(const std::string& sessionName) {
    pthread_mutex_lock(&block->mutex);

    for (size_t i = 0; i < block->count; ++i) {
        if (strncmp(block->entries[i].sessionName, sessionName.c_str(), MAX_SESSION_NAME) == 0) {
            pthread_mutex_unlock(&block->mutex);
            return std::string(block->entries[i].usdPath);
        }
    }

    pthread_mutex_unlock(&block->mutex);
    return "";
}

void SharedData::removeEntry(const std::string& sessionName) {
    pthread_mutex_lock(&block->mutex);

    for (size_t i = 0; i < block->count; ++i) {
        if (strncmp(block->entries[i].sessionName, sessionName.c_str(), MAX_SESSION_NAME) == 0) {
            block->entries[i] = block->entries[block->count - 1];  // Swap with last
            block->count--;
            break;
        }
    }

    pthread_mutex_unlock(&block->mutex);
}


void SharedData::printAll() {
    pthread_mutex_lock(&block->mutex);

    std::cout << "== Shared USD Sessions ==" << std::endl;
    for (size_t i = 0; i < block->count; ++i) {
        std::cout << "Session: " << block->entries[i].sessionName
                  << ", Path: " << block->entries[i].usdPath << std::endl;
    }

    pthread_mutex_unlock(&block->mutex);
}

void SharedData::handleRequest(const std::string &jsonFile) {
    std::ifstream in(jsonFile);
    if (!in.is_open()) {
        std::cerr << "Failed to open request file: " << jsonFile << std::endl;
        return;
    }

    json request;
    try {
        in >> request;
    } catch (const std::exception &e) {
        std::cerr << "Invalid JSON: " << e.what() << std::endl;
        return;
    }

    const std::string action = request.value("action", "");
    const std::string session = request.value("session", "");
    const std::string path = request.value("path", "");

    if (action == "add") {
        if (session.empty() || path.empty()) {
            std::cerr << "Missing session or path for add." << std::endl;
            return;
        }
        addEntry(session, path);
    } else if (action == "get") {
        if (session.empty()) {
            std::cerr << "Missing session name for get." << std::endl;
            return;
        }
        std::string usd = getEntry(session);
        std::cout << "Retrieved path for session [" << session << "]: " << usd << std::endl;
    } else if (action == "remove") {
        if (session.empty()) {
            std::cerr << "Missing session name for remove." << std::endl;
            return;
        }
        removeEntry(session);
    } else if (action == "print") {
        printAll();
    } else {
        std::cerr << "Unknown action: " << action << std::endl;
    }
}



