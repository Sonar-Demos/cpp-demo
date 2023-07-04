if(APPLE)
  set(JSON_C_INCLUDE_DIR "/opt/homebrew/opt/json-c/include")
  link_directories("/opt/homebrew/opt/json-c/lib")
else()
  set(JSON_C_INCLUDE_DIR)
endif()

cmake_minimum_required(VERSION 3.15)
project(ReadsProfiler CXX)

set(CMAKE_CXX_STANDARD 17)

include(FetchContent)
add_subdirectory(src/Server)
add_subdirectory(src/Client)
add_subdirectory(test)
