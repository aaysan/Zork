#include "Container.h"
#include "Room.h"
#include <string.h>
// void openContainer(char* container, vector<Container*> containers);
// bool openExit(Room* room);

void openContainer(char* container, vector<Container*> containers){
    for(int i = 0; i < containers.size(); i++){
        if(strcmp(container, containers[i]->getName()) == 0){
            vector<Item*> items = containers[i]->getItem();

            if(items.size() == 0){
                cout<<"Contains no elements\n";
                return;
            }

            for(int j = 0; j < items.size(); j++){
                cout<<items[i]->getName()<<endl;
            }
            
        }
    }
}

bool openExit(Room* room){

    if(room == NULL){
        return false;
    }


    if(strcmp(room->getType(),"exit") == 0){
        return true;
    }

    return false;
}

void updateStatus(Item* item, char* status){
    item->setStatus(status);
}

void updateStatus(Container* container, char* status){
    container->setStatus(status);
}

void updateStatus(Creature* creature, char* status){
    creature->setStatus(status);
}

void updateStatus(Room* room, char* status){
    room->setStatus(status);
}

void turnOnItem(char* item, vector<Item*> items){

    for(int i = 0; i < items.size(); i++){

        if(strcmp(items[i]->getName(),item) == 0){

            if(items[i]->getTurnOn() != NULL && items[i]->getTurnOn()->getPrint() != NULL){
                cout<<items[i]->getTurnOn()->getPrint()<<endl;
            }
            else{
                cout<<"Can't turn on.. Item doesn't have that capability"<<endl;
            }

            //action
            return;
        }

    }

    cout<<"Can't turn on... Item not found"<<endl;

}

bool gameOver(){
    cout<<"Victory!";
    return true;
}

void readItem(char* item){
    if(inventory.empty()){
        cout<<"Item not found in inventory!"<<endl;
    }

    for(int i = 0; i < inventory.size();i++){
        if(strcmp(item,inventory[i]->getName()) == 0){

            if(inventory[i]->getWriting() != NULL){
                cout<<inventory[i]->getWriting()<<endl;
            }
            else{
                cout<<"Nothing written\n";
            }

            return;

        }
    }

    cout<<"Item not found in the inventory!"<<endl;
}