#ifndef CONTAINER_H
#define CONTAINER_H
#include "rapidxml.hpp"
#include "Item.h"
#include "Trigger.h"
#include <vector>
#include <map>
#include <string.h>
using namespace rapidxml;
using namespace std;



class Container{
private:
    char* name;
    const char* status;
    char* description;
    vector<char*> accpt;
    vector<Item*> item;
    vector<Trigger*> trigger;
public:
    Container();
    Container(xml_node<>* node, vector<Item*> items);
    Container(Container& container);
    ~Container();
    void setName(char* name);
    void setStatus(const char* stat);
    void setDescription(char* ds);
    void setAccept(char* acpt);
    void setItem(char* itm, vector<Item*> items);
    void setTrigger(xml_node<>* node);
    char* getName();
    const char* getStatus();
    char* getDescription();
    vector<char*> getAccept();
    vector<Item*> getItem();
    vector<Trigger*> getTrigger();
};

#endif