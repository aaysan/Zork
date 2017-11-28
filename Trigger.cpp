#include "Trigger.h"
#include <iostream>
#include <string.h>
using namespace std;

Trigger::Trigger(){
    // cout << "Trigger:";
    setType(NULL);
    // cout << "Trigger:";
    setCommand(NULL);
    // cout << "Trigger:";
    setCondition(NULL);
    // cout << "Trigger:";
    setPrint(NULL);
    // cout << "Trigger:";
    setAction(NULL);
}

Trigger::~Trigger(){
    if(condition != NULL){
        delete condition;
    }
}

Trigger::Trigger(xml_node<> * node){
    // cout << "Trigger:";
    setType(NULL);
    // cout << "Trigger:";
    setCommand(NULL);
    // cout << "Trigger:";
    setCondition(NULL);
    // cout << "Trigger:";
    setPrint(NULL);
    // cout << "Trigger:";
    setAction(NULL);

     if(node == NULL){
        return;
    }

    xml_node<>* temp = node->first_node();

   
    
    while(temp != NULL){
        if(temp->value() == NULL){
            temp = temp->next_sibling();
            continue;
        }
        if(!strcmp(temp->name(), "type")){
            setType(temp->value());
        }
        else if(!strcmp(temp->name(), "command")){
            setCommand(temp->value());
        }
        else if(!strcmp(temp->name(), "condition")){
            setCondition(temp);
        }
        else if(!strcmp(temp->name(), "print")){
            setPrint(temp->value());
        }
        else if(!strcmp(temp->name(), "action")){
            setAction(temp->value());
        }
        temp = temp->next_sibling();
    }

}

Trigger::Trigger(Trigger& trig){

    this->type = trig.type;
    this->command = trig.command;
    this->condition = new Condition(*(trig.condition));
    this->prnt = trig.prnt;
    this->action = trig.action;
}

void Trigger::setType(char* ty){
    // cout<<"Set Type"<<endl;
    type = ty;
}      

void Trigger::setCommand(char* cmd){
    // cout<<"Set Command"<<endl;
    command = cmd;
}

void Trigger::setCondition(xml_node<>* node){
    // cout<<"Set Condition"<<endl;

    if(node == NULL){
        condition = NULL;
        return;
    }

    Condition* cndt = new Condition(node);
    condition = new Condition(*cndt);
    delete cndt;
}

void Trigger::setPrint(char* prt){
    // cout<<"Set Print"<<endl;
    prnt = prt;
}

void Trigger::setAction(char* act){
    // cout<<"Set Action"<<endl;

    if(act == NULL){
        return;
    }

    action.push_back(act);
}

char* Trigger::getType(){
    // cout<<"Get Type"<<endl;
    return type;
}

char* Trigger::getCommand(){
    // cout<<"Get Command"<<endl;
    return command;
}

Condition* Trigger::getCondition(){
    // cout<<"Get Condition"<<endl;
    return condition;
}

char* Trigger::getPrint(){
    // cout<<"Get Print"<<endl;
    return prnt;
}

vector<char*> Trigger::getAction(){
    // cout<<"Get Action"<<endl;
    return action;
}

