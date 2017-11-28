#include "Item.h"

Item::Item(){
    // cout<<"Item:";
    setName(NULL);
    // cout<<"Item:";
    setStatus(NULL);
    // cout<<"Item:";
    setDescription(NULL);
    // cout<<"Item:";
    setWriting(NULL);
    // cout<<"Item:";
    setTurnOn(NULL);
    // cout<<"Item:";
    setTrigger(NULL);
}

Item::Item(xml_node<>* node){
    // cout<<"Item:";
    setName(NULL);
    // cout<<"Item:";
    setStatus(NULL);
    // cout<<"Item:";
    setDescription(NULL);
    // cout<<"Item:";
    setWriting(NULL);
    // cout<<"Item:";
    setTurnOn(NULL);
    // cout<<"Item:";
    setTrigger(NULL);


    if(node == NULL){
        return;
    }

    xml_node<>* temp = node->first_node();

    while(temp != NULL){
        if(strcmp(temp->name(),"name") == 0){
            setName(temp->value());
        }
        else if(strcmp(temp->name(),"status") == 0){
            setStatus(temp->value());
        }
        else if(strcmp(temp->name(),"description") == 0){
            setDescription(temp->value());
        }
        else if(strcmp(temp->name(),"writing") == 0){
            setWriting(temp->value());
        }
        else if(strcmp(temp->name(),"turnon") == 0){
            setTurnOn(temp);
        }
        else if(strcmp(temp->name(),"trigger") == 0){
            setTrigger(temp);
        }

        temp = temp->next_sibling();
    }
}

Item::Item(Item& itm){

    this->name = itm.name;
    this->status = itm.status;
    this->description = itm.description;
    this->writing = itm.writing;

    if(itm.turnon != NULL){
        this->turnon = new TurnOn(*(itm.turnon));
    }
    else{
        this->turnon = NULL;
    }

    for(int i = 0; i < (itm.trigger).size(); i++){
        Trigger* test = new Trigger(*(itm.trigger[i]));
        this->trigger.push_back(test);
    }
}

Item::~Item(){
    if(turnon != NULL){
        delete turnon;
    }


    for(int i = 0; i < trigger.size(); i++){
        delete trigger[i];
    }
}

void Item::setName(char* nm){
    // cout<< "Set Name\n";
    name = nm;
}

void Item::setStatus(const char* stat){
    // cout<< "Set Status\n";
    status = stat;
}

void Item::setDescription(char* ds){
    // cout<< "Set Description\n";
    description = ds;
}

void Item::setWriting(char* wr){
    // cout<< "Set Writing\n";
    writing = wr;
}

void Item::setTurnOn(xml_node<>* node){
    // cout<< "Set Turnon\n";

    if(node == NULL){
        turnon = NULL;
        return;
    }

    turnon = new TurnOn(node);
}

void Item::setTrigger(xml_node<>* node){
    // cout<< "Set Trigger\n";

    if(node == NULL){
        return;
    }

    Trigger* trig = new Trigger(node);

    trigger.push_back(trig); 
}

char* Item::getName(){
    return name;
}

const char* Item::getStatus(){
    return status;
}

char* Item::getDescription(){
    return description;
}

char* Item::getWriting(){
    return writing;
}

TurnOn* Item::getTurnOn(){
    return turnon;
}

vector<Trigger*> Item::getTrigger(){
    return trigger;
}