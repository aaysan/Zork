#include "Game.h"
string roomState = "Main";
vector<Item*> inventory;

void startGame(vector<Room*> roomVector, vector<Item*> items, vector<Container*> cnts, vector<Creature*> creatures){
  // start game
  cout<<endl<<"----------Game Starts Now----------"<<endl<<endl;
  string inputFromUser;
  roomState = "Entrance";
  cout<<roomVector[0]->getDescription()<<endl;
  bool checker = false;
  while(!checker){
      getline(cin, inputFromUser);
      checker = gotCommand(checker, inputFromUser, roomVector, items, cnts, creatures);
      // check for triggers
  }
}

bool gotCommand(bool checker, string input, vector<Room*> roomVector, vector<Item*> items, vector<Container*> cnts, vector<Creature*> creatures){
    // GET CURRENT ROOM
    string tempWord;
    string tempWord2;
    istringstream iss(input);
    iss >> tempWord;
    int idx = getRoomIdx(roomState, roomVector);
    if (tempWord == "n" || tempWord == "north" || tempWord == "s" || tempWord == "south" || tempWord == "e" || tempWord == "east" || tempWord == "w" || tempWord == "west"){
        nextRoomCommand(tempWord, roomVector);
    }
    else if (tempWord == "i" || tempWord == "inventory"){
        inventoryCommand(roomVector);
    }
    else if(tempWord == "take"){
        iss >> tempWord;
        iss >> tempWord2;
        iss >> tempWord2;
        if(tempWord != ""){
            takeCommand(tempWord, tempWord2, roomVector);
        }
        else{
            cout<<"Error"<<endl;
        }
    }
    else if(tempWord == "open"){
        iss >> tempWord;
        if(tempWord == "exit"){
            bool check = openExit(roomVector[idx]);
            if(check){
                checker = gameOver();
            }
        }
        else if(tempWord != ""){
            vector<Container*> containerTmp = roomVector[idx]->getContainer();
            openContainer(tempWord, containerTmp);
        }

        else{
            cout<<"Error"<<endl;
        }
    }
    else if(tempWord == "delete"){
        iss >> tempWord;
        if(tempWord != ""){
            cout<<"h"<<endl;
            vector<Border*> br;
            for(int i = 0; i < roomVector.size(); i++){
                br = roomVector[i]->getBorder();
                for(int j = 0; j < br.size(); j++){
                    cout<<br[j]->getDirection()<<": "<<br[j]->getName()<<endl;
                }
            }
            //inventoryCommand(roomVector);
            deleteCommand(tempWord, roomVector, items, cnts, creatures);
            for(int i = 0; i < roomVector.size(); i++){
                br = roomVector[i]->getBorder();
                for(int j = 0; j < br.size(); j++){
                    cout<<br[j]->getDirection()<<": "<<br[j]->getName()<<endl;
                }
            }
            //inventoryCommand(roomVector);
        }
        else{
            cout<<"Error"<<endl;
        }
    }
    // else if(tempWord == "read"){
    //     iss >> tempWord;
    //     if(tempWord != NULL){
    //           readCommand(input);
    //     }
    //     else{
    //         cout<<"Error"<<endl;
    //     }
    // }
    // else if(tempWord == "put"){
    //     iss >> tempWord;
    //     if(tempWord != NULL){
    //           putCommand(input);
    //     }
    //     else{
    //         cout<<"Error"<<endl;
    //     }
    // }
    // else if(tempWord == "turn"){
    //     iss >> tempWord;
    //     iss >> tempWord2;
    //     if(tempWord == on && tempWord2 != NULL){
    //           turnOnCommand(input);
    //     }
    //     else{
    //         cout<<"Error"<<endl;
    //     }
    // }
    // else if(tempWord == "attack"){
    //     iss >> tempWord;
    //     iss >> tempWord;
    //     iss >> tempWord;
    //     if(tempWord != NULL){
    //           attackCommand(input);
    //     }
    //     else{
    //         cout<<"Error"<<endl;
    //     }
    // }
    else if(tempWord == "put"){
        iss >> tempWord;
        iss >> tempWord2;
        iss >> tempWord2;
        if(tempWord != "" && tempWord2 != ""){
            //   cout<<"Items: "<<endl;
              //int idx = getRoomIdx(roomState, roomVector);
              vector<Item*> it = roomVector[idx]->getItem();
            //   for(int i = 0; i < it.size(); i++){
            //       cout<<it[i]->getName()<<endl;
            //   }
              //addCommand(tempWord, tempWord2, roomVector);
              addCommand(tempWord, tempWord2, roomVector, items);
              cout<<"Items: ";
              it = roomVector[idx]->getItem();
              for(int i = 0; i < it.size(); i++){
                  cout<<it[i]->getName()<<", "<<endl;
              }
              cout<<"Container Items: ";
              vector<Container*> abc = roomVector[idx]->getContainer();
              
              for(int j = 0; j < abc.size(); j++){\
                
                it = abc[j]->getItem();

                for(int i = 0; i < it.size(); i++){
                    cout<<it[i]->getName()<<", "<<endl;
                }
              }
        }
        else{
            cout<<"Error"<<endl;
        }
    }
    // Check for behind the scenes commands
    else {
        cout<<"Error"<<endl;
    }
    return checker;
}

