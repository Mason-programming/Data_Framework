cmake_minimum_required(VERSION 3.14)
project(Data_Framework)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find JSON library
find_package(nlohmann_json REQUIRED)
find_package(pxr CONFIG REQUIRED)
find_package(OpenSubdiv CONFIG REQUIRED)

# Add subdirectory for C++ Frameworks
add_subdirectory(src/sharedData)
add_subdirectory(src/blender_usd_delegate)