cmake_minimum_required(VERSION 3.15)
project(ReadsProfiler CXX)

include(FetchContent)
FetchContent_Declare(json-c
    GIT_REPOSITORY https://github.com/json-c/json-c.git
    GIT_TAG 4d529f9)

FetchContent_MakeAvailable(json-c)

if(MACOS)

endif()

set(CMAKE_CXX_STANDARD 17)

add_executable(server
    src/Server/serverReadsProfiler.cpp)

target_include_directories(server PRIVATE
    src/Server
    ${json-c_SOURCE_DIR})

target_link_libraries(server
    json-c)
