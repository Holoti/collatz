# Reset execution counts so each report reflects only the current test run.
if(NOT IS_ABSOLUTE "${COVERAGE_BUILD_DIR}"
   OR NOT EXISTS "${COVERAGE_BUILD_DIR}/CMakeCache.txt")
    message(FATAL_ERROR "COVERAGE_BUILD_DIR must be an existing CMake build directory.")
endif()

file(REAL_PATH "${COVERAGE_BUILD_DIR}" coverage_build_root)
file(GLOB_RECURSE coverage_data LIST_DIRECTORIES false
    "${coverage_build_root}/*.gcda")
foreach(data_file IN LISTS coverage_data)
    file(REAL_PATH "${data_file}" resolved_data_file)
    cmake_path(IS_PREFIX coverage_build_root "${resolved_data_file}" NORMALIZE is_inside_build)
    if(NOT is_inside_build)
        message(FATAL_ERROR "Coverage data is outside the build directory: ${data_file}")
    endif()
    file(REMOVE "${data_file}")
endforeach()