int getRoomIdx(string roomCurr, vector<Room*> roomVector){
    for(int i = 0; i < roomVector.size(); i++){
        if(roomCurr == roomVector[i]->getName()){
            return i;
        }
    }
    return -1;
}

void nextRoomCommand(string input, vector<Room*> roomVector){
    // get current room
    int idx =  getRoomIdx(roomState, roomVector);
    if(input == "n" || input == "north"){
        input = "north";
    }
    else if(input == "s" || input == "south"){
        input = "south";
    }
    else if(input == "e" || input == "east"){
        input = "east";
    }
    else {
        input = "west";
    }
    int borderIdx = 500;
    vector<Border*> br = roomVector[idx]->getBorder();
    for(int i = 0; i < br.size(); i++){
        if (input == br[i]->getName()){
            roomState = br[i]->getDirection();
            cout<<roomState<<endl;
            borderIdx = getRoomIdx(roomState, roomVector);
            break;
        }
    }
    if(borderIdx != 500){
        cout<<roomVector[borderIdx]->getDescription()<<endl;
    }
    else{
        cout<<"Can’t go that way."<<endl;
    }
}

void inventoryCommand(vector<Room*> roomVector){
    cout<<"Inventory: ";
    if(inventory.empty()){
        cout<<"empty"<<endl;
        return;
    }
    for(int i = 0; i < inventory.size(); i++){
        cout<<inventory[i]->getName()<<endl;
    }
}

void takeCommand(string input,string container, vector<Room*> roomVector){


    for(int i = 0; i < inventory.size(); i++){
        if(input == inventory[i]){
            return;
        }
    }


    int idx =  getRoomIdx(roomState, roomVector);
    
    if(container.empty()){
        vector<Item*> it = roomVector[idx]->getItem();
        for(int i = 0; i < it.size(); i++){
            if(input == it[i]->getName()){
                cout<<"Item "<<it[i]->getName()<<" added to inventory."<<endl;
                Item* newitm = new Item(*it[i]);
                inventory.push_back(newitm);
                // remove or hide from room
                return;
            }
        }
        cout<<"Error"<<endl;
        return;
    }

    vector<Container*> containers = roomVector[idx]->getContainer();
    for(int i = 0; i < containers.size(); i++){
        if(container == containers[i]->getName()){
            cout<<containers[i]->getStatus()<<endl;
            if(containers[i]->getStatus() != "open"){
                cout<<"You need to open that container\n";
                return;
            }

            vector<Item*> itm = containers[i]->getItem();
            for(int j = 0; j < itm.size();j++){
                if(input == itm[j]->getName()){
                    cout<<"Item "<<itm[j]->getName()<<" added to inventory."<<endl;
                    Item* newitm = new Item(*itm[i]);
                    inventory.push_back(newitm);
                    // remove or hide from room
                    return;
                }
            }
        }
    }

    cout<<"Error"<<endl;
}

void dropCommand(string input, vector<Room*> roomVector){
    int idx =  getRoomIdx(roomState, roomVector);
    vector<Item*> it = roomVector[idx]->getItem();
    for(int i = 0; i < inventory.size(); i++){
        if(input == inventory[i]->getName()){
            cout<<inventory[i]->getName()<<" dropped."<<endl;
            // remove or hide from inventory
            // add to room
            return;
        }
    }
    cout<<"Error"<<endl;
}

