//
// Created by 王若璇 on 16/10/26.
//

#include "Scanner.h"


void Scanner::initKeyWords() {
    /**
     * @note to use initialize_list
    keyWords.clear();
    keyWords.insert("int");
    keyWords.insert("printf");
    keyWords.insert("void");
    keyWords.insert("if");
    keyWords.insert("else");
    keyWords.insert("else if");
    keyWords.insert("return");
    keyWords.insert("while");
    keyWords.insert("break");
    keyWords.insert("do");
    keyWords.insert("for");
     * */


    keyWords = {{"int"},
                {"printf"},
                {"void"},
                {"if"},
                {"else"},
                {"else"},
                {"else if"},
                {"return"},
                {"while"},
                {"break"},
                {"do"},
                {"for"}
    };
}

void Scanner::initSymbols() {
    symbols.clear();
    symbols.insert("{");
    symbols.insert("}");

    symbols.insert("(");
    symbols.insert(")");

    symbols.insert("[");
    symbols.insert("]");

    symbols.insert(";");
    symbols.insert(".");
    symbols.insert(",");

    symbols.insert("+");
    symbols.insert("-");
    symbols.insert("*");
    symbols.insert("/");

    symbols.insert(">");
    symbols.insert(">=");
    symbols.insert("<");
    symbols.insert("<=");
    symbols.insert("=");
    symbols.insert("==");
    symbols.insert("!=");

    symbols.insert("/*");
    symbols.insert("*/");
    symbols.insert("//");

    symbols.insert("++");
    symbols.insert("--");

    symbols.insert("|");
    symbols.insert("^");
    symbols.insert("~");
    symbols.insert("!");

    symbols.insert("&&");
    symbols.insert("||");

    symbols.insert("#");


}

char Scanner::nextChar() {
    if (bufferPos >= lineBuffer.length()) {
        row++;
        getline(fin, lineBuffer);
        lineBuffer += '\n';
        //bufferPos = 0;
        //cerr<<"row "<<row<<" "<<lineBuffer.size()<<endl;
#ifdef DEBUG_TOKEN
        cerr<<"row "<<row<<" "<<lineBuffer<<endl;
#endif
        if (!fin.fail()) {
            bufferPos = 0;
            return lineBuffer[bufferPos++];
        } else {
            //cerr<<"ok"<<endl;
            return EOF;
        }

    } else {
        return lineBuffer[bufferPos++];
    }
}

void Scanner::rollBack() {
    assert(bufferPos > 0);
    bufferPos--;
}

Scanner::TokenType Scanner::searchReserved(const string &s) {
    if (keyWords.find(s) != keyWords.end()) {
        return KEY_WORD;
    } else {
        return ID;
    }
}

void Scanner::openFile(const string &filename) { //在这个地方注意exit 和 return的区别。

    if (filename.empty()) {
        std::cerr << "filename is Empty!" << endl;
        return;
    }
    string suffix_txt(filename.substr(filename.length() - 4, 4));;
    string suffix_c(filename.substr(filename.length() - 2, 2));
    if (suffix_c == ".c" || suffix_txt == ".txt") {
        fin.open(filename);
        if (fin.fail() || !fin.is_open()) {
            cerr << "file " << filename << " does not exit" << endl;
            return;
        }
    } else {
        std::cerr << "Error :" << filename << " no a valid filename" << endl;
    }


}

Scanner::Scanner() {
    row = 0;
    bufferPos = 0;
    initKeyWords();
    initSymbols();
    initKeyMap();

}

void Scanner::closeFile() {
    fin.close();
}


