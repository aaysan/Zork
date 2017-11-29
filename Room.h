#ifndef ROOM_H
#define ROOM_H
#include "rapidxml.hpp"
#include "Border.h"
#include "Container.h"
#include "Item.h"
#include "Creature.h"
#include "Trigger.h"
#include <iostream>
#include <string.h>
#include <vector>
using namespace std;
using namespace rapidxml;

class Room{
private:
    char* name;
    const char* status;
    const char* type;
    char* description;
    vector<Border*> borders;
    vector<Item*> items;
    vector<Container*> containers;
    vector<Creature*> creatures;
    vector<Trigger*> triggers;
public:
    Room();
    Room(xml_node<>* node, vector<Container*> cnts, vector<Item*> itm, vector<Creature*> crs);
    Room(Room& rm);
    ~Room();
    void setName(char* nm);
    void setStatus(const char* stat);
    void setType(const char* ty);
    void setDescription(char* desc);
    void setBorder(xml_node<>* node);
    void setBorder(vector<Border*> border);
    void setContainer(char* container, vector<Container*> cnts);
    void setContainer(vector<Container*> container);
    void setItem(char* item, vector<Item*> itm);
    void setItem(vector<Item*> itm);
    void setCreature(char* cr, vector<Creature*> crs);
    void setCreature(vector<Creature*> creature);
    void setTrigger(xml_node<>* node);
    char* getName();
    const char* getStatus();
    const char* getType();
    char* getDescription();
    vector<Border*> getBorder();
    vector<Item*> getItem();
    vector<Container*> getContainer();
    vector<Creature*> getCreature();
    vector<Trigger*> getTrigger();
};

#endif