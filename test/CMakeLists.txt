cmake_minimum_required(VERSION 3.6)
set(COMPILER_UNITTEST_SCANNER "test_scanner")
set(COMPILER_UNITTEST_PARSER "test_parser")



set(CMAKE_CXX_STANDARD 11)

add_executable(${COMPILER_UNITTEST_SCANNER}
        "src/catch.hpp"
        "src/test_scanner.cpp")

#"../src/RecDesParser.h"
#"../src/RecDesParser.cpp"
#"../src/Scanner.h"
#"../src/Scanner.cpp"
#"../src/AST.h"
#"../src/AST.cpp"
#"../src/Error.h"
#"../src/Error.cpp"

add_executable(${COMPILER_UNITTEST_PARSER}
        "src/catch.hpp"
        "src/test_parser.cpp"
        )
#target_include_directories(${COMPLIER_UNITTEST_TARGET_NAME} PRIVATE "src")
target_link_libraries(${COMPILER_UNITTEST_SCANNER} ${SCANNER_LIB})

#${PARSER_LIB} ${AST_LIB} ${SCANNER_LIB})
target_link_libraries(${COMPILER_UNITTEST_PARSER} ${SOURCE_LIB})

