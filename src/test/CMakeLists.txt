cmake_minimum_required(VERSION 3.16)

project(ABSTRACT_TEST)

include(${CMAKE_CURRENT_LIST_DIR}/../abstract/abstract_include.cmake)

add_executable(ABSTRACT_TEST
    test_runner.c
    parser_test/parser_test.c

    unity/unity.c
)
target_include_directories(ABSTRACT_TEST PRIVATE
    unity
    parser_test
)
target_link_libraries(ABSTRACT_TEST PRIVATE
    abstract_files
)
