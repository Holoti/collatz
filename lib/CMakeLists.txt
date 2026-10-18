add_library(${PROJECT_NAME}-lib STATIC
    collatz/tree.cpp
)

target_include_directories(${PROJECT_NAME}-lib PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)
