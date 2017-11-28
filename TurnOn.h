#ifndef TURNON_H
#define TURNON_H
#include "rapidxml.hpp"
#include <iostream>
#include <string.h>
using namespace rapidxml;
using namespace std;

class TurnOn{
private:
    char* prnt;
    char* action;
public:
    TurnOn();
    TurnOn(xml_node<>* node);
    TurnOn(TurnOn& trn);
    void setPrint(char* pr);
    void setAction(char* act);
    char* getPrint();
    char* getAction();
};

#endif