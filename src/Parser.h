//
// Created by 王若璇 on 16/12/7.
//

#ifndef COMPILER_PARSER_H
#define COMPILER_PARSER_H

#include "AST.h"
#include "Symbol.h"
#include "Scanner.h"
#include "Error.h"
#include <stack>
#include <map>
#include <unordered_map>
#include <vector>
#include <deque>


using namespace std;

///forward defined RecDesParser
//class RecDesParser;

///@brief grammar rules class.
class Production {
public:
    vector<Symbol::SymbolType> grammar;


public:
    Production() {}

    Production(const vector<Symbol::SymbolType> &grammar) : grammar(grammar) {}

    void addSymbol(Symbol::SymbolType symbol) {
        grammar.push_back(symbol);
    }
};


/**
 * @brief Parser class
 * @pram
 *      primary_expression                          -ok
        expression                                  -ok
        multiplicative_expression                   -ok
        additive_expression
        relational_expression
        equality_expression
        assignment_expression                       -ok

        assignment_operator  <=> '='
        multiplicative_operator <=> '*' '/'
        additive_operator <=> '+' '-'


 * @details
 *
 *         expression -> expression + multiplicative_expression | multiplicative_expression
 *         multiplicative_expression -> multiplicative_expression  multiplicative_operator primary_expression
 *                                      | primary_expression
 *         primary_expression -> id | num | (expression)
 *
 *
 *
 *         assignment_expression -> primary_expression assignment_operator additive_expression
 *
 *
 *
 *
 * @example E -> TE'
 *          E -> +TE' | ε
 *          T -> FT'
 *          T'-> *FT' | ε
 *          F -> (E) | id | num
 * */

/**
 * @brief specialize std::less to implement user defined map.
 * The advantage of this is that it will be picked by std::map "by default",
 * and yet you do not expose operator< to client code otherwise.*/
namespace std {
    template<>
    struct less<pair<Symbol::SymbolType, Scanner::TokenType> > {
        bool operator()(const pair<Symbol::SymbolType, Scanner::TokenType> &lhs,
                        const pair<Symbol::SymbolType, Scanner::TokenType> &rhs) const {
            if (lhs.first != rhs.first) {
                return lhs.first < rhs.first;
            } else {
                return lhs.second < rhs.second;
            }
        }
    };
}


///@todo can use friend class to implement
class Parser {
public:

    ///@brief typedef and friend class.
    ///@todo to think the relationship between the Parser class and ResDesParser class
    ///@todo learn and use design pattern method.

    ///@note friend class provide interface to this class and
    /// have access to this class's private member.
    //friend class RecDesParser;
    typedef Symbol::SymbolType Symtype;
//    typedef Scanner::TokenType  tokenType;
///@note another way to redefine type just like typedef.
    using tokenType = Scanner::TokenType;
    using Token = Scanner::Token;
    AST ast;
private:

    ///@note also can implement this use static instance.
    Scanner scanner_;
    deque<Scanner::Token> lhsBuffer_;
    deque<Scanner::Token> rhsBuffer_;

    map<pair<Symbol::SymbolType, Scanner::TokenType>, Production> parserTable_;
    map<pair<Symbol::SymbolType, Scanner::TokenType>, Production>::iterator parserIt_;
    stack<Symtype> symStack_;

public:
    const map<pair<Symbol::SymbolType, Scanner::TokenType>, Production> &getParserTable_() const;

    void setParserTable_(const map<pair<Symbol::SymbolType, Scanner::TokenType>, Production> &parserTable_);
    ///unordered_map need user defined hash function.

private:
    Symtype tokenToSymbol(const tokenType &type);

    tokenType fixType_(const tokenType &type);

public:


    bool predictiveParse();

    ///@note noexcept equal noexcept(true) this function is declared to not throw any exceptions.

    ///@note only predictiveParse() need to call this function.
    void initParserTable() noexcept;

    void setSourcefile(const string &path);

    Token nextToken();

    void rollbackToken() noexcept(false);

};

/**
 *  @brief specialize std::tr1::hash<Key> with Key = std::pair<int, int>
 *  before declaring tr1::unordered_map<Pair,Value>;
 *
 *
 *  */



#endif //COMPILER_PARSER_H
