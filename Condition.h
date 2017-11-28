#ifndef CONDITION_H
#define CONDITION_H


#include "rapidxml.hpp"
#include "rapidxml_print.hpp"
#include <iostream>

using namespace std;
using namespace rapidxml;

class Condition{
private:
    char* owner;
    char* has;
    char* object;
    char* status;
public:
    Condition();
    Condition(xml_node<>* node);
    Condition(Condition& cndt);
    void setOwner(char* own);
    char* getOwner();
    void setHas(char* hs);
    char* getHas();
    void setObject(char* obj);
    char* getObject();
    void setStatus(char* stat);
    char* getStatus();
};

#endif