//
// Created by 王若璇 on 16/11/3.
//

#ifndef SEEDCUP_ERROR_H
#define SEEDCUP_ERROR_H

#include <iostream>

using namespace std;
/**
 * @brief 编译错误处理类*/
class Error {
public:
    static void syntaxError();
    static void numberError(const string& error);
    /*static void syntaxError(const Scanner::Token& token);*/
    static void redeclaration(int row,string type,string name);
    static void typeUndeclaration(int row,string varName);


};


#endif //SEEDCUP_ERROR_H
