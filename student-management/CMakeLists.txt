cmake_minimum_required(VERSION 3.10)
project(StudentManagementSystem CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

file(GLOB SOURCES "${CMAKE_SOURCE_DIR}/src/*.cpp")

add_executable(StudentApp ${SOURCES})
target_include_directories(StudentApp PRIVATE "${CMAKE_SOURCE_DIR}/include")
