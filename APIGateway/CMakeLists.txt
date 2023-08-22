cmake_minimum_required(VERSION 3.13)

set(PROJECT_NAME server)

# set(CMAKE_CXX_FLAGS "-std=c++14 -lpthread")

project(${PROJECT_NAME})

include_directories(include)

# set(SOURCES src/.cpp)
# set(HEADERS include/*.hpp)

file(GLOB SOURCES "src/*.cpp")
# file(GLOB HEADERS "include/*.hpp")

set(TEST_SOURCE "test/test_server.cpp")
list(APPEND SOURCES ${TEST_SOURCE})


message(${PROJECT_NAME})

add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})

target_link_libraries(${PROJECT_NAME} pthread)

target_compile_options(${PROJECT_NAME} PRIVATE -std=c++14)