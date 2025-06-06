cmake_minimum_required(VERSION 3.5)

project(logger)

set(SOURCE_EXE main.cpp)

set(PATH_TO_CPP_FILES src)

set(SOURCE_LIB_DATA1 ${PATH_TO_CPP_FILES}/logger1.cpp)
set(SOURCE_LIB_DATA2 ${PATH_TO_CPP_FILES}/logger2.cpp)
set(SOURCE_LIB_DATA3 ${PATH_TO_CPP_FILES}/logger3.cpp)
set(SOURCE_LIB_DATA4 ${PATH_TO_CPP_FILES}/logger4.cpp)

add_library(logger1 STATIC ${SOURCE_LIB_DATA1})
add_library(logger2 STATIC ${SOURCE_LIB_DATA2})
add_library(logger3 STATIC ${SOURCE_LIB_DATA3})
add_library(logger4 STATIC ${SOURCE_LIB_DATA4})

add_executable(main ${SOURCE_EXE})

target_link_libraries(main logger1 logger2 logger3 logger4)
