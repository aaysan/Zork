#include "Attack.h"

Attack::Attack(){
    // cout<<"Attack:";
    setCondition(NULL);
    // cout<<"Attack:";
    setPrint(NULL);
    // cout<<"Attack:";
    setAction(NULL);
}

Attack::~Attack(){


    if(condition != NULL){
        delete condition;
    }
}

Attack::Attack(xml_node<>* node){
    // cout<<"Attack:";
    setCondition(NULL);
    // cout<<"Attack:";
    setPrint(NULL);
    // cout<<"Attack:";
    setAction(NULL);

    if(node == NULL){
        return;
    }

    xml_node<>* temp = node->first_node();

    while(temp != NULL){
        if(strcmp(temp->name(),"condition") == 0){
            setCondition(temp);
        }
        else if(strcmp(temp->name(), "print") == 0){
            setPrint(temp->value());
        }
        else if(strcmp(temp->name(), "action") == 0){
            setAction(temp->value());
        }

        temp = temp->next_sibling();
    }
}

Attack::Attack(Attack& att){

    if(att.condition != NULL){
        this->condition = new Condition(*(att.condition));
    }
    else{
        this->condition = NULL;
    }
    this->prnt = att.prnt;
    this->action = att.action;
}

void Attack::setCondition(xml_node<>* node){
    
    // cout<<"Set condition\n";

    if(node == NULL){
        condition = NULL;
        return;
    }

    Condition* cndt = new Condition(node);
    condition = new Condition(*cndt);
    delete cndt;
}

void Attack::setPrint(char* pr){
    // cout<<"Set Print\n";
    prnt = pr;
}

void Attack::setAction(char* act){
    // cout<<"Set action\n";
    if(act == NULL){
        return;
    }
    action.push_back(act);
}

Condition* Attack::getCondition(){
    // cout<<"Get Condition\n";
    return condition;
}

char* Attack::getPrint(){
    // cout<<"Get Print\n";
    return prnt;
}
    
vector<char*>  Attack::getAction(){
    // cout<<"Get Action\n";
    return action;
}