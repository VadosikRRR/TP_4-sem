cmake_minimum_required(VERSION 3.5)

project(experiments)

set(SOURCE_EXE main.cpp)

set(PATH_TO_CPP_FILES src)

set(SOURCE_LIB_PROGRAMS ${PATH_TO_CPP_FILES}/programs.cpp)

add_library(programs STATIC ${SOURCE_LIB_PROGRAMS})

add_executable(main ${SOURCE_EXE})

target_link_libraries(main programs)
