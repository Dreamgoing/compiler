//
// Created by 王若璇 on 16/12/22.
//

#include "InterCode.h"

int Quaternion::tolNum = 0;
int InterCode::tolTempNum;


InterCode::E_place InterCode::genExpression(TreeNode *node) {
    if(node== nullptr||node->getChildren_().empty()){
        return "none";
    }
    E_place e1;
    E_place e2;
    string res;

    ///@note auto pointer don't support inc_op "++".otherwise it will lead to memory error.ls
    for(int i = 0;i<node->getChildren_().size();i++){

        if(i==0){
            e1 = genTerm(node->getChildren_()[0]);
            res = e1;
        } else{
            TreeNode* it = node->getChildren_()[i];
            if(it->kind==nodeType::ADD||it->kind==nodeType::SUB){
                string tmpOp = it->kind==nodeType::ADD? "+" :"-";
                i++;
                e2 = genTerm(node->getChildren_()[i]);
                res = newTemp();

                emit(Quaternion(tmpOp,e1,e2,res));
                e1 = res;
            }
        }
    }
    return res;

}


void InterCode::emit(const Quaternion &quaternion) {
    ///later use fout.
    cout<<quaternion.toString()<<endl;
}

InterCode::T_place InterCode::genTerm(TreeNode *node) {
    if(node== nullptr||node->getChildren_().empty()){
        return "none";
    }
    T_place t1;
    T_place t2;
    string res;
//    node->showNode();
//    cout<<node->token.lexeme<<endl;
//     cerr<<node->kind<<" " <<node->getChildren_().size()<<endl;
    for(int i = 0;i<node->getChildren_().size();i++){
        if(i==0){
            t1 = genFactor(node->getChildren_()[0]);
            res= t1;
        } else{
            TreeNode *it = node->getChildren_()[i];
            if(it->kind==nodeType::MULT||it->kind==nodeType::DIV){
                string tmpOp = it->kind==nodeType::MULT?"*":"/";
                i++;
                TreeNode* next = node->getChildren_()[i];
                t2 = genFactor(next);
                res = newTemp();
                emit(Quaternion(tmpOp,t1,t2,res));
                t1 = res;
            }
        }
    }
    return res;
}

InterCode::F_place InterCode::genFactor(TreeNode *node) {
    if(node->kind==nodeType::EXPRESSION){
        return genExpression(node);
    }else if(node->kind==nodeType::ID){
        return node->token.lexeme;
    } else if(node->kind==nodeType::BINARY_NUMBER){
        if(node->token.empty()){
            return "num";
        } else{
            return node->token.lexeme;
        }

    } else{
        Error::syntaxError("empty Factor!");
    }
}

string InterCode::newTemp() {

    ///push it to symbolTable.
    return "t"+ to_string(tolTempNum++);
}

const vector<Quaternion> &InterCode::getQuaternionList_() const {
    return quaternionList_;
}

void InterCode::setQuaternionList_(const vector<Quaternion> &quaternionList_) {
    InterCode::quaternionList_ = quaternionList_;
}