Scanner::Token Scanner::nextToken() {
    Token resToken;
    resToken.lexeme.clear();
    State nowState = START_STATE;
    while (nowState != DONE_STATE) {
        char nowChar = nextChar();
        //cout<<nowChar;
#ifdef DEBUG_TOKEN
        cout<<nowChar<<" --- "<<endl;
#endif
        if (nowChar == EOF) {
            //cout<<"ok"<<endl;
            resToken.kind = ENDOFFILE;
            break;

        }
        //cout<<resToken.lexeme<<" ";
        switch (nowState) {
            case START_STATE:
                if (nowChar == '\t' || nowChar == '\n' || nowChar == ' ' || nowChar == '\r' || nowChar == '\b') {

                } else if (isalpha(nowChar) || nowChar == '_') {  //处理标识符和关键字
                    nowState = ID_STATE;
                    resToken.lexeme += nowChar;
                    setTokenType(resToken, ID, row, bufferPos);
                } else if (isdigit(nowChar)) { //处理整型数字
                    nowState = INT_STATE;
                    resToken.lexeme += nowChar;
                    setTokenType(resToken, INT, row, bufferPos);
                } else if (symbols.find({nowChar}) != symbols.end()) {//处理符号

                    nowState = SYMBOL_STATE;
                    resToken.lexeme += nowChar;
                    setTokenType(resToken, SYMBOL, row, bufferPos);

                } else if (nowChar == '"') {                          //处理字符串
                    nowState = STRING_STATE;
                    setTokenType(resToken, STRING, row, bufferPos);
                } else if (nowChar == '\'') {                         //处理单个字符
                    nowState = CHAR_STATE;
                    setTokenType(resToken, CHAR, row, bufferPos);
                } else {
                    nowState = ERROR_STATE;                       //处理错误格式
                    setTokenType(resToken, ERROR, row, bufferPos);
                    resToken.lexeme += nowChar;
                }
                break;
            case ID_STATE:
                //cout<<resToken.lexeme<<endl;
                if (isdigit(nowChar) || isalpha(nowChar) || nowChar == '_') {
                    resToken.lexeme += nowChar;
                } else {
                    nowState = DONE_STATE;
                    rollBack();
                    if (searchReserved(resToken.lexeme) == KEY_WORD) {
                        resToken.kind = KEY_WORD;
                        //cout<<resToken.lexeme<<" --"<<endl;
                    } else {
                        resToken.kind = ID;
                    }
                }
                break;
            case INT_STATE:
                if (isdigit(nowChar)) {
                    resToken.lexeme += nowChar;
                } else if(nowChar=='.'||nowChar=='e'){
                    rollBack();
                    //resToken.lexeme += nowChar;
                    nowState = DOUBLE_STATE;
                } else {
                    rollBack();
                    resToken.kind = Scanner::INT;
                    nowState = DONE_STATE;
                }
                break;
            case STRING_STATE:
                if (nowChar == '"') {
                    nowState = DONE_STATE;
                } else if (nowChar == '\\') {   //转义部分有问题再考虑
                    nowState = ESCAPE_STRING_STATE;
                    resToken.lexeme += nowChar;
                } else {
                    resToken.lexeme += nowChar;
                }
                break;

                //switch 位置顺序不同 编译不通过？
            case ESCAPE_STRING_STATE:
                nowState = STRING_STATE;
                resToken.lexeme.pop_back();
                resToken.lexeme += nowChar;
                break;
            case LINE_COMMENT_STATE:
                if (nowChar == '\n') {
                    nowState = DONE_STATE;
                }
                break;
            case BLOCK_COMMENT_STATE:
                if (nowChar == '*') {
                    nowState = PREEND_BLOCK_COMMENT_STATE;
                    resToken.lexeme += nowChar;
                }
                break;
            case PREEND_BLOCK_COMMENT_STATE:
                if (nowChar == '/') {
                    nowState = DONE_STATE;
                    resToken.lexeme += nowChar;
                }
                break;
                //
            case DOUBLE_STATE:
                setTokenType(resToken, DOUBLE, row, bufferPos);
                if(nowChar=='.'){
                    resToken.lexeme+=nowChar;
                    nowChar = nextChar();
                    if(!isdigit(nowChar)){
                        Error::numberError("number format error");
                    }
                    while (isdigit(nowChar)){
                        resToken.lexeme +=nowChar;
                        nowChar = nextChar();
                    }
                }
                // cerr<<" now "<<nowChar<<" "<<resToken.lexeme<<endl;
                if(nowChar=='e'){
                    resToken.lexeme+=nowChar;
                    nowChar = nextChar();
                    if(nowChar=='+'||nowChar=='-'){
                        resToken.lexeme+=nowChar;
                        nowChar = nextChar();
                    }
                    if(!isdigit(nowChar)){
                        Error::numberError("number format error");
                    }
                    while (isdigit(nowChar)){
                        resToken.lexeme +=nowChar;
                        nowChar = nextChar();
                    }
                    rollBack();
                } else{
                    //cout<<"ok"<<endl;
                    rollBack();
                }
                nowState = DONE_STATE;
                break;

            case SYMBOL_STATE:  //符号分为单符号和双符号
                string pre = resToken.lexeme;
                /*处理其它的符号*/
                if (nowChar == '=') {
                    if (!pre.empty()) {   //双符号
                        resToken.lexeme += nowChar;
                        nowState = DONE_STATE;
                    }
                } else if (nowChar == '/'&&pre == "/") {
                    nowState = LINE_COMMENT_STATE;
                    resToken.lexeme += nowChar;
                } else if (nowChar == '*'&&pre == "/") {
                    nowState = BLOCK_COMMENT_STATE;
                    resToken.lexeme += nowChar;
                } else if (nowChar == '|' && pre == "|") {
                    nowState = DONE_STATE;
                    resToken.lexeme += nowChar;
                } else if (nowChar == '&' && pre == "&") {
                    nowState = DONE_STATE;
                    resToken.lexeme += nowChar;
                } else if(pre=="+"||pre=="-"){
                    if(isdigit(nowChar)){
                        //cout<<tmp<<endl;
                        rollBack();
                        nowState = INT_STATE;
                    } else{
                        rollBack();
                        nowState = DONE_STATE;
                    }
                } else{
                    rollBack();
                    nowState = DONE_STATE;
                }
                break;
                /*@delete
                 * else if (nowChar == '+' && pre == "+") {
                    nowState = DONE_STATE;
                    resToken.lexeme += nowChar;
                } else if (nowChar == '-' && pre == "-") {
                    nowState = DONE_STATE;
                    resToken.lexeme += nowChar;

                } */



        }
    }
    //cerr<<lineBuffer<<" "<<resToken.lexeme<<endl;
    return resToken;
}

