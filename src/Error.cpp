//
// Created by 王若璇 on 16/11/3.
//

#include "Error.h"

void Error::syntaxError() {
    cerr<<"Error: syntax error!"<<endl;
}



void Error::redeclaration(int row, string type, string name) {
    cerr<<"Error: in line "<<row<<" : redeclaration of '"<<type<<" "<<name<<"'"<<endl;
}

void Error::typeUndeclaration(int row, string varName) {
    cerr<<"Error: in line"<<row<<" : '"<<varName<<"' does not declared in this scope"<<endl;

}

void Error::numberError(const string &error) {
    cerr<<"Error: "<<error<<endl;
}

void Error::syntaxError(const string &tokenName, const int &row) {
    cerr<<"Error: syntax error! in "<<row<<" row ,"<<tokenName<<endl;
}

void Error::exceptSyntax(const string& error,const string &exp) noexcept {
    cerr<<"Error: in "<<error<<". Syntax Error ! except "<<exp<<endl;
}

void Error::syntaxError(const string &error) {
    cerr<<"Error: "<<error<<endl;
}
