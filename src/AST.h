//
// Created by 王若璇 on 16/12/7.
//

#ifndef COMPILER_AST_H
#define COMPILER_AST_H

#include <iostream>
#include <vector>
#include <queue>

#include "Scanner.h"

using namespace std;

class TreeNode {
public:

    ///node's level.
    mutable int deep;
    bool terminal{false};
    ///@todo how to use c++ union
//    union Value{
//        string id;
//        string key;
//        double dvalue; ///double value
//        int ivalue;    ///int value
//    }value;
    enum NodeType {
        ENDOFFILE = 100,

        ///@brief terminal symbol

        ///key word
                MAIN = 1,
        INT = 2,
        FLOAT = 3,
        DOUBLE = 4,
        CHAR = 5,
        IF = 6,
        ELSE = 7,
        DO = 8,
        WHILE = 9,

        ///variable
                STRING = 10,
        ID = 10,
        BINARY_NUMBER = 20,
        DOUBLE_NUMBER = 20,
        INT_NUMBER = 20,

        ///symbol
                ADD = 22,
        ASSIGN = 21,
        SUB = 23,
        MULT = 24,
        DIV = 25,
        LEFT_PAR = 26,
        RIGHT_PAR = 27,
        LEFT_BLOCK = 28,
        RIGHT_BLOCK = 29,
        COMMA = 30,
        SEMICOLON = 31,
        GREATER = 32,
        GREATER_EQUAL = 33,
        SMALLER = 34,
        SMALLER_EQUAL = 35,
        EQUAL = 36,
        NON_EQUAL = 37,
        HASH_MARK = 38,
        BOOL = 39,

        ///@brief TOP symbol
                KEY_WORD = 50,
        SYMBOL = 51,
        NONE = 52,
        ERROR = 53,
        END_MARK = 100,

        ///@brief non-terminal
                PROGRESS,
        STATEMENT,
        STATEMENTS,
        STATEMENT_BLOCK,
        ASSIGN_STATEMENT,
        DO_WHILE_STATEMENT,
        WHILE_STATEMENT,
        IF_CONDITION,
        ELSE_STATEMENT,
        TERM,
        FACTOR,
        EXPRESSION,
        CONDITION,
        SELECTION_STATEMENT


    } kind;
    Scanner::Token token;

public:
    TreeNode();

private:
    std::vector<TreeNode *> children_;


public:
    const std::vector<TreeNode *> &getChildren_() const;

    void setChildren_(const std::vector<TreeNode *> &children_);

    void addChild(TreeNode *child);

    void showNode();
};


/**
 * @brief Abstract syntax tree
 * @details The tree is used to contains all the node created in the parsing process.
 * */
class AST {

public:
    friend class TreeNode;

    using NodeType = TreeNode::NodeType;

private:
    TreeNode *root_;

    std::map<TreeNode::NodeType, string> infoTable_;

private:
    void DFSshowAST_(TreeNode *node, int deep);

    void showNode(TreeNode *node);


public:

    const map<NodeType, string> &getInfoTable_() const;

    void setInfoTable_(const map<NodeType, string> &infoTable_);

    void initInfoTable_();

    AST();

    AST(const AST &) = delete;

    void DFSshowAST();

    void BFSshowAST() const;

    TreeNode *getRoot() const;

    void setRoot(TreeNode *root);


};


#endif //COMPILER_AST_H
