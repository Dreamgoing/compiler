//
// Created by 王若璇 on 16/10/26.
//

/*
 * Scanner 类用来提取源代码中的token
 * 没有实现检测是否合法的功能
 * */

#ifndef SEEDCUP_SCANNER_H
#define SEEDCUP_SCANNER_H

//#define SHOW_FIN
//#define DEBUG_TOKEN

#include <string>
#include <fstream>
#include <deque>
#include <set>
#include <iostream>
#include <cassert>
#include <map>
#include "Error.h"



using namespace std;


class Scanner {
private:
    const static unsigned INFROW = 0x3f3f3f3f;

    enum State { //各种状态
        START_STATE,
        INT_STATE,
        ID_STATE,
        SYMBOL_STATE,
        CHAR_STATE,
        STRING_STATE,
        ESCAPE_STRING_STATE,
        LINE_COMMENT_STATE,
        BLOCK_COMMENT_STATE,
        PREEND_BLOCK_COMMENT_STATE,
        DONE_STATE,
        ERROR_STATE,
        DOUBLE_STATE

    };
public:
    set<string> keyWords;
    set<string> symbols;
    enum TokenType {
        KEY_WORD,
        ID,

        BOOL,

        SYMBOL,
        NONE,
        ERROR,
        ENDOFFILE,
        MAIN = 1,
        INT = 2,
        FLOAT = 3,
        DOUBLE = 20,
        CHAR = 5,
        IF = 6,
        ELSE = 7,
        DO = 8,
        WHILE = 9,
        STRING = 10,
        BINARY_NUMBER = 4,
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
        HASH_MARK = 38
        ///@todo ( +|-|ε ) dd*(.dd* | ε)( e ( +|-|ε ) dd*|ε)
    };

    struct Token {
        TokenType kind; //token 的类型
        string lexeme; //token 的值
        unsigned int row; //当前的行数
        unsigned int pos; //当前行的位置
        Token() {
            kind = NONE;
            lexeme.clear();
            row = INFROW;
        }
    };

    void initKeyWords();

    void initSymbols();

private:
    string lineBuffer; //缓冲行，保存程序的某一行数据
    unsigned int bufferPos; //缓冲行的索引
    unsigned int row; //当前的行号
    ifstream fin;
    Token pre;
    map<string,TokenType > keyMap;

private:

    void initKeyMap();

    char nextChar();

    void rollBack();

    TokenType searchReserved(const string &s);

    void setTokenType(Token &rhs, TokenType nowType, unsigned int nowRow, unsigned int nowPos);

    void setTokenType(Token &rhs);
public:
    Scanner();

    void openFile(const string &filename);

    void closeFile();

    Token nextToken();

    unsigned int getRow();

    string getLineBuffer();

    void resetRow();

    void cleanUp();

#ifdef SHOW_FIN
    void showFin();
#endif
};


#endif //SEEDCUP_SCANNER_H
