# Add the shared data server executable
add_executable(shared_data_server
        sharedData.cpp
        server_main.cpp
)

# Link dependencies
target_link_libraries(shared_data_server
        PRIVATE
        pthread
        nlohmann_json::nlohmann_json
)
