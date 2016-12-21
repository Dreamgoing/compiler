//
// Created by 王若璇 on 16/11/3.
//

#ifndef SEEDCUP_ERROR_H
#define SEEDCUP_ERROR_H

#include <iostream>
#include "Scanner.h"

using namespace std;
/**
 * @brief 编译错误处理类*/
class Error {
public:
    static void syntaxError();
    static void numberError(const string& error);
    static void syntaxError(const string& tokenName,const int& row);
    static void redeclaration(int row,string type,string name);
    static void typeUndeclaration(int row,string varName);
    static void exceptSyntax(const string& error,const string& exp) noexcept ;
    static void syntaxError(const string& error);

};


#endif //SEEDCUP_ERROR_H
