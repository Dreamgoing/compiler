cmake_minimum_required(VERSION 3.6)
project(compiler VERSION 0.1.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
enable_testing()
option(BuildTests "Build the unit tests" ON)

#define project variable
set(COMPLIER_TARGET_NAME ${PROJECT_NAME})
set(SCANNER_LIB "scanner_lib")

# define the Scanner class's library.
set(SCANNER_LIB_SOURCE src/Scanner.h src/Scanner.cpp src/Error.cpp src/Error.h)

set(SOURCE_FILES ${SCANNER_LIB})
add_library(${SCANNER_LIB} ${SCANNER_LIB_SOURCE})

if (BuildTests)
    add_subdirectory(test)
endif ()


#add_executable(tet ${SOURCE_FILES})