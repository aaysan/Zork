#include "Creature.h"

Creature::Creature(){
    // cout<<"Creature:";
    setName(NULL);
    // cout<<"Creature:";
    setStatus(NULL);
    // cout<<"Creature:";
    setDescription(NULL);
    // cout<<"Creature:";
    setVulnerability(NULL);
    // cout<<"Creature:";
    setAttack(NULL);
    // cout<<"Creature:";
    setTrigger(NULL);

}

Creature::~Creature(){
    if(attack != NULL){
        delete attack;
    }

    for(int i = 0; i < trigger.size();i++){
        delete trigger[i];
    }
}

Creature::Creature(xml_node<>* node){

    // cout<<"Creature:";
    setName(NULL);
    // cout<<"Creature:";
    setStatus(NULL);
    // cout<<"Creature:";
    setDescription(NULL);
    // cout<<"Creature:";
    setVulnerability(NULL);
    // cout<<"Creature:";
    setAttack(NULL);
    // cout<<"Creature:";
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
        else if(strcmp(temp->name(),"vulnerability") == 0){
            setVulnerability(temp->value());
        }
        else if(strcmp(temp->name(), "attack") == 0){
            setAttack(temp);
        }
        else if(strcmp(temp->name(), "trigger") == 0){
            setTrigger(temp);
        }

        temp = temp->next_sibling();
    }
}

Creature::Creature(Creature& cr){

    this->name = cr.name;
    this->status = cr.status;
    this->description = cr.description;

    for(int i = 0; i < (cr.vulnerability).size(); i++){
        this->vulnerability.push_back(cr.vulnerability[i]);
    }

    if(cr.attack != NULL){
        attack = new Attack(*(cr.attack));
    }
    else{
        attack = NULL;
    }

    for(int i = 0; i < (cr.trigger).size(); i++){
        Trigger* newtrig = new Trigger(*(cr.trigger[i]));
        this->trigger.push_back(newtrig);
    }
}

void Creature::setName(char* nm){
    // cout<< "Set Name\n";
    name = nm;
}

void Creature::setStatus(const char* stat){
    // cout<< "Set Status\n";
    status = stat;
}

void Creature::setDescription(char* ds){
    // cout<< "Set Description\n";
    description = ds;
}

void Creature::setVulnerability(char* vuln){
    // cout<< "Set Vuln\n";
    if(vuln == NULL){
        return;
    }

    vulnerability.push_back(vuln);
}

void Creature::setAttack(xml_node<>* node){
    // cout<< "Set Attack\n";

    if(node == NULL){
        attack = NULL;
        return;
    }

    Attack* att = new Attack(node);
    attack = new Attack(*att);
    delete att;
}

void Creature::setTrigger(xml_node<>* node){
    // cout<< "Set Trigget\n";

    if(node == NULL){
        return;
    }

    Trigger* trig = new Trigger(node);
    trigger.push_back(trig);
}

char* Creature::getName(){
    // cout<< "Get name\n";
    return name;
}

const char* Creature::getStatus(){
    // cout<< "Get status\n";
    return status;
}

char* Creature::getDescription(){
    // cout<< "Get Description\n";
    return description;
}

vector<char*> Creature::getVulnerability(){
    // cout<< "Get Vulnerability\n";
    return vulnerability;
}

Attack* Creature::getAttack(){
    // cout<< "Get Attack\n";
    return attack;
}

vector<Trigger*> Creature::getTrigger(){
    // cout<<"Get Trigger\n";
    return trigger;
}