cmake_minimum_required(VERSION 3.13)

set(PROJECT_NAME server)

set(CMAKE_CXX_FLAGS "-std=c++14 -lpthread")

project(${PROJECT_NAME})

set(SOURCES src/*.cpp)

set(HEADERS src/*.hpp)

message(${PROJECT_NAME})

add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})