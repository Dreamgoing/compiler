//
// Created by 王若璇 on 16/12/14.
//

#include "RecDesParser.h"


///@todo can use c++ design pattern Strategy pattern.

/**
 * symbol: < x >  x appear once
 *         { x }  x appear more than zero
 *         [ x ]  x appear once or not appear
 * */
pair<bool, int> mystringToInt(const string &str) noexcept(false) {
    int res;
    istringstream istr{str};
//    throw "exp";
    if (!(istr >> res)) {
        assert(0);
        throw "type conversion failed";
    }
    return make_pair(istr.eof(), res);


}

pair<bool, double> mystringToDouble(const string &str) noexcept(false) {
    double res;
    istringstream istr{str};
    if (!(istr >> res)) {
        throw "type conversion failed";
    }
    return make_pair(istr.eof(), res);
}

void RecDesParser::recusiveDescentParse() {
    this->ast.setRoot(progress());
}


///@brief Progress ::= main()<statementBlock>
TreeNode *RecDesParser::progress() {
    TreeNode *node = new TreeNode;

    ///set the node type.
    Scanner::Token token = this->nextToken();
//    cout<<token.lexeme<<token.kind<<endl;
    if (token.kind != Scanner::TokenType::MAIN) {
        ///solve the syntax error.
        Error::exceptSyntax(token.lexeme, "main");
    } else {
        if (this->nextToken().kind == tokenType::LEFT_PAR &&
            this->nextToken().kind == tokenType::RIGHT_PAR) {
            ///ensure the syntax correct.
            node->terminal = true;
            //node->key = token.lexeme;
            node->kind = nodeType::MAIN;
            node->token = token;
            node->addChild(statementBlock());

        } else {

            ///solve the syntax error.
            Error::syntaxError("symbol format error!");
        }
    }
    return node;
}

///@brief statementBlock ::= '{' <statements> '}'
TreeNode *RecDesParser::statementBlock() {
    TreeNode *node = new TreeNode;
    Scanner::Token token = this->nextToken();
    if (token.kind == tokenType::LEFT_BLOCK) {
        ///ensure the syntax correct.
        node->kind = nodeType::STATEMENT_BLOCK;
        node->addChild(statements());

//        {
//            cout<<"** "<<this->nextToken().lexeme<<endl;
//            rollbackToken();
//        }
        if (this->nextToken().kind != tokenType::RIGHT_BLOCK) {
            ///right parenthesis missing
            cerr<<token.row<<" row"<<endl;
            Error::exceptSyntax("missing right block", "}");
        }
    }
    return node;
}

///@brief statements ::= statement { ;<statement> };
TreeNode *RecDesParser::statements() {
    TreeNode *node = new TreeNode;
    TreeNode *child = nullptr;
    bool flag = false;
    do {
        child = statement();
        if (child != nullptr) {
            flag = true;
            node->addChild(child);
            //child = nullptr;
            if (this->nextToken().kind != tokenType::SEMICOLON) {

                cerr<<this->nextToken().row<<" row"<<endl;
                rollbackToken();
                Error::exceptSyntax("missing semicolon ';' ", " symbol ';' ");
            }
        }
    } while (child != nullptr);
    if (flag) {
        node->kind = nodeType::STATEMENTS;
        return node;
    } else {
        delete node;
        return nullptr;
    }
}

///@brief statement ::= assignStatement | selectionStatement | loopStatement
TreeNode *RecDesParser::statement() {
    TreeNode *node = nullptr;

    ///look ahead one token.
    Scanner::Token token = this->nextToken();
    this->rollbackToken();
    if (token.kind == tokenType::ID) {
        node = assignStatement();
        node->kind = nodeType::ASSIGN_STATEMENT;
    } else if (token.kind == tokenType::DO) {
        node = do_whileStatement();
        node->kind = nodeType::DO_WHILE_STATEMENT;
    } else if (token.kind == tokenType::IF) {
        node = selectionStatement();
        node->kind = nodeType::SELECTION_STATEMENT;
    } else if(token.kind == tokenType::WHILE){
        node = whileStatement();
        node->kind = nodeType::WHILE_STATEMENT;
    } else{
        //        cout<<token.lexeme<<endl;

//        Error::syntaxError("empty statement!");
    }
    return node;
}

