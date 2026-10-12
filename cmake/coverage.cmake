option(WITH_COVERAGE "Enable GCC coverage instrumentation and reports" OFF)

if(NOT WITH_COVERAGE)
    return()
endif()

if(NOT CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    message(FATAL_ERROR "WITH_COVERAGE requires GCC and a matching gcov executable.")
endif()

if(CMAKE_SOURCE_DIR STREQUAL CMAKE_BINARY_DIR)
    message(FATAL_ERROR "Coverage requires an out-of-source build, e.g. -B build.")
endif()

find_program(GCOVR_EXECUTABLE NAMES gcovr REQUIRED)

# Include the tests because header implementations are compiled into them.
# Keep instrumentation private to our targets, excluding third-party libraries.
foreach(target IN ITEMS ${PROJECT_NAME}-lib ${PROJECT_NAME} ${PROJECT_NAME}-tests)
    target_compile_options(${target} PRIVATE --coverage -O0 -g)
endforeach()

foreach(target IN ITEMS ${PROJECT_NAME} ${PROJECT_NAME}-tests)
    target_link_options(${target} PRIVATE --coverage)
endforeach()

add_custom_target(coverage
    COMMAND ${CMAKE_COMMAND}
        "-DCOVERAGE_BUILD_DIR=${CMAKE_BINARY_DIR}"
        -P "${CMAKE_CURRENT_LIST_DIR}/reset_coverage.cmake"
    COMMAND ${CMAKE_CTEST_COMMAND}
        --test-dir "${CMAKE_BINARY_DIR}"
        -C "$<CONFIG>" --output-on-failure --no-tests=error
    COMMAND "${GCOVR_EXECUTABLE}"
        --root "${CMAKE_SOURCE_DIR}" "${CMAKE_BINARY_DIR}"
        --filter "lib/" --filter "bin/"
        --html-details "${CMAKE_BINARY_DIR}/coverage.html"
        --html-self-contained --html-theme green
        --txt "${CMAKE_BINARY_DIR}/coverage.txt"
        --json-summary "${CMAKE_BINARY_DIR}/coverage.json"
    COMMAND ${CMAKE_COMMAND} -E echo
        "Coverage report: ${CMAKE_BINARY_DIR}/coverage.html"
    WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}"
    COMMENT "Running tests and generating coverage reports"
    VERBATIM
    USES_TERMINAL
)

add_dependencies(coverage ${PROJECT_NAME}-tests)
