cmake_minimum_required(VERSION 3.10)
project(ChessGame CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

file(GLOB SOURCES "${CMAKE_SOURCE_DIR}/src/*.cpp")

add_executable(ChessGame ${SOURCES})
target_include_directories(ChessGame PRIVATE "${CMAKE_SOURCE_DIR}/include")