void addCommand(string object, string destination, vector<Room*> roomVector, vector<Item*> items){
    // get destination
    int dest = destination == roomState ? 0 : 2;
    int idx =  getRoomIdx(roomState, roomVector);
    int cntidx = 0;
    vector<Container*> cnt = roomVector[idx]->getContainer();
    if(destination != roomState){
        for(int i = 0; i < cnt.size(); i++){
            if(cnt[i]->getName() == destination){
                dest = 1;
                cntidx = i;
            }
        }
    }
    if(inventory.empty() || dest == 2){
        cout<<"Error\n";
        return;
    }
    for(int i = 0; i < inventory.size(); i++){
        if(inventory[i]->getName() == object){
            Item* newitm = new Item(*inventory[i]);
            if(dest){
                cout<<"contadd"<<endl;
                vector<Item*> cntItems = cnt[cntidx]->getItem();
                for(int i = 0; i < cntItems.size(); i++){
                    if(cntItems[i]->getName() == object){
                      cout<<"Already here."<<endl;
                      return;
                    }
                }
                cnt[cntidx]->setItem(newitm->getName(), items);
            }
            else {
                cout<<"roomadd"<<endl;
                vector<Item*> roomItems = roomVector[idx]->getItem();
                for(int i = 0; i < roomItems.size(); i++){
                    if(roomItems[i]->getName() == object){
                      cout<<"Already here."<<endl;
                      return;
                    }
                }
                roomVector[idx]->setItem(newitm->getName(), items);
            }
        }
    }
}


void openContainer(string container, vector<Container*> containers){
    for(int i = 0; i < containers.size(); i++){
        if(container == containers[i]->getName()){
            vector<Item*> items = containers[i]->getItem();
            cout<<"updatinng... "<<containers[i]->getStatus()<<endl;
            updateStatus(containers[i], "open");
            cout<<"done... "<<containers[i]->getStatus()<<endl;

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

void updateStatus(Item* item, const char* status){
    item->setStatus(status);
}

void updateStatus(Container* container, const char* status){
    container->setStatus(status);
}

void updateStatus(Creature* creature, const char* status){
    creature->setStatus(status);
}

void updateStatus(Room* room, const char* status){
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

void deleteCommand(string object, vector<Room*> roomVector, vector<Item*> items, vector<Container*> cnts, vector<Creature*> creatures){
    for(int i = 0; i < roomVector.size(); i++){
        if(object == roomVector[i]->getName()){
            cout<<"1"<<endl;
            deleteRoom(object, roomVector);
        }
    }
    for(int i = 0; i < items.size(); i++){
        if(object == items[i]->getName()){
            //deleteItem(i, items);
            cout<<"2"<<endl;
        }
    }
    for(int i = 0; i < cnts.size(); i++){
        if(object == cnts[i]->getName()){
            //deleteContainer(i, cnts);
            cout<<"3"<<endl;
        }
    }
    for(int i = 0; i < creatures.size(); i++){
        if(object == creatures[i]->getName()){
            //deleteCreature(i, creatures);
            cout<<"4"<<endl;
        }
    }
}

void deleteRoom(string object, vector<Room*> roomVector){
    for(int i = 0; i < roomVector.size(); i++){
        vector<Border*> borders = roomVector[i]->getBorder();
        for(int j = 0; j < borders.size(); j++){
          cout<<object<<",                                    "<<borders[j]->getDirection()<<endl;
          if(borders[j]->getDirection() == object){
              borders.erase(borders.begin() + j);
              roomVector[i]->setBorder(borders);
          }
        }
    }
}

// void addCommand(string object, string destination, Room* room){
// 	int flag = 0;
// 	Item* putitm;
// 	for(int i = 0; i < inventory.size(); i++){
// 		if(object == inventory[i]->getName()){
// 			flag = 1;
// 			putitm = inventory[i];
// 			break;
// 		}
// 	}
//
// 	if(!flag){
// 		cout<<"Can't do that\n";
// 		return;
// 	}
//
// 	if(isRoom(destination, room)){
// 		room->setItem(putitm->getName(), room->getItem());
//     return;
// 	}
//
// 	int idx = isContainer(destination, room->getContainer());
//   cout<<idx<<endl;
// 	if(idx != -1){
// 		(room->getContainer())[idx]->setItem(putitm->getName(), (room->getContainer())[idx]->getItem());
// 		return;
// 	}
//
// 	cout<<"Error\n";
// }
//
// bool isRoom(string destination, Room* room){
// 	if(destination == roomState){
// 		return true;
// 	}
//
// 	return false;
// }
//
// bool isContainer(string destination, vector<Container*> containers){
// 	for(int i = 0; i < containers.size(); i++){
// 		if(destination == containers[i]->getName()){
// 			return i;
// 		}
// 	}
//
// 	return -1;
// }
