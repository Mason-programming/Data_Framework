//
// Created by Mason Kirby on 6/14/25.
//
#include "sharedData.h"
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <nlohmann/json.hpp>
#include <iostream>
#include <sstream>

using json = nlohmann::json;

int main() {
    SharedData server;

    int server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd == 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    sockaddr_in address{};
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(7777);

    if (bind(server_fd, (struct sockaddr*)&address, sizeof(address)) < 0) {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }

    if (listen(server_fd, 3) < 0) {
        perror("listen");
        exit(EXIT_FAILURE);
    }

    std::cout << "🟢 SharedData socket server running on port 7777...\n";

    while (true) {
        int addrlen = sizeof(address);
        int client_fd = accept(server_fd, (struct sockaddr*)&address, (socklen_t*)&addrlen);
        if (client_fd < 0) {
            perror("accept");
            continue;
        }

        char buffer[4096] = {0};
        ssize_t valread = read(client_fd, buffer, sizeof(buffer) - 1);
        if (valread <= 0) {
            close(client_fd);
            continue;
        }

        try {
            json request = json::parse(buffer);
            json response;

            std::string cmd = request.value("cmd", "");
            std::string session = request.value("sessionName", "");
            std::string path = request.value("usdFile", "");

            if (cmd == "addEntry") {
                server.addEntry(session, path);
                response["status"] = "ok";
            } else if (cmd == "getEntry") {
                std::string result = server.getEntry(session);
                response["usdFile"] = result;
            } else if (cmd == "removeEntry") {
                server.removeEntry(session);
                response["status"] = "removed";
            } else {
                response["error"] = "Unknown command";
            }

            std::string reply = response.dump();
            send(client_fd, reply.c_str(), reply.size(), 0);
        } catch (const std::exception& e) {
            std::string err = std::string("{\"error\": \"") + e.what() + "\"}";
            send(client_fd, err.c_str(), err.size(), 0);
        }

        close(client_fd);
    }

    return 0;
}
