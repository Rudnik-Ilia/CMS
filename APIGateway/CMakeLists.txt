cmake_minimum_required(VERSION 3.13)

set(PROJECT_NAME server)

project(${PROJECT_NAME})

include_directories(include /usr/include/nlohmann)

file(GLOB SOURCES "src/*.cpp")

set(TEST_SOURCE "test/test_server.cpp")
list(APPEND SOURCES ${TEST_SOURCE})

message(${PROJECT_NAME})

add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})

target_link_libraries(${PROJECT_NAME} PRIVATE pthread)
target_link_libraries(${PROJECT_NAME}  PRIVATE jwt)


target_compile_options(${PROJECT_NAME} PRIVATE -std=c++14)



