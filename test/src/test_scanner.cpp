//
// Created by 王若璇 on 16/12/6.
//

//#define CATCH_CONFIG_MAIN before the #include "catch.hpp" in exactly one source file.
#define CATCH_CONFIG_MAIN //This tells Catch to provide a main() - only do this in one cpp file

/**
 * @brief Scanner Unit_test file.re
 * @todo set the executable file path under current directory.
 * */

#include "catch.hpp"
#include "../../src/Scanner.h"

TEST_CASE("Scanner unit_test ","[Scanner]"){
    Scanner scanner;
    SECTION("Base_test scanner_test1.txt"){
        scanner.cleanUp();
        ///@note there are some problems in using absolute path.
//        scanner.openFile("~/ClionProjects/complier/test/data/scanner_test1.txt");

        ///@brief the first line.
        scanner.openFile("../../test/data/scanner_test1.txt");
        CHECK(scanner.nextToken().lexeme=="+");
        CHECK(scanner.nextToken().lexeme=="+");
        CHECK(scanner.nextToken().lexeme=="+");
        CHECK(scanner.nextToken().lexeme=="-123.456e-127");
        CHECK(scanner.nextToken().lexeme=="*");
        CHECK(scanner.nextToken().lexeme=="+45.99e+200");
        CHECK(scanner.nextToken().lexeme=="+");
        CHECK(scanner.nextToken().lexeme=="+");
        CHECK(scanner.nextToken().lexeme=="abc");
        CHECK(scanner.nextToken().lexeme=="+");
        CHECK(scanner.nextToken().lexeme=="-");
        CHECK(scanner.nextToken().lexeme=="cnt");
        CHECK(scanner.nextToken().lexeme=="+");
        CHECK(scanner.nextToken().lexeme=="+49");

        ////@brief the second line.
        CHECK(scanner.nextToken().lexeme=="(");
        CHECK(scanner.nextToken().lexeme=="+123.456");
        CHECK(scanner.nextToken().lexeme=="+");
        CHECK(scanner.nextToken().lexeme=="-456.789e-120");
        CHECK(scanner.nextToken().lexeme==")");
        CHECK(scanner.nextToken().lexeme=="*");
        CHECK(scanner.nextToken().lexeme=="m2");
        CHECK(scanner.nextToken().lexeme=="+");
        CHECK(scanner.nextToken().lexeme=="(");
        CHECK(scanner.nextToken().lexeme=="a");
        CHECK(scanner.nextToken().lexeme=="+");
        CHECK(scanner.nextToken().lexeme=="+456");
        CHECK(scanner.nextToken().lexeme==")");
        CHECK(scanner.nextToken().lexeme=="*");
        CHECK(scanner.nextToken().lexeme=="-");
        CHECK(scanner.nextToken().lexeme=="c123");

    }
    SECTION("Notes_test scanner_test2.txt"){
        scanner.cleanUp();
        scanner.openFile("../../test/data/scanner_test2.txt");
        CHECK(scanner.nextToken().lexeme=="//");
        CHECK(scanner.nextToken().lexeme=="/**/");
    }
}


