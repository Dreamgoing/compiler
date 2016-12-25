cmake_minimum_required(VERSION 3.6)
project(compiler VERSION 0.1.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
enable_testing()
option(BuildTests "Build the unit tests" ON)


#define project variable
set(COMPLIER_TARGET_NAME ${PROJECT_NAME})
set(SCANNER_LIB "scanner_lib")
set(AST_LIB "ast_lib")
set(PARSER_LIB "parser_lib")
set(SYMBOL_LIB "symbol_lib")
set(SOURCE_LIB "source_lib")
set(RECDESPARSER_LIB "resdesparser_lib")

# define the Util.hpp
set(UTIL_SOURCE src/Util.h)

# define the Scanner class's library.
set(SCANNER_LIB_SOURCE src/Scanner.h src/Scanner.cpp src/Error.cpp src/Error.h)
add_library(${SCANNER_LIB} ${SCANNER_LIB_SOURCE})

# define the AST class's library.
set(AST_LIB_SOURCE src/AST.h src/AST.cpp)
add_library(${AST_LIB} ${AST_LIB_SOURCE})

# define the Parser class's library
set(PARSER_LIB_SOURCE
        src/Parser.h src/Parser.cpp
        src/RecDesParser.h src/RecDesParser.cpp
        )
add_library(${PARSER_LIB} ${PARSER_LIB_SOURCE})

# define the Symbol class's library
set(SYMBOL_LIB_SOURCE src/Symbol.h src/Symbol.cpp)
add_library(${SYMBOL_LIB} ${SYMBOL_LIB_SOURCE})

# define the  RecDesParser class's library
set(RECDESPARSER_LIB_SOURCE
        src/RecDesParser.h src/RecDesParser.cpp
        )
add_library(${RECDESPARSER_LIB} ${RECDESPARSER_LIB_SOURCE} ${UTIL_SOURCE})

set(SOURCE_FILES
        src/Scanner.h src/Scanner.cpp
        src/Error.cpp src/Error.h
        src/AST.h src/AST.cpp
        src/Parser.h src/Parser.cpp
        src/Symbol.h src/Symbol.cpp
        src/RecDesParser.h src/RecDesParser.cpp
        src/SymbolTable.h src/SymbolTable.cpp
        src/InterCode.h src/InterCode.cpp)
add_library(${SOURCE_LIB} ${SOURCE_FILES})

if (BuildTests)
    add_subdirectory(test)
endif ()


#add_executable(tet ${SOURCE_FILES})