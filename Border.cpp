#include "Border.h"

Border::Border(){
    setDirection(NULL);
    setName(NULL);
}

Border::Border(xml_node<>* node){
    // cout<<"Border:";
    setDirection(NULL);
    // cout<<"Border:";
    setName(NULL);

    if(node == NULL){
        return;
    }

    xml_node<>* temp = node->first_node();

    while(temp != NULL){
        if(strcmp(temp->name(),"direction")){
            setDirection(temp->value());
        }
        else if(strcmp(temp->name(),"name")){
            setName(temp->value());
        }

        temp = temp->next_sibling();
    }
}

Border::Border(Border& brdr){
    this->direction = brdr.direction;
    this->name = brdr.name;
}

void Border::setDirection(char* direc){
    // cout<<"Set Direction\n";
    direction = direc;
}

void Border::setName(char* nm){
    // cout<<"Set Name\n";
    name = nm;
}

char* Border::getDirection(){
    return direction;
}

char* Border::getName(){
    return name;
}