///@brief assignStatement ::= ID '=' <expression>
TreeNode *RecDesParser::assignStatement() {
    TreeNode *node = new TreeNode;
    node->kind = nodeType::ASSIGN_STATEMENT;
    node->addChild(id());
    Scanner::Token token = this->nextToken();
    if (token.kind != tokenType::ASSIGN) {
        Error::syntaxError("irregular assignStatement");
    }
    TreeNode *tmp = new TreeNode;
    tmp->kind = nodeType::ASSIGN;
    tmp->token = token;
    tmp->terminal = true;
    node->addChild(tmp);
    node->addChild(expression());
    return node;
}

///@brief loopStatement ::= do_whileStatement | whileStatement | forStatement
///@note more strong function.
TreeNode *RecDesParser::loopStatement() {
    TreeNode *node = nullptr;

    Scanner::Token token = this->nextToken();
    rollbackToken();
    if (token.kind == tokenType::DO) {
        node = do_whileStatement();
    } else if (token.kind == tokenType::WHILE) {
        node = whileStatement();
    } else if (/*(token.kind==tokenType::FOR*/true) {
//        node = forStatement();
    } else {
        Error::syntaxError("irregular loopStatement");
    }
    return node;
}

///@brief do_whileStatement ::= do <statementBlock> while ( <condition> )
TreeNode *RecDesParser::do_whileStatement() {
    TreeNode *node;
    if (nextToken().kind == tokenType::DO) {
        node = new TreeNode;
        node->kind = nodeType::DO_WHILE_STATEMENT;
        node->addChild(statementBlock());
        if (nextToken().kind == tokenType::WHILE) {
            node->addChild(parCondition());
        } else {
            rollbackToken();
            Error::exceptSyntax("missing while_condition", "while");

        }
    } else {
        Error::syntaxError("empty do_whileStatement");
    }
    return node;
}

///@brief whileStatement ::= while ( <condition> ) <statementBlock>
TreeNode *RecDesParser::whileStatement() {
    TreeNode *node;
    if(nextToken().kind==tokenType::WHILE){
        node = new TreeNode;
        node->kind = nodeType::WHILE_STATEMENT;
        node->addChild(parCondition());
        node->addChild(statementBlock());
    } else{
        rollbackToken();
        Error::exceptSyntax("missing key_word ","while");
    }
    return node;
}

///@brief selectionStatement ::= if ( <condition> ) <statementBlock> [else <statementBlock>]
TreeNode *RecDesParser::selectionStatement() {
    TreeNode *node = new TreeNode;

    node->kind = nodeType::SELECTION_STATEMENT;
    if (nextToken().kind == tokenType::IF) {
        //cout<<"if"<<endl;
        node->addChild(parCondition());

        node->addChild(statementBlock());
    } else {
        rollbackToken();
        Error::syntaxError("empty if condition");
    }
    if (nextToken().kind == tokenType::ELSE) {
        node->addChild(statementBlock());
    } else {
        rollbackToken();
    }
    return node;
}

TreeNode *RecDesParser::parCondition() {
    TreeNode *node = nullptr;
    if (nextToken().kind == tokenType::LEFT_PAR) {
        node = condition();
        if (nextToken().kind != tokenType::RIGHT_PAR) {
            rollbackToken();
            Error::exceptSyntax("missing right parenthesis", ")");
        }
    } else {
        ///rollback twice
        rollbackToken();
        Error::syntaxError("irregular par_condition");
    }
    return node;
}

TreeNode *RecDesParser::elseStatement() {
    return nullptr;
}

///@brief condition ::= <expression> <relationalOp> <expression>
TreeNode *RecDesParser::condition() {
    TreeNode *node = new TreeNode;
    node->kind = nodeType::CONDITION;
    node->addChild(expression());
    node->addChild(relationalOp());
    node->addChild(expression());
    return node;
}

