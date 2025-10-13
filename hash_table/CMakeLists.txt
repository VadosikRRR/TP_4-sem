cmake_minimum_required(VERSION 3.5)

project(hash_table)

set(CMAKE_BUILD_TYPE Debug)

set(SOURCE_EXE main.cpp)

set(PATH_TO_CPP_FILES src)

set(SOURCE_LIB_DATA ${PATH_TO_CPP_FILES}/data.cpp)
set(SOURCE_LIB_EXCEPTION ${PATH_TO_CPP_FILES}/exception.cpp)
set(SOURCE_LIB_THREAD_POOL ${PATH_TO_CPP_FILES}/thread_pool.cpp)
set(SOURCE_LIB_LIST ${PATH_TO_CPP_FILES}/list.cpp)
set(SOURCE_LIB_HASH_TABLE ${PATH_TO_CPP_FILES}/hash_table.cpp)
set(SOURCE_LIB_TEST test.cpp)

add_library(data STATIC ${SOURCE_LIB_DATA})
add_library(exception STATIC ${SOURCE_LIB_EXCEPTION})
add_library(thread_pool STATIC ${SOURCE_LIB_THREAD_POOL})
add_library(list STATIC ${SOURCE_LIB_LIST})
add_library(hash_table STATIC ${SOURCE_LIB_HASH_TABLE})
add_library(test STATIC ${SOURCE_LIB_TEST})

add_executable(main ${SOURCE_EXE})

target_link_libraries(main test hash_table list thread_pool exception data)