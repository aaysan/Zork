#include "rapidxml.hpp"
#include <fstream>
#include <iostream>
#include <vector>
#include "Condition.h"
#include "Trigger.h"
#include "Attack.h"
#include "Creature.h"
#include "Item.h"
#include "Container.h"
#include "Border.h"
#include "Room.h"
#include <string.h>
#include <sstream>
using namespace rapidxml;
using namespace std;

void startGame(vector<Room*> roomVector, vector<Item*> items, vector<Container*> cnts, vector<Creature*> creatures);
bool gotCommand(bool checker, string input, vector<Room*> roomVector, vector<Item*> items, vector<Container*> cnts, vector<Creature*> creatures);
int getRoomIdx(string roomCurr, vector<Room*> roomVector);
void nextRoomCommand(string input, vector<Room*> roomVector);
void inventoryCommand(vector<Room*> roomVector);
void takeCommand(string input,string container, vector<Room*> roomVector);
void dropCommand(string input, vector<Room*> roomVector, vector<Item*> items);
// void addCommand(string object, string destination, Room* room);
bool isRoom(string destination, Room* room);
bool isContainer(string destination, vector<Container*> containers);
// void addCommand(string object, string destination, vector<Room*> roomVector, vector<Item*> items);
void openContainer(string container, vector<Container*> containers);
bool openExit(Room* room);
void updateStatus(Item* item, const char* status);
void updateStatus(Container* container, const char* status);
void updateStatus(Creature* creature, const char* status);
void updateStatus(Room* room, const char* status);
void turnOnItem(string item, vector<Room*> roomVector, vector<Container*> cnts, vector<Creature*> creatures);
bool gameOver();
void readItem(string item);
void deleteCommand(string object, vector<Room*> roomVector, vector<Item*> items, vector<Container*> cnts, vector<Creature*> creatures);
void deleteRoom(string object, vector<Room*> roomVector);
vector<Item*> deleteItemFrom(vector<Item*>, string item);
void deleteItem(string object, vector<Room*> roomVector);
void deleteContainer(string object, vector<Room*> roomVector);
void deleteCreature(string object, vector<Room*> roomVector);
bool behindCommand(bool checker, string input, vector<Room*> roomVector, vector<Item*> items, vector<Container*> cnts, vector<Creature*> creatures);
bool attackCommand(bool checker, string input, string tempCreature, string tempItem, vector<Room*> roomVector, vector<Item*> items, vector<Container*> cnts, vector<Creature*> creatures);
bool inventoryPresent(string tempItem);
void addCommand(string object, string destination, vector<Room*> room, vector<Item*> items, vector<Creature*> creatures, vector<Container*> containers);
void addToItem(string object, vector<Item*> items);
void addToRoom(string object, Room* room, vector<Item*> items, vector<Creature*> creatures, vector<Container*> containers);
Container* addToContainer(string object, Container* containers, vector<Item*> items);
Item* inventoryObject(string obj);
bool conditionCheck(string object, Condition* condition, vector<Room*> roomVector);
bool checkTriggers(string command, Room* room);
bool match(bool has, bool hasTmp);