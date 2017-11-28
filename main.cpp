#include "rapidxml.hpp"
#include "rapidxml_print.hpp"
#include "rapidxml_utils.hpp"
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
#include "Game.h"
#include <string.h>
using namespace rapidxml;
using namespace std;

vector<Item*> getItemVector(xml_node<>* node);
vector<Container*> getContainerVector(xml_node<>* node, vector<Item*> items);
vector<Creature*> getCreatureVector(xml_node<>* node);
vector<Room*> getRoomVector(xml_node<>* node, vector<Item*> items, vector<Container*> cnts, vector<Creature*> creatures);

int main(int argc, char** argv){

    //next lines check if file exists properly.
    if(argc < 2){
        cout << "No input file given!" <<endl;
        return 0;
    }

    ifstream f(argv[1]);
    if(!f.good()){
        f.close();
        return 0;
    }
    f.close();
    //done checking

    file<> xmlFile(argv[1]);
    xml_document<> doc;
    doc.parse<0>(xmlFile.data());
    //done parsing

    //INITIALIZING AND PARSING THE XML INTO CLASSES
    //THE VECTOR NAMED ROOMS CONTAINS THE ROOMS
    //THAT VECTOR IS WHAT WE WILL DO STUFF ON

    // cout<<"ITEMS\n";
    xml_node<> * node = doc.first_node("map")->first_node("item");
    vector<Item*> items = getItemVector(node);

    // cout<<"CONTAINER\n";
    node = doc.first_node("map")->first_node("container");
    vector<Container*> cnts = getContainerVector(node, items);

    // cout<<"CREATURE\n";
    node = doc.first_node("map")->first_node("creature");
    vector<Creature*> creatures = getCreatureVector(node);

    // cout<<"ROOM\n";
    node = doc.first_node("map")->first_node("room");
    vector<Room*> rooms =  getRoomVector(node, items, cnts, creatures);

    // Start the game
    startGame(rooms, items, cnts, creatures);

    //FREEING
    for(int i = 0; i < items.size(); i++){
        delete items[i];
    }
    for(int i = 0; i < cnts.size(); i++){
        delete cnts[i];
    }
    for(int i = 0; i < creatures.size(); i++){
        delete creatures[i];
    }
    for(int i = 0; i < rooms.size(); i++){
        delete rooms[i];
    }
    return 0;

}

vector<Item*> getItemVector(xml_node<>* node){

    vector<Item*> items;

    while(node!= NULL && strcmp(node->name(), "item") == 0){
        Item* itm = new Item(node);
        cout<<"Found item: "<<itm->getName()<<endl;
        items.push_back(itm);
        node = node->next_sibling();
    }

    return items;
}

vector<Container*> getContainerVector(xml_node<>* node, vector<Item*> items){
    vector<Container*> cnts;
    while(node != NULL && strcmp(node->name(), "container") == 0){
        Container* newcnts = new Container(node,items);
        cout<<"Found container: "<<newcnts->getName()<<endl;
        cnts.push_back(newcnts);
        node = node->next_sibling();
    }
    return cnts;
}

vector<Creature*> getCreatureVector(xml_node<>* node){
    vector<Creature*> creatures;
    while(node != NULL && strcmp(node->name(), "creature") == 0){
        Creature* creature = new Creature(node);
        cout<<"Found creature: "<<creature->getName()<<endl;
        creatures.push_back(creature);
        node = node->next_sibling();
    }
    return creatures;
}

vector<Room*> getRoomVector(xml_node<>* node, vector<Item*> items, vector<Container*> cnts, vector<Creature*> creatures){
    vector<Room*> rooms;
    while(node != NULL && strcmp(node->name(), "room") == 0){
        cout<<"\nNEW ONE\n\n";
        Room* newroom = new Room(node, cnts, items, creatures);

        cout<<"Found room: "<< newroom->getName()<<endl;

        if(newroom->getStatus() != NULL){
            cout<<"Status: "<<newroom->getStatus()<<endl;
        }
        if(newroom->getType() != NULL){
            cout<<"Type: "<<newroom->getType()<<endl;
        }
        if(newroom->getDescription() != NULL){
            cout<<"Description: "<<newroom->getDescription()<<endl;
        }

        vector<Border*> br = newroom->getBorder();

        for(int i = 0; i < br.size(); i++){
            cout<<br[i]->getDirection()<<": "<<br[i]->getName()<<endl;
        }

        vector<Item*> it = newroom->getItem();

        for(int i = 0; i < it.size(); i++){
            cout<<"Item: "<<it[i]->getName()<<endl;
        }

        vector<Container*> cnn = newroom->getContainer();

        for(int i = 0; i < cnn.size();i++){
            cout<<"Container:"<<cnn[i]->getName()<<endl;
        }

        vector<Trigger*> trigsss = newroom->getTrigger();

        for(int i = 0; i < trigsss.size();i++){
            cout<<"Trigger: "<<trigsss[i]->getPrint()<<endl;
        }

        vector<Creature*> crr = newroom->getCreature();

        for(int i = 0; i < crr.size();i++){
            cout<<"Creature: "<<crr[i]->getName()<<endl;
        }

        rooms.push_back(newroom);
        node = node->next_sibling();
    }
    return rooms;
}
