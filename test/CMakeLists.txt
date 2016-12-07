cmake_minimum_required(VERSION 3.6)
set(COMPLIER_UNITTEST_TARGET_NAME "complier_unit")



set(CMAKE_CXX_STANDARD 11)

add_executable(${COMPLIER_UNITTEST_TARGET_NAME}
        "src/catch.hpp"
        "src/test_scanner.cpp")

#target_include_directories(${COMPLIER_UNITTEST_TARGET_NAME} PRIVATE "src")
target_link_libraries(${COMPLIER_UNITTEST_TARGET_NAME} ${SCANNER_LIB})
#set(SOURCE_FILES src/test_scanner.cpp)
