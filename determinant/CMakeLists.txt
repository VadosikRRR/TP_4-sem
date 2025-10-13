cmake_minimum_required(VERSION 3.5)

project(matrix_determinate)

set(SOURCE_EXE main.cpp)

set(PATH_TO_CPP_FILES src)

set(SOURCE_LIB_MATRIX ${PATH_TO_CPP_FILES}/matrix.cpp)
set(SOURCE_LIB_DETERMINANT ${PATH_TO_CPP_FILES}/determinant.cpp)
set(SOURCE_LIB_THREAD_POOL ${PATH_TO_CPP_FILES}/thread_pool.cpp)
set(SOURCE_LIB_TESTS test.cpp)

add_library(matrix STATIC ${SOURCE_LIB_MATRIX})
add_library(determinant STATIC ${SOURCE_LIB_DETERMINANT})
add_library(thread_pool STATIC ${SOURCE_LIB_THREAD_POOL})
add_library(tests STATIC ${SOURCE_LIB_TESTS})

add_executable(main ${SOURCE_EXE})

target_link_libraries(main tests matrix determinant thread_pool)
