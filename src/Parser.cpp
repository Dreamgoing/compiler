//
// Created by 王若璇 on 16/12/7.
//

#include "Parser.h"

#define SHOW_PREDICTIVE_PROGRESS


void Parser::initParserTable() noexcept {

    parserTable_ = {

            ///@brief Parser table.

            ///E - ID ->TE'
            {make_pair(Symtype::expression,tokenType::ID),
                    Production({Symtype::multiplicative_expression,Symtype::expression_})},

            ///E - '('->TE'
            {make_pair(Symtype::expression,tokenType::LEFT_PAR),
                    Production({Symtype::multiplicative_expression,Symtype::expression_})},

            ///E' - '+'|'-' ->+TE' @note ADD contains '+' and '-'
            {make_pair(Symtype::expression_,tokenType::ADD),
                    Production({Symtype::additive_operator,Symtype::multiplicative_expression,Symtype::expression_})},

            ///E'- ')'->ε and E' - $->ε
            {make_pair(Symbol::expression_,tokenType::RIGHT_PAR),
                    Production({Symtype::terminal_ε})},
            {make_pair(Symbol::expression_,tokenType::END_MARK),
                    Production({Symtype::terminal_ε})},

            ///T - ID ->FT'
            {make_pair(Symbol::multiplicative_expression,tokenType::ID),
                    Production({Symtype::primary_expression,Symtype::multiplicative_expression_})},

            ///T - '('->FT'
            {make_pair(Symbol::multiplicative_expression,tokenType::LEFT_PAR),
                    Production({Symtype::primary_expression,Symtype::multiplicative_expression_})},

            ///T' - '+'|'-' ->ε
            {make_pair(Symbol::multiplicative_expression_,tokenType::ADD),
                    Production({Symtype::terminal_ε})},

            ///T' - '*'|'/' ->*FT'
            {make_pair(Symbol::multiplicative_expression_,tokenType::MULT),
                        Production({Symtype::multiplicative_operator,Symtype::primary_expression,Symtype::multiplicative_expression_})},


            ///T' - ')'->ε
            {make_pair(Symbol::multiplicative_expression_,tokenType::RIGHT_PAR),
                    Production({Symtype::terminal_ε})},

            ///T' - $-> ε
            {make_pair(Symbol::multiplicative_expression_,tokenType::END_MARK),
                    Production({Symtype::terminal_ε})},

            ///F - ID -> id
            {make_pair(Symbol::primary_expression,tokenType::ID),
                    Production({Symtype::terminal_id})},

            ///F - '(' -> (E)
            {make_pair(Symbol::primary_expression,tokenType::LEFT_PAR),
                    Production({Symtype::terminal_leftpar,Symtype::expression,Symtype::terminal_rightpar})},


            ///E -Num-> TE'
            {make_pair(Symbol::expression,tokenType::BINARY_NUMBER),
                    Production({Symtype::multiplicative_expression,Symtype::expression_})},

            ///T-Num-> FT
            {make_pair(Symbol::multiplicative_expression,tokenType::BINARY_NUMBER),
                    Production({Symtype::primary_expression,Symtype::multiplicative_expression_})},

            ///F -Num-> num;
            {make_pair(Symbol::primary_expression,tokenType::BINARY_NUMBER),
                    Production({Symtype::terminal_double})}

    };

}

const map<pair<Symbol::SymbolType, Scanner::TokenType>, Production> &Parser::getParserTable_() const {
    return parserTable_;
}

void Parser::setParserTable_(const map<pair<Symbol::SymbolType, Scanner::TokenType>, Production> &parserTable_) {
    Parser::parserTable_ = parserTable_;
}


