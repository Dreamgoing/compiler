//
// Created by 王若璇 on 16/12/22.
//

#include "InterCode.h"

int Quaternion::tolNum = 0;
int InterCode::tolTempNum = 0;
int Quaternion::tolLabel = 0;


InterCode::InterCode() {
    Quaternion::tolNum = 0;
    InterCode::tolTempNum = 0;
    Quaternion::tolLabel = 0;


}

int Quaternion::getIndex_() const {
    return index_;
}

void Quaternion::setIndex_(int index_) {
    Quaternion::index_ = index_;
}


///@brief Expression intermediate Code.
InterCode::E_place InterCode::genExpression(TreeNode *node) {
    if(node== nullptr||node->getChildren_().empty()){
        return "none";
    }
    E_place e1;
    E_place e2;
    string res;

    ///@note auto pointer don't support inc_op "++".otherwise it will lead to memory error.
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
//                cerr<<"res "<<res<<endl;

                emit(Quaternion(tmpOp,e1,e2,res));
                e1 = res;
            }
        }
    }
    return res;

}


void InterCode::emit(const Quaternion &quaternion) {
    ///later use fout.
#ifdef SHOW_ROW_NUM
//    cout<<quaternion.row<<" :";
#endif
    quaternionList_.push_back(quaternion);
//    cout<<quaternion.toString()<<endl;
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

void InterCode::emit(const string &str) {
//    cout<<str<<endl;
}

void InterCode::genAssignment(TreeNode *node) {

    ///@brief according to the structure of AST.

    emit(Quaternion("=",genExpression(node->getChildren_()[2]),"",node->getChildren_()[0]->token.lexeme));
}

///use pointer is smarter.
///@todo to support "||" and "&&" operation.
InterCode::codeIndex InterCode::genCondition(TreeNode *node) {
    Quaternion condition;
    if(node->kind!=nodeType::CONDITION){
        Error::syntaxError("irregular condition!");
    }
    assert(condition.row==Quaternion::tolNum);
    condition.trueList = condition.row;
    condition.falseList = condition.row+1;
    condition.beginCode = condition.row;
    condition.isCondition = true;
    if(node->getChildren_().size()==1){
        ///single expression
        condition.arg1 = genExpression(node->getChildren_()[0]);

    } else if(node->getChildren_().size()==3){
        ///binary expression
        condition.arg1 = genExpression(node->getChildren_()[0])+node->getChildren_()[1]->token.lexeme+genExpression(node->getChildren_()[2]);
    } else;///irregular condition.

    Quaternion gotoZero;
    gotoZero.isJump = true;
    emit(condition);
    emit(gotoZero);
    return condition.getIndex_();
}

InterCode::codeIndex InterCode::genSelectionStatement(TreeNode *node) {
    if(node->kind!=nodeType::SELECTION_STATEMENT){
        Error::syntaxError("irregular selection_statement");
    }
    int index = genCondition(node->getChildren_()[0]);

    ///trueList
//    cout<<"l"<<Quaternion::tolNum<<endl;
    bathPatch_(index,Quaternion::tolNum+1);

    ///C_chain is the index in the list.
    int C_chain = quaternionList_[index].falseList-1;
    ///S1_chain is the head of list.
    int S1_chain = genStatementBlock(node->getChildren_()[1]);
    if(node->getChildren_().size()==2){
        ///non-else statement
        ///@note a little different
        ///failList
        merge_(C_chain,Quaternion::tolNum+1);


    } else if(node->getChildren_().size()==3){
        int tmpFailList = Quaternion::tolNum; ///tmpQ index
        Quaternion tmpQ;
        tmpQ.isJump = true;
        emit(tmpQ);

        ///the same
        bathPatch_(C_chain,Quaternion::tolNum+1);

        ///S2_chain is the head of list
        int S2_chain = genStatementBlock(node->getChildren_()[2]);

        int outIndex = Quaternion::tolNum+1;
        merge_(tmpFailList,outIndex);
    } else{
        Error::syntaxError("interCode::irregular selection statement");
    }
    return 0;
}

void InterCode::bathPatch_(InterCode::codeIndex index, int pos) {
    quaternionList_[index].result = to_string(pos);

    quaternionList_[index].assigned = true;
//    cout<<pos<<" "< <quaternionList_[index].toString()<<endl;
}

InterCode::codeIndex InterCode::genStatementBlock(TreeNode *node) {
    if(node->kind!=nodeType::STATEMENT_BLOCK){
        Error::syntaxError("interCode::irregular selection statement");
    }
    if(node->getChildren_().size()==1){
        genStatements(node->getChildren_()[0]);
    }
    return Quaternion::tolNum;
}

///@note
InterCode::codeIndex InterCode::merge_(InterCode::codeIndex p1, InterCode::codeIndex p2) {
    quaternionList_[p1].result = to_string(p2);
    quaternionList_[p1].assigned = true;
    return 0;
}

void InterCode::showQuaternionList() {
    for(auto it:quaternionList_){
#ifdef SHOW_ROW_NUM
        cout<<it.row<<": ";
#endif
        cout<<it.toString()<<endl;
    }
}

InterCode::codeIndex InterCode::genStatement(TreeNode *node) {
    if(node->kind==nodeType::ASSIGN_STATEMENT){
        genAssignment(node);
    }else if(node->kind==nodeType::SELECTION_STATEMENT){
        genSelectionStatement(node);
    }else if(node->kind==nodeType::DO_WHILE_STATEMENT){

    }else if(node->kind==nodeType::WHILE_STATEMENT){
        genWhileStatement(node);
    }else;
    return 0;
}

InterCode::codeIndex InterCode::genStatements(TreeNode *node) {
    if(node->kind!=nodeType::STATEMENTS){
        Error::syntaxError("interCode::irregular statements");
    }
    for(auto it:node->getChildren_()){
        genStatement(it);
    }
    return 0;
}

InterCode::codeIndex InterCode::genWhileStatement(TreeNode *node) {
    if(node->kind==nodeType::WHILE_STATEMENT){
        int index = genCondition(node->getChildren_()[0]);
        bathPatch_(index,Quaternion::tolNum+1);
        int W_chain = quaternionList_[index].falseList-1;
        int S_chain = genStatementBlock(node->getChildren_()[1]);
        merge_(W_chain,Quaternion::tolNum+1);
        Quaternion tmpQ;
        tmpQ.isJump = true;
        tmpQ.assigned = true;
        tmpQ.result = to_string(index+1);
        emit(tmpQ);
    }
    return Quaternion::tolNum;
}
InterCode::codeIndex InterCode::genDoStatement(TreeNode *node) {
    return 0;
}

void InterCode::genProgress(TreeNode *node) {
    if(node->kind==nodeType::MAIN&&node->getChildren_().size()==1){
        genStatementBlock(node->getChildren_()[0]);
    }else{
        Error::syntaxError("interCode:: irregular progress");
    }
    emit(Quaternion("","","","END"));

}





