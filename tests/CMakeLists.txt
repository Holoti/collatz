include(FetchContent)

FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/releases/download/v1.16.0/googletest-1.16.0.tar.gz
    DOWNLOAD_EXTRACT_TIMESTAMP ON
    FIND_PACKAGE_ARGS NAMES GTest
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

FetchContent_MakeAvailable(googletest)

add_executable(${PROJECT_NAME}-tests
    physics/geometry_vector/named_requirements_test.cpp
)

target_link_libraries(${PROJECT_NAME}-tests PRIVATE
    ${PROJECT_NAME}-lib
    GTest::gtest_main
)

add_dependencies(${PROJECT_NAME}-tests ${PROJECT_NAME})

target_compile_definitions(${PROJECT_NAME}-tests PRIVATE
    VALKEY_EXECUTABLE="$<TARGET_FILE:${PROJECT_NAME}>"
)

include(GoogleTest)

gtest_discover_tests(${PROJECT_NAME}-tests)