//
// Created by 王若璇 on 16/12/8.
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
 * @brief Parser Unit_test source
 * @todo + Naming conventions
 *       + more strong
 *
 * */


TEST_CASE("Parser test","[Parser]"){
    Parser parser;
    parser.initParserTable();
    //std::cout<<Symbol::expression<<" "<<Symbol::expression_<<std::endl;
    SECTION("parser table test"){
        CHECK(!parser.getParserTable_().empty());
    }
    SECTION("parser example test_1"){
        WARN("example : ab + bc");
        parser.setSourcefile("../../test/data/parser_test1.txt");
        CHECK(parser.predictiveParse());
    }
    SECTION("parser example test_2"){
        WARN("example : num + -123.346e-128 + +12 --12");
        parser.setSourcefile("../../test/data/parser_test2.txt");
        Scanner::Token token = parser.nextToken();
        while (token.kind!=Scanner::TokenType::ENDOFFILE){
            cout<<token.lexeme<<" "<<token.kind<<endl;
            token = parser.nextToken();
        }
//        CHECK(parser.predictiveParse());
    }
    SECTION("parser example test_3"){
        WARN("example : (+123.456+-456.789e-120)*m2+(a++456)*-c123");
        parser.setSourcefile("../../test/data/parser_test3.txt");
        CHECK(parser.predictiveParse());
    }

    SECTION("string convert to num. @param [string] @return [double] or [int]"){
        INFO("to distinguish between double and int");

        ///@todo why no throw. learn how to use CHEAK_NOTHROW
        ///@note when fail to call function stringToInt
//        CHECK(mystringToInt("123").second==123);
//        CHECK_NOTHROW(mystringToInt("123"));
//        CHECK_THROWS(stringToInt("123"));
//        CHECK_THROW(stringToInt("1.1")==1.1);
//        CHECK_THROWS(stringToInt("1.123"));
    }
    SECTION("parser example test_4"){
        WARN("build the AST");
        //INFO("derived class implement");
        RecDesParser rParser;
        rParser.setSourcefile("../../test/data/parser_test4.txt");

        ///@brief show token
//        Scanner::Token token = rParser.nextToken();
//        while (token.kind!=Scanner::TokenType::ENDOFFILE){
//            cout<<token.lexeme<<" "<<token.kind<<endl;
//            token = rParser.nextToken();
//        }

        ///@brief predictive Method
//        rParser.initParserTable();
//        CHECK(rParser.predictiveParse());

        ///@brief RecDesParser Method
        rParser.ast.setRoot(rParser.progress());
//        rParser.ast.BFSshowAST();
        rParser.ast.DFSshowAST();

//        parser.setSourcefile("../../test/data/parser_test4.txt");
//        RecDesParser::recusiveDescentParse(parser);
//
        //parser.getAst_().showAST();

    }
}
