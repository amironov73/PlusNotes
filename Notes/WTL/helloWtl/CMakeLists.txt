cmake_minimum_required(VERSION 2.8)
project(helloWtl)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(${PROJECT_SOURCE_DIR}/WTL)
add_executable(helloWtl WIN32 main.cpp)