#ifndef ITEM_H
#define ITEM_H
#include "rapidxml.hpp"
#include "TurnOn.h"
#include "Trigger.h"
#include <vector>
#include <string.h>
using namespace rapidxml;
using namespace std;

class Item{
private:
    char* name;
    const char* status;
    char* description;
    char* writing;
    TurnOn* turnon;
    vector<Trigger*> trigger;
public:
    Item();
    Item(xml_node<>* node);
    Item(Item& itm);
    ~Item();
    void setName(char* nm);
    void setStatus(const char* stat);
    void setDescription(char* ds);
    void setWriting(char* wr);
    void setTurnOn(xml_node<>* node);
    void setTrigger(xml_node<>* node);
    char* getName();
    const char* getStatus();
    char* getDescription();
    char* getWriting();
    TurnOn* getTurnOn();
    vector<Trigger*> getTrigger();
    
};

#endif