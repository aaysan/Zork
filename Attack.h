#ifndef ATTACK_H
#define ATTACK_H

#include "rapidxml.hpp"
#include "Condition.h"
#include <vector>
#include <iostream>
#include <string.h>
using namespace rapidxml;
using namespace std;

class Attack{

private:
    Condition* condition;
    char* prnt;
    vector<char*> action;

public:
    Attack();
    ~Attack();
    Attack(xml_node<>* node);
    Attack(Attack& att);
    void setCondition(xml_node<>* node);
    void setPrint(char* pr);
    void setAction(char* act);
    Condition* getCondition();
    char* getPrint();
    vector<char*> getAction();

};

#endif