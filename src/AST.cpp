//
// Created by 王若璇 on 16/12/7.
//

#include "AST.h"


///@brief Node getChildren method.
///@return private class member children_
const std::vector<TreeNode *> &TreeNode::getChildren_() const {
    return children_;
}

///@brief Node setChildren method
void TreeNode::setChildren_(const std::vector<TreeNode *> &children_) {
    TreeNode::children_ = children_;
}

void TreeNode::addChild(TreeNode *child) {
    children_.push_back(child);

}

TreeNode::TreeNode() {
    deep = 0;
    children_.clear();
    terminal = false;
}

void TreeNode::showNode() {
    for (int i = 0; i < deep; i++) {
        cout << '-';
    }
    cout << "( " << token.lexeme << " , " << kind << " )" << endl;
}


void AST::initInfoTable_() {

    infoTable_ = {
            {NodeType::MAIN,               "main()"}, /// "main" seem ok too.
            {NodeType::INT,                "int"},
            {NodeType::FLOAT,              "float"},
            {NodeType::DOUBLE,             "double"},
            {NodeType::CHAR,               "char"},
            {NodeType::IF,                 "if"},
            {NodeType::ELSE,               "else"},
            {NodeType::DO,                 "do"},
            {NodeType::WHILE,              "while"},
            {NodeType::ID,                 "ID"},
            {NodeType::BINARY_NUMBER,      "num"},

            {NodeType::ADD,                "+"},
            {NodeType::SUB,                "-"},
            {NodeType::MULT,               "*"},
            {NodeType::DIV,                "/"},
            {NodeType::LEFT_PAR,           "("},
            {NodeType::RIGHT_PAR,          ")"},
            {NodeType::LEFT_BLOCK,         "{"},
            {NodeType::RIGHT_BLOCK,        "}"},
            {NodeType::COMMA,              ","},
            {NodeType::SEMICOLON,          ";"},
            {NodeType::GREATER,            ">"},
            {NodeType::GREATER_EQUAL,      ">="},
            {NodeType::SMALLER,            "<"},
            {NodeType::SMALLER_EQUAL,      "<="},
            {NodeType::EQUAL,              "=="},
            {NodeType::ASSIGN,             "="},
            {NodeType::NON_EQUAL,          "!="},
            {NodeType::HASH_MARK,          "#"},
            {NodeType::BOOL,               "bool"},
            {NodeType::KEY_WORD,           "keyword"},
            {NodeType::SYMBOL,             "symbol"},
            {NodeType::NONE,               "none"},
            {NodeType::ERROR,              "error"},
            {NodeType::END_MARK,           "EOF"},

            {NodeType::PROGRESS,           "progress"},
            {NodeType::STATEMENT,          "statement"},
            {NodeType::STATEMENTS,         "statements"},
            {NodeType::STATEMENT_BLOCK,    "statement_block"},
            {NodeType::ASSIGN_STATEMENT,   "assign_statement"},
            {NodeType::DO_WHILE_STATEMENT, "do_while_statement"},
            {NodeType::IF_CONDITION,       "if_condition"},
            {NodeType::ELSE_STATEMENT,     "else_statement"},
            {NodeType::TERM,               "term"},
            {NodeType::FACTOR,             "factor"},
            {NodeType::EXPRESSION,         "expression"}


    };
}


TreeNode *AST::getRoot() const {
    return root_;
}

void AST::setRoot(TreeNode *root) {
    AST::root_ = root;
}

AST::AST() {
    initInfoTable_();
    root_ = nullptr;

}

void AST::BFSshowAST() const {
    queue<TreeNode *> nodeQueue{};
    nodeQueue.push(root_);
    ///ensure the root_ not nullptr
    assert(root_ != nullptr);
    ///can do exception solve
    while (!nodeQueue.empty()) {
        TreeNode *now = nodeQueue.front();
        nodeQueue.pop();
        cout << '\n';
        now->showNode();
        for (auto it:now->getChildren_()) {
            it->deep = now->deep + 2;
            //cout<<"ok"<<endl;
            nodeQueue.push(it);
        }
    }
}

const map<TreeNode::NodeType, string> &AST::getInfoTable_() const {
    return infoTable_;
}

void AST::setInfoTable_(const map<TreeNode::NodeType, string> &infoTable_) {
    AST::infoTable_ = infoTable_;
}

void AST::DFSshowAST_(TreeNode *node,int deep) {
    if(node== nullptr){
        return;
    }
    for(int i = 0;i<deep;i++){
        cout<<"- - ";
    }
//    cout<<"->";
    showNode(node);
    for(auto it:node->getChildren_()){
        DFSshowAST_(it,deep+1);
    }
}

void AST::showNode(TreeNode *node) {
    cout<<"( ";
    if(!node->terminal){
        cout<<"non-terminal";
    } else{
        if(node->token.lexeme.empty()){
            cout<<"symbol";
        } else{
            cout<<node->token.lexeme;
        }
    }
    cout<<" , "<<infoTable_[node->kind]<<" )"<<endl;

}

void AST::DFSshowAST() {
    DFSshowAST_(root_,0);
}
