//
// Created by 王若璇 on 16/12/22.
//

#ifndef COMPILER_INTERCODE_H
#define COMPILER_INTERCODE_H

#define SHOW_ROW_NUM
#define SHOW_LABEL

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
    int row;
    int chain{-1};
    Quaternion(const string &op,
               const string &arg1,
               const string &arg2,
               const string &result) : op(op),
                                       arg1(arg1),
                                       arg2(arg2),
                                       result(result)
    {tolNum++;row=tolNum;isCondition = false;index_ = row-1;}

    string result;
    bool isCondition{false};
    bool assigned{false};
    bool isJump{false};
    int trueList{-1};
    int falseList{-1};
    int beginCode{-1};


    static int tolLabel;
    static int tolNum;

private:
    int index_;
public:
    int getIndex_() const;

    void setIndex_(int index_);

public:


    Quaternion(){tolNum++; row=tolNum;isCondition = false;index_ = row-1;}
    ///@todo please use share_ptr
    ~Quaternion(){/*cerr<<"tolnum-- "<<tolNum<<endl;tolNum--;*/};


    string toString() const{
        if (op == "+" || op == "*" || op == "/" || op == "-") {
            return result + " = " + arg1 + " " + op + " " + arg2;
        } else if(op=="="){
            return result + " = "+arg1;
        } else if(isCondition){
            ///assigned or has't assigned
            if(assigned){
                return "if "+arg1+" goto "+result;
            } else{
                return "if "+arg1+" goto 0";
            }
        } else if(isJump){
            if(assigned){
                return "goto "+result;
            } else{
                return "goto 0";
            }
        } else{
            return result;
        }

    }


};

class InterCode {


public:
    using nodeType = TreeNode::NodeType ;
    using E_place = std::string;
    using T_place = std::string;
    using F_place = std::string;
    using codeIndex = int;
    static int tolTempNum;
private:
    ///use a file to save output result.
    ofstream fout;
    vector<Quaternion> quaternionList_;
public:
    const vector<Quaternion> &getQuaternionList_() const;

    void setQuaternionList_(const vector<Quaternion> &quaternionList_);


private:
    void bathPatch_(codeIndex index,int pos);
    codeIndex merge_(codeIndex p1,codeIndex p2);
public:

    InterCode();
    void emit(const string& str);
    void emit(const Quaternion& quaternion);


    string newTemp();
    E_place genExpression(TreeNode* node);

    ///@return value has't been decided.
    void genAssignment(TreeNode* node);

    T_place genTerm(TreeNode* node);
    F_place genFactor(TreeNode* node);
    codeIndex genCondition(TreeNode* node);
    codeIndex genSelectionStatement(TreeNode* node);
    codeIndex genStatement(TreeNode* node);
    codeIndex genStatements(TreeNode* node);
    codeIndex genWhileStatement(TreeNode* node);
    codeIndex genDoStatement(TreeNode* node);

    ///@brief statement chain
    codeIndex genStatementBlock(TreeNode* node);
    void genProgress(TreeNode* node);
//    void genComment(const string& info);
    void showQuaternionList();

};


#endif //COMPILER_INTERCODE_H