void Scanner::resetRow() {
    row = 0;
}

void Scanner::setTokenType(Scanner::Token &rhs, Scanner::TokenType nowType, unsigned int nowRow, unsigned int nowPos) {
    rhs.pos = nowPos;
    rhs.kind = nowType;
    rhs.row = nowRow;
}


unsigned int Scanner::getRow() {
    return row;
}

string Scanner::getLineBuffer() {
    return lineBuffer;
}

void Scanner::setTokenType(Scanner::Token &rhs) {
    switch (rhs.kind){
        case SYMBOL:

            break;
    }
}

void Scanner::initKeyMap() {
    keyMap = {
            {"main",MAIN},
            {"int",INT},
            {"float",FLOAT},
            {"double",DOUBLE},
            {"char",CHAR},
            {"if",IF},
            {"else",ELSE},
            {"do",DO},
            {"while",WHILE},
            {"l(l|d)*",STRING},
            {"( +|-|ε ) dd*(.dd* | ε)( e ( +|-|ε ) dd*|ε) ",BINARY_NUMBER},
            {"=",ASSIGN},
            {"+",ADD},
            {"-",SUB},
            {"*",MULT},
            {"/",DIV},
            {"(",LEFT_PAR},
            {")",RIGHT_BLOCK},
            {"{",LEFT_BLOCK},
            {"}",RIGHT_BLOCK},
            {",",COMMA},
            {";",SEMICOLON},
            {">",GREATER},
            {">=",GREATER_EQUAL},
            {"<",SMALLER},
            {"<=",SMALLER_EQUAL},
            {"==",EQUAL},
            {"!=",NON_EQUAL},
            {"#",HASH_MARK}
    };
}

void Scanner::cleanUp() {
    bufferPos = 0;
    row = 0;
    closeFile();
    ///@todo try to use try catch to solve exception.
}


#ifdef SHOW_FIN
void Scanner::showFin() {
    while (!fin.eof()){
        string str;
        getline(fin,str);
        cout<<str<<endl;
    }
}
#endif
