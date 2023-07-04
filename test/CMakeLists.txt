FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG 9b12f74)

FetchContent_MakeAvailable(googletest)

add_executable(unit_tests
    ServerTest.cpp)

target_include_directories(unit_tests PRIVATE
    ${JSON_C_INCLUDE_DIR})

target_link_libraries(unit_tests
    GTest::gtest_main
    json-c)

set_target_properties(
    unit_tests
    PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

enable_testing()
include(GoogleTest)
gtest_discover_tests(unit_tests)
