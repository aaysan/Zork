#include "TurnOn.h"

TurnOn::TurnOn(){
    // cout<<"TurnOn: ";
    setPrint(NULL);
    // cout<<"TurnOn: ";
    setAction(NULL);
}

TurnOn::TurnOn(xml_node<>* node){
    // cout<<"TurnOn: ";
    setPrint(NULL);
    // cout<<"TurnOn: ";
    setAction(NULL);

    if(node == NULL){
        return;
    }

    xml_node<>* temp = node->first_node();

    while(temp != NULL){
        if(strcmp(temp->name(),"print") == 0){
            // cout<<"TEST: "<<temp->value()<<endl;
            setPrint(temp->value());
        }
        else if(strcmp(temp->name(), "action") == 0){
            setAction(temp->value());
        }
        temp = temp->next_sibling();
    }
}

TurnOn::TurnOn(TurnOn& trn){

    this->prnt = trn.prnt;
    this->action = trn.action;
}

void TurnOn::setPrint(char* pr){
    // cout<< "Set PRint\n";
    prnt = pr;
}

void TurnOn::setAction(char* act){
    // cout<< "Set Action\n";

    action = act;
}

char* TurnOn::getPrint(){
    // cout<< "Get Print\n";
    return prnt;
}

char* TurnOn::getAction(){
    // cout<< "Get Action\n";

    return action;
}