///@todo need test predictiveParse.
bool Parser::predictiveParse() {
    //symStack_.push(Symtype::terminal_end);
    symStack_.push(Symtype::expression);
    Scanner::Token token = nextToken();
#ifdef SHOW_PREDICTIVE_PROGRESS
    cerr<<token.lexeme<<" "<<token.kind<<endl;
#endif
    while(!symStack_.empty()){
        Symtype now = symStack_.top();
        if(Symbol::isterminal(now)){
            if(now==Symbol::SymbolType::terminal_ε){
                symStack_.pop();

                continue;
            }

            if(now==tokenToSymbol(fixType_(token.kind))){ ///predicted outcome
                ///@todo solve and output Token,to set symbolType and tokenType the same only for terminal symbol.
#ifdef SHOW_PREDICTIVE_PROGRESS
                cerr<<"( "<<token.lexeme<<" , "<<token.kind<<" )"<<endl;
#endif
                token = nextToken();

                symStack_.pop(); ///pop now.
            }
        } else{
            ///now is non-terminal
            parserIt_ = parserTable_.find(make_pair(now,fixType_(token.kind)));
            if(parserIt_!=parserTable_.end()){
                ///find a grammar,pop now.
//                assert(0);
                symStack_.pop();

                ///push symbols of Production, last first.
                for(vector<Symbol::SymbolType >::reverse_iterator
                            rit = parserIt_->second.grammar.rbegin(); rit!=parserIt_->second.grammar.rend();++rit){
                    symStack_.push(*rit);
                }

            } else{

                ///solve error information.
                if(token.kind==Scanner::TokenType::ENDOFFILE){
                    break;
                }
                Error::syntaxError();
                cerr<<"info: "<<token.lexeme<<" "<<token.kind<<endl;
                //cerr<<Symbol::SymbolType::terminal_ε<<endl;
                ///@note syntaxError abort
                //assert(0);

                break;

            }


        }
    }
    if(Symbol::SymbolType ::terminal_end==tokenToSymbol(token.kind) ){
        return true;
    } else{
        Error::syntaxError(token.lexeme,token.row);
        return false;
    }
}

Parser::Symtype Parser::tokenToSymbol(const Parser::tokenType &type) {

    ///use static_cast implement but it seems no safe sometimes.
    if(type==tokenType::SUB){
        return static_cast<Symtype> (tokenType::ADD);
    }else if(type==tokenType::DIV){
        return static_cast<Symtype> (tokenType::MULT);
    }
    else{
        return static_cast<Symtype>  (type);
    }

}

void Parser::setSourcefile(const string &path) {
    while (!lhsBuffer_.empty()){
        lhsBuffer_.pop_back();
    }
    while (!rhsBuffer_.empty()){
        rhsBuffer_.pop_back();
    }
    scanner_.cleanUp();
    scanner_.openFile(path);
}

Parser::tokenType Parser::fixType_(const Parser::tokenType &type) {
    if(type==tokenType::SUB){
        return tokenType::ADD;
    }else if(type==tokenType::DIV){
        return tokenType::MULT;
    } else{
        return type;
    }
}

Parser::Token Parser::nextToken() {

    Token res; ///local variable
    Token pre;
    if(!lhsBuffer_.empty()){
        pre = lhsBuffer_.back();
    }
    if(rhsBuffer_.empty()){
        lhsBuffer_.push_back(scanner_.nextToken());
        res = lhsBuffer_.back();
        ///set the max size of lhsBuffer_ is 10.
        if(lhsBuffer_.size()>10){
            lhsBuffer_.pop_front();
        }
    } else{
        res = rhsBuffer_.front();
        rhsBuffer_.pop_front();
        lhsBuffer_.push_back(res);
    }
    Token tmp;
    if(res.kind==tokenType::BINARY_NUMBER){
        if(res.lexeme[0]=='+'||res.lexeme[0]=='-'){
            if(pre.kind==tokenType::ID||pre.kind==tokenType::BINARY_NUMBER){
                lhsBuffer_.pop_back();
                tmp.lexeme=res.lexeme.substr(0,1);
                tmp.kind = res.lexeme[0]=='+'?tokenType::ADD:tokenType::SUB;
                tmp.row = res.row;
                tmp.pos = res.pos;
                lhsBuffer_.push_back(tmp);
                res.lexeme = res.lexeme.substr(1,res.lexeme.length());
                rhsBuffer_.push_back(res);
                return tmp;
            }
        }
    }
    return res;
}

void Parser::rollbackToken() noexcept (false){
    Token res;
    if(lhsBuffer_.size()==0){
        ///@note throw an exception.
        throw "Nothing has been output from scanner";
    } else{
        auto token = lhsBuffer_.back();
        lhsBuffer_.pop_back();
        rhsBuffer_.push_front(token);
    }

}

