cmake_minimum_required(VERSION 3.5)

project(matrix_determinate)

set(SOURCE_EXE main.cpp)

set(PATH_TO_CPP_FILES src)

set(SOURCE_LIB_MATRIX ${PATH_TO_CPP_FILES}/matrix.cpp)
set(SOURCE_LIB_TESTS test.cpp)

add_library(matrix STATIC ${SOURCE_LIB_MATRIX})
add_library(tests STATIC ${SOURCE_LIB_TESTS})

add_executable(main ${SOURCE_EXE})

target_link_libraries(main matrix tests)
