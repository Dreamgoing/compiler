//
// Created by 王若璇 on 16/12/22.
//

#ifndef COMPILER_INTERCODE_H
#define COMPILER_INTERCODE_H

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <forward_list>
#include "AST.h"

using namespace std;

class Quaternion{
public:
    string op;
    string arg1;
    string arg2;

    Quaternion(const string &op, const string &arg1, const string &arg2, const string &result) : op(op), arg1(arg1),
                                                                                                 arg2(arg2),
                                                                                                 result(result) {}

    string result;



    static int tolNum;
public:

    Quaternion(){tolNum++;}


    string toString() const{
        if (op == "+" || op == "*" || op == "/" || op == "-") {
            return result + " = " + arg1 + " " + op + " " + arg2;
        } else;

    }


};

class InterCode {


public:
    using nodeType = TreeNode::NodeType ;
    using E_place = std::string;
    using T_place = std::string;
    using F_place = std::string;
    static int tolTempNum;
private:
    ///use a file to save output result.
    ofstream fout;
    vector<Quaternion> quaternionList_;
public:
    const vector<Quaternion> &getQuaternionList_() const;

    void setQuaternionList_(const vector<Quaternion> &quaternionList_);


public:
    void emit(const string& str);
    void emit(const Quaternion& quaternion);

    string newTemp();
    E_place genExpression(TreeNode* node);
    void genAssignment(TreeNode* node);
    T_place genTerm(TreeNode* node);
    F_place genFactor(TreeNode* node);

    void genBinaryOp();
    void genComment(const string& info);
    void showQuaternionList();

};


#endif //COMPILER_INTERCODE_H
