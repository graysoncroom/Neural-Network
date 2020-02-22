cmake_minimum_required(VERSION 3.14)
project(Neural_Network VERSION 1.0)

set(CMAKE_CXX_STANDARD 14)

configure_file(Config.h.in Config.h)

add_executable(Neural_Network main.cpp mnist_reader.cpp mnist_reader.h)

target_include_directories(Neural_Network PUBLIC "${PROJECT_BINARY_DIR}")
