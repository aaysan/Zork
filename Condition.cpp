#include "Condition.h"
#include <stdio.h>
#include <string.h>

Condition::Condition(){
    Condition::setOwner(NULL);
    Condition::setHas(NULL);
    Condition::setObject(NULL);
    Condition::setStatus(NULL);
}

Condition::Condition(xml_node<>* node){
    // cout << "Condition:";
    Condition::setOwner(NULL);
    // cout << "Condition:";
    Condition::setHas(NULL);
    // cout << "Condition:";
    Condition::setObject(NULL);
    // cout << "Condition:";
    Condition::setStatus(NULL);

    if(node == NULL){
        return;
    }

    xml_node<>* temp = node->first_node();
   


    while(temp != NULL){
        if(strcmp(temp->name(),"has") == 0){
            Condition::setHas(temp->value());
        }
        else if(strcmp(temp->name(), "object") == 0){
            Condition::setObject(temp->value());
        }
        else if(strcmp(temp->name(), "owner") == 0){
            Condition::setOwner(temp->value());
        }
        else if(strcmp(temp->name(), "status") == 0){
            Condition::setStatus(temp->value());
        }
        
        temp = temp->next_sibling();
    }
}

Condition::Condition(Condition& cndt){

    

    this->owner = cndt.owner;
    this->has = cndt.has;
    this->object = cndt.object;
    this->status = cndt.status;
}

void Condition::setOwner(char* own){
    // cout<<"set owner"<<endl;
    owner = own;
}

void Condition::setHas(char* hs){
    // cout<<"set has"<<endl;
    has = hs;
}

void Condition::setObject(char* obj){
    // cout<<"Set Object"<<endl;
    object = obj;
}

void Condition::setStatus(char* stat){
    // cout<<"Set Status"<<endl;
    status = stat;
}

char* Condition::getOwner(){
    // cout<<"Get Owner"<<endl;
    return owner;
}

char* Condition::getHas(){
    // cout<<"Get Has"<<endl;
    return has;
}

char* Condition::getObject(){
    // cout<<"Get Object"<<endl;
    return object;
}

char* Condition::getStatus(){
    // cout<<"Get Status"<<endl;
    return status;
}