///@brief expression ::= <term> {+ <term> | - <term>}
TreeNode *RecDesParser::expression() {
    TreeNode *node = new TreeNode;
    node->kind = nodeType::EXPRESSION;
    TreeNode *child = term();
    node->addChild(child);
    Scanner::Token token;
    while (!(token = this->nextToken()).empty() && (token.kind == tokenType::ADD || token.kind == tokenType::SUB)) {
        TreeNode *tmp = new TreeNode;
        tmp->kind = token.kind == tokenType::ADD ? nodeType::ADD : nodeType::SUB;

        ///@note not contain more detail about token.
        tmp->token = token;
        tmp->terminal = true;
        node->addChild(tmp);
        node->addChild(term());
    }
    rollbackToken();
    return node;
}

///@brief term ::= <factor> {* <factor> | / <factor>}
TreeNode *RecDesParser::term() {
    TreeNode *node = new TreeNode;
    node->kind = nodeType::TERM;
    TreeNode *child = factor();
    node->addChild(child);
    Scanner::Token token;
    while (!(token = nextToken()).empty() && (token.kind == tokenType::MULT || token.kind == tokenType::DIV)) {
        TreeNode *tmp = new TreeNode;
        tmp->kind = token.kind == tokenType::MULT ? nodeType::MULT : nodeType::DIV;
        tmp->token = token;
        tmp->terminal = true;
        node->addChild(tmp);
        node->addChild(factor());
    }
    rollbackToken();
    return node;
}

///@brief factor ::= ID | NUM | (expression)
TreeNode *RecDesParser::factor() {
    TreeNode *node = nullptr;

    ///look ahead one token.
    Scanner::Token token = this->nextToken();
    this->rollbackToken();
    if (token.kind == tokenType::ID) {
        node = id();
    } else if (token.kind == tokenType::BINARY_NUMBER) {
        node = num();
    } else if (token.kind == tokenType::LEFT_PAR) {

        ///ignore the left parenthesis.
        this->nextToken();
        node = expression();

        ///solve syntax error.
        if (this->nextToken().kind != tokenType::RIGHT_PAR) {
            Error::syntaxError("irregular expression miss right parenthesis.");
        }
    }
    return node;
}

TreeNode *RecDesParser::num() {
    Scanner::Token token = this->nextToken();
    TreeNode *node = new TreeNode;
    if (token.kind == tokenType::BINARY_NUMBER) {

        ///this function may throw exception.
        node->terminal = true;
        node->token = token;
        try {
            pair<bool, double> tmpd = mystringToDouble(token.lexeme);
            pair<bool, int> tmpi = mystringToInt(token.lexeme);
            ///store tmpd or tmpi in node.
            if (tmpd.first) {
                node->kind = nodeType::DOUBLE_NUMBER;
//                node->value.dvalue = tmpd.second;
            } else if (tmpi.first) {
                node->kind = nodeType::INT_NUMBER;
            } else {
                Error::syntaxError("type conversion error !");
            }
        } catch (const char *s) {
            cerr << "exception: " << s << endl;
        }

    } else {

        ///rollback and syntax error.
        this->rollbackToken();
        Error::syntaxError("irregular number !");
    }
    return node;
}


TreeNode *RecDesParser::id() {
    TreeNode *node = nullptr;
    Scanner::Token token = this->nextToken();
    if (token.kind == tokenType::ID) {
        node = new TreeNode;
        node->kind = nodeType::ID;
        node->terminal = true;
        node->token = token;
    } else {
        Error::syntaxError("no vivid id");
    }
    return node;
}

TreeNode *RecDesParser::relationalOp() {
    TreeNode *node = new TreeNode;
    Scanner::Token token = this->nextToken();
    node->token = token;
    if (token.kind == tokenType::SMALLER) {
        node->kind = nodeType::SMALLER;
    } else if (token.kind == tokenType::SMALLER_EQUAL) {
        node->kind = nodeType::SMALLER_EQUAL;
    } else if (token.kind == tokenType::GREATER) {
        node->kind = nodeType::GREATER;
    } else if (token.kind == tokenType::GREATER_EQUAL) {
        node->kind = nodeType::GREATER_EQUAL;
    } else if (token.kind == tokenType::EQUAL) {
        node->kind = nodeType::EQUAL;
    } else if (token.kind == tokenType::NON_EQUAL) {
        node->kind = nodeType::NON_EQUAL;
    } else {
        delete node;
        node = nullptr;
        this->rollbackToken();
        Error::syntaxError("irregular relational operator !");
    }
    return node;
}









