//
// Created by 王若璇 on 16/12/8.
//

#ifndef COMPILER_SYMBOL_H
#define COMPILER_SYMBOL_H


/**
 * @brief Symbol class's one Symbol's type is terminal symbol, other's is non-terminal.
 * */
//#define DECLARE_SYMBOL(name, index) \


class Symbol {
public:

    ///@note the enum type value can't the same.
    enum SymbolType{
        primary_expression, /// -----0
        expression,
        expression_,
        multiplicative_expression,
        multiplicative_expression_,
        additive_expression,
        relational_expression,
        equality_expression,
        assignment_expression, /// ----8 @brief Non-terminal symbol limit.

        additive_operator = 22,
        multiplicative_operator = 24,
        assignment_operator = 21,


        terminal_id = 10,
        terminal_num = 20,
        terminal_double = 20,
        terminal_add = 22,
        terminal_sub = 23,
        terminal_mult = 24,
        terminal_div = 25,
        terminal_leftpar = 26,
        terminal_rightpar = 27,
        terminal_leftblock = 28,
        terminal_rightblock = 29,
        terminal_comma = 30,
        terminal_semincolon = 31,
        terminal_greater = 32,


        terminal_end = 100,
        terminal_ε
    };
public:
    bool isTerminal;

private:

public:
    static bool isterminal(SymbolType type){
        return type>8;
    }
    Symbol(bool isTerminal);
    Symbol();

};

///can use override and final to manager virtual function.
class TerminalSymbol : Symbol{


};
class NonterminalSymbol : Symbol{

};

#endif //COMPILER_SYMBOL_H
