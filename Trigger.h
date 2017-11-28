#ifndef TRIGGER_H
#define TRIGGER_H

#include "Condition.h"
#include <vector>
#include "rapidxml.hpp"
#include "rapidxml_print.hpp"
using namespace rapidxml;

class Trigger{

private:
    char* type;
    char* command;
    Condition* condition;
    char* prnt;
    vector<char*> action; //behind the scenes;
public:
    Trigger();
    ~Trigger();
    Trigger(xml_node<>* node);
    Trigger(Trigger& trig);
    void setType(char* ty);
    void setCommand(char* cmd);
    void setCondition(xml_node<>* node);
    void setPrint(char* prt);
    void setAction(char* act);
    char* getType();
    char* getCommand();
    Condition* getCondition();
    char* getPrint();
    vector<char*> getAction();
};

#endif