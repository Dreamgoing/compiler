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

TEST_CASE("InterCode test", "[InterCode]") {
    SECTION("interCode example test_1") {
        WARN("test expression");
        RecDesParser parser;
        InterCode interCode;
        parser.setSourcefile("../../test/data/intercode_test1.txt");
        parser.ast.setRoot(parser.assignStatement());
        parser.ast.DFSshowAST();
        interCode.genAssignment(parser.ast.getRoot());
        interCode.showQuaternionList();
    }
    SECTION("interCode example test_2") {
        WARN("test condition");
        RecDesParser parser;
        InterCode interCode;
        parser.setSourcefile("../../test/data/intercode_test2.txt");
        parser.ast.setRoot(parser.condition());
        parser.ast.DFSshowAST();
        interCode.genCondition(parser.ast.getRoot());
    }
    SECTION("interCode example test_3") {
        WARN("test selectionStatement");
        RecDesParser parser;
        InterCode interCode;
        assert(Quaternion::tolNum == 0);
        parser.setSourcefile("../../test/data/intercode_test3.txt");
        parser.ast.setRoot(parser.selectionStatement());
        parser.ast.DFSshowAST();
        interCode.genSelectionStatement(parser.ast.getRoot());
        interCode.showQuaternionList();
    }
    SECTION("interCode example test_4") {
        WARN("test loopStatement");
        RecDesParser parser;
        InterCode interCode;
        assert(Quaternion::tolNum == 0);
        parser.setSourcefile("../../test/data/intercode_test4.txt");
        parser.ast.setRoot(parser.whileStatement());
        parser.ast.DFSshowAST();
        interCode.genWhileStatement(parser.ast.getRoot());
        interCode.showQuaternionList();

    }
    SECTION("interCode example test_5") {
        WARN("final test");
        RecDesParser parser;
        InterCode interCode;
        assert(Quaternion::tolNum == 0);
        parser.setSourcefile("../../test/data/intercode_test5.txt");
        parser.ast.setRoot(parser.progress());
        parser.ast.DFSshowAST();
        interCode.genProgress(parser.ast.getRoot());
        interCode.showQuaternionList();

    }
}
