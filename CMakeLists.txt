cmake_minimum_required(VERSION 3.14)
project(Data_Framework)

set(CMAKE_CXX_STANDARD 17)

# Find JSON library
find_package(nlohmann_json REQUIRED)

# Add subdirectory for sharedData (C++ server)
add_subdirectory(src/sharedData)
