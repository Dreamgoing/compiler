//
// Created by 王若璇 on 16/12/14.
//

#ifndef COMPILER_RECDESPARSER_H
#define COMPILER_RECDESPARSER_H

#include "Parser.h"
#include "Error.h"
//#include "Util.h"
#include "AST.h"

#include <string>
#include <sstream>
#include "Scanner.h"

///@brief RecDesParser class use Strategy pattern implement.

///public inheritance.
class RecDesParser : public Parser {
    using tokenType = Scanner::TokenType;
    using nodeType =  TreeNode::NodeType;
public:
    void recusiveDescentParse();

    TreeNode *progress();

    ///statement
    TreeNode *statementBlock();

    TreeNode *statements();

    TreeNode *statement();

    TreeNode *assignStatement();

    TreeNode *loopStatement();

    TreeNode *do_whileStatement();

    TreeNode *whileStatement();

    TreeNode *parCondition();

    TreeNode *elseStatement();

    TreeNode *selectionStatement();

    TreeNode *condition();

    ///expression
    TreeNode *expression();

    TreeNode *term();

    TreeNode *factor();

    ///other

    TreeNode *num();

    TreeNode *id();

    TreeNode *relationalOp();


};


#endif //COMPILER_RECDESPARSER_H
