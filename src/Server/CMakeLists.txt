add_executable(server
    serverReadsProfiler.cpp)

target_link_libraries(server
    json-c
    pthread)

target_include_directories(server PRIVATE
    ${JSON_C_INCLUDE_DIR})

set_target_properties(
    server
    PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
