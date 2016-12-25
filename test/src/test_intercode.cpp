//
// Created by 王若璇 on 16/12/25.
//


#define CATCH_CONFIG_MAIN //This tells Catch to provide a main() - only do this in one cpp file

#include <iostream>
#include "catch.hpp"
#include "../../src/Scanner.h"
#include "../../src/Parser.h"
#include "../../src/Symbol.h"
#include "../../src/Util.h"
#include "../../src/RecDesParser.h"
#include "../../src/InterCode.h"


/**
 * @brief InterCode Unit_test source
 *
 */

TEST_CASE("InterCode test","[InterCode]"){
    SECTION("interCode example test_1"){
        WARN("test expression");
        RecDesParser parser;
        InterCode interCode;
        parser.setSourcefile("../../test/data/intercode_test1.txt");
        parser.ast.setRoot(parser.expression());
        parser.ast.DFSshowAST();
        interCode.genExpression(parser.ast.getRoot());
    }
}
