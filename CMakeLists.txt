
cmake_minimum_required(VERSION 2.8)

# Project name
project(distance_optimise)

# Project flags
set (CMAKE_CXX_FLAGS "--std=gnu++11 ${CMAKE_CXX_FLAGS}")

# Sources folder
aux_source_directory(./src/ SRC_LIST)

# Outpu directory to bin/
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Generate executable
add_executable(${PROJECT_NAME} ${SRC_LIST})

