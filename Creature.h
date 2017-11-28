#ifndef CREATURE_H
#define CREATURE_H
#include "rapidxml.hpp"
#include "Attack.h"
#include "Trigger.h"
#include <vector>
#include <iostream>
#include <string.h>
using namespace rapidxml;
using namespace std;

class Creature{
private:
    char* name;
    const char* status;
    char* description;
    vector<char*> vulnerability;
    Attack* attack;
    vector<Trigger*> trigger;

public:
    Creature();
    ~Creature();
    Creature(xml_node<>* node);
    Creature(Creature& cr); //TODO: implement
    void setName(char* nm);
    void setStatus(const char* stat);
    void setDescription(char* ds);
    void setVulnerability(char* vuln);
    void setAttack(xml_node<>* node);
    void setTrigger(xml_node<>* node);
    char* getName();
    const char* getStatus();
    char* getDescription();
    vector<char*> getVulnerability();
    Attack* getAttack();
    vector<Trigger*> getTrigger();
};

#endif