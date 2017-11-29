#include "Game.h"
string roomState = "Main";
vector<Item*> inventory;

void startGame(vector<Room*> roomVector, vector<Item*> items, vector<Container*> cnts, vector<Creature*> creatures){
  // start game
    cout<<endl<<"----------Game Starts Now----------"<<endl<<endl;
  string inputFromUser = "";
  roomState = "Entrance";
  cout<<roomVector[0]->getDescription()<<endl;
  bool checker = false;
  int idx = 0;
  bool trgChecker = false;
  while(!checker){
      cout<<">";

      getline(cin, inputFromUser);

      idx = getRoomIdx(roomState, roomVector);
      trgChecker = checkTriggers(inputFromUser, roomVector[idx]);

      if(!trgChecker){
        checker = gotCommand(checker, inputFromUser, roomVector, items, cnts, creatures);
      }
      
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
    else if(tempWord == "drop"){
        iss >> tempWord;
        if(tempWord != ""){
            dropCommand(tempWord, roomVector,items);
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
    /*else if(tempWord == "delete"){
        iss >> tempWord;
        if(tempWord != ""){
            // cout<<"h"<<endl;
            vector<Border*> br;
            // for(int i = 0; i < roomVector.size(); i++){
            //     br = roomVector[i]->getBorder();
            //     for(int j = 0; j < br.size(); j++){
            //         cout<<br[j]->getDirection()<<": "<<br[j]->getName()<<endl;
            //     }
            // }
            //inventoryCommand(roomVector);
            deleteCommand(tempWord, roomVector, items, cnts, creatures);
            // for(int i = 0; i < roomVector.size(); i++){
            //     br = roomVector[i]->getBorder();
            //     for(int j = 0; j < br.size(); j++){
            //         cout<<br[j]->getDirection()<<": "<<br[j]->getName()<<endl;
            //     }
            // }
            //inventoryCommand(roomVector);
        }
        else{
            cout<<"Error"<<endl;
        }
    }*/
    else if(tempWord == "read"){
        iss >> tempWord;
        if(tempWord != ""){
              readItem(tempWord);
        }
        else{
            cout<<"Error"<<endl;
        }
    }

    else if(tempWord == "turn"){
        iss >> tempWord;
        iss >> tempWord2;
        if(tempWord == "on" && tempWord2 != ""){
            char inp[tempWord.size()+1];
            strcpy(inp, tempWord2.c_str());
            // cout <<inp <<endl;
            turnOnItem(inp, roomVector, cnts, creatures);
            for(int i = 0; i < inventory.size(); i++){
                cout<<inventory[i]->getName() << ": "<< inventory[i]->getStatus()<<endl;
            }
        }
        else{
            cout<<"Error"<<endl;
        }
    }
    else if(tempWord == "attack"){
        iss >> tempWord;
        iss >> tempWord2;
        iss >> tempWord2;
        if(tempWord != ""){
            checker = attackCommand(checker, input, tempWord, tempWord2, roomVector, items, cnts, creatures);
        }
        else{
            cout<<"Error"<<endl;
        }
    }
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
              addCommand(tempWord, tempWord2, roomVector, items, creatures,cnts);
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
    else if(tempWord == "add"){
        iss >> tempWord;
        iss >> tempWord2;
        iss >> tempWord2;
        
        if(tempWord != "" && tempWord2 != ""){
            addCommand(tempWord, tempWord2, roomVector, items, creatures, cnts);
        }
    }
    // Check for behind the scenes commands
    else {
        cout<<"Error"<<endl;
    }
    return checker;
}

bool behindCommand(bool checker, string input, vector<Room*> roomVector, vector<Item*> items, vector<Container*> cnts, vector<Creature*> creatures){
    //cout<<"called behindCommand"<<endl;
    string tempWord;
    string tempWord2;
    istringstream iss(input);
    iss >> tempWord;
    // cout<<tempWord<<endl;
    int idx = getRoomIdx(roomState, roomVector);
    if(tempWord == "Add"){
        iss >> tempWord;
        iss >> tempWord2;
        iss >> tempWord2;
      //cout<<"add"<<endl;
        addCommand(tempWord, tempWord2, roomVector, items, creatures,cnts);
    }
    else if(tempWord == "Delete"){
    //   cout<<"delete"<<endl;

        iss >> tempWord;
        if(tempWord != ""){
            // cout<<"h"<<endl;
            vector<Border*> br;
            // for(int i = 0; i < roomVector.size(); i++){
            //     br = roomVector[i]->getBorder();
            //     // for(int j = 0; j < br.size(); j++){
            //     //     cout<<br[j]->getDirection()<<": "<<br[j]->getName()<<endl;
            //     // }
            // }
            //inventoryCommand(roomVector);
            deleteCommand(tempWord, roomVector, items, cnts, creatures);
            // for(int i = 0; i < roomVector.size(); i++){
            //     br = roomVector[i]->getBorder();
            //     // for(int j = 0; j < br.size(); j++){
            //     //     cout<<br[j]->getDirection()<<": "<<br[j]->getName()<<endl;
            //     // }
            // }
            // inventoryCommand(roomVector);
        }
      }
    else if(tempWord == "Update"){
        //   cout<<"update"<<endl;

            iss >> tempWord;
            iss >> tempWord2;
            iss >> tempWord2;
            vector<Item*> is;
            vector<Container*> cs;
            vector<Creature*> crs;
            if(tempWord != "" && tempWord2 != ""){
                
                if(inventoryPresent(tempWord)){
                    char* inp = (char*)malloc(sizeof(*inp) * (tempWord2.size()+1)) ;
                    strcpy(inp, tempWord2.c_str());
                    for(int i = 0; i < inventory.size(); i++){
                        if(tempWord == inventory[i]->getName()){
                            //updateStatus(inventory[i], inp);
                            inventory[i]->setStatus(inp);
                            cout<<inventory[i]->getStatus()<<endl;;
                            return checker;
                        }
                    }
                    
                }

                for(int i = 0; i < roomVector.size(); i++){
                    if(tempWord == roomVector[i]->getName()){
                        char inp[tempWord2.size()+1];
                        strcpy(inp, tempWord2.c_str());
                        updateStatus(roomVector[i], inp);
                        return checker;
                    }
                    is = roomVector[i]->getItem();
                    for(int j = 0; j < is.size(); j++){
                        if(tempWord == is[j]->getName()){
                            char inp[tempWord2.size()+1];
                            strcpy(inp, tempWord2.c_str());
                            updateStatus(is[j], inp);
                            return checker;
                        }
                    }
                    cs = roomVector[i]->getContainer();
                    for(int j = 0; j < cs.size(); j++){
                        is = cs[j]->getItem();
                        if(cs[j]->getName() == tempWord){
                            char inp[tempWord2.size()+1];
                            strcpy(inp, tempWord2.c_str());
                            updateStatus(cs[j], inp);
                            return checker;
                        }
                        is = cs[j]->getItem();
                        for(int k = 0; k < is.size(); k++){
                            if(tempWord == is[k]->getName()){
                                char inp[tempWord2.size()+1];
                                strcpy(inp, tempWord2.c_str());
                                updateStatus(is[k], inp);
                                return checker;
                            }
                        }
                    }
                    crs = roomVector[i]->getCreature();
                    for(int j = 0; j < crs.size(); j++){
                        if(tempWord == crs[j]->getName()){
                            char inp[tempWord2.size()+1];
                            strcpy(inp, tempWord2.c_str());
                            updateStatus(crs[j], inp);
                            return checker;
                        }
                    }
                }
                cout<<"Not found. - Behind the Scenes."<<endl;
            }
            else{
                cout<<"Error Behind the Scenes."<<endl;
            }
        }
    else if(input == "Game Over"){
          cout<<"go"<<endl;
            // checker = openExit();
            checker = gameOver();
            // return checker;
        }
    else{
           cout<<"gotcom"<<endl;
            checker = gotCommand(checker, input, roomVector, items, cnts, creatures);
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
        if(input == inventory[i]->getName()){
            cout<<"This is already in your inventory!\n";
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
                vector<Item*> updateditm = deleteItemFrom(it,newitm->getName());
                roomVector[idx]->setItem(updateditm);
                return;
            }
        }
        cout<<"Error"<<endl;
        return;
    }

    vector<Container*> containers = roomVector[idx]->getContainer();
    for(int i = 0; i < containers.size(); i++){
        if(container == containers[i]->getName()){
            // cout<<containers[i]->getStatus()<<endl;
            if(containers[i]->getStatus() != "open"){
                cout<<"You need to open that container\n";
                return;
            }

            vector<Item*> itm = containers[i]->getItem();
            for(int j = 0; j < itm.size();j++){
                if(input == itm[j]->getName()){
                    cout<<"Item "<<itm[j]->getName()<<" added to inventory."<<endl;
                    Item* newitm = new Item(*itm[j]);
                    inventory.push_back(newitm);
                    vector<Item*> updateditm = deleteItemFrom(itm,newitm->getName());
                    containers[i]->setItem(updateditm);
                    return;
                }
            }
        }
    }

    cout<<"Error"<<endl;
}

void dropCommand(string input, vector<Room*> roomVector, vector<Item*> items){
    int idx =  getRoomIdx(roomState, roomVector);
    vector<Item*> it = roomVector[idx]->getItem();
    for(int i = 0; i < inventory.size(); i++){
        if(input == inventory[i]->getName()){
            cout<<inventory[i]->getName()<<" dropped."<<endl;
            inventory = deleteItemFrom(inventory, input);
            char inp[input.size()+1];
            strcpy(inp, input.c_str());
            roomVector[idx]->setItem(inp,items);
            cout<<"ITEMS IN THE ROOM: ";
            for(int q = 0; q < (roomVector[idx]->getItem().size()); q++){
                cout<<(roomVector[idx]->getItem())[q]->getName();
            }
            cout<<endl;
            return;
        }
    }
    cout<<"Error"<<endl;
}

void openContainer(string container, vector<Container*> containers){
    for(int i = 0; i < containers.size(); i++){
        if(container == containers[i]->getName()){
            vector<Item*> itm = containers[i]->getItem();
            // cout<<"updatinng... "<<containers[i]->getStatus()<<endl;
            updateStatus(containers[i], "open");
            // cout<<"done... "<<containers[i]->getStatus()<<endl;

            if(itm.size() == 0){
                cout<<"Contains no elements\n";
                return;
            }

            for(int j = 0; j < itm.size(); j++){
                cout<<itm[j]->getName()<<endl;
            }
            return;

        }
    }
    cout<<"couldn't find the container\n";
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

void turnOnItem(string item, vector<Room*> roomVector, vector<Container*> cnts, vector<Creature*> creatures){

    for(int i = 0; i < inventory.size(); i++){

        if(inventory[i]->getName() == item){
            // cout<<"\n\n\n\n"<<items[i]->getName()<<"\n\n\n"<<endl;
            
            if(inventory[i]->getTurnOn() != NULL && inventory[i]->getTurnOn()->getPrint() != NULL){
                cout<<inventory[i]->getTurnOn()->getPrint()<<endl;
            }
            else{
                cout<<"Can't turn on.. Item doesn't have that capability"<<endl;
                return;
            }
            bool checker;
    
            char* c = inventory[i]->getTurnOn()->getAction();
            string inputTmp = string(c);
                        //   cout<<inputTmp<<endl;
            vector<Item*> nothing;
            checker = behindCommand(checker, inputTmp, roomVector, nothing, cnts, creatures);
            

            return;
        }

    }

    cout<<"Can't turn on... Item not found"<<endl;

}

bool gameOver(){
    cout<<"Victory!";
    return true;
}

void readItem(string item){
    if(inventory.empty()){
        cout<<"Item not found in inventory!"<<endl;
        return;
    }

    for(int i = 0; i < inventory.size();i++){
        if(item == inventory[i]->getName()){

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
            // cout<<"1"<<endl;
            deleteRoom(object, roomVector);
            return;
        }
    }
    for(int i = 0; i < items.size(); i++){
        if(object == items[i]->getName()){
            deleteItem(object, roomVector);
            
            // cout<<"2"<<endl;
            return;
        }
    }
    for(int i = 0; i < cnts.size(); i++){
        if(object == cnts[i]->getName()){
            deleteContainer(object, roomVector);
            // cout<<"3"<<endl;
            return;
        }
    }
    for(int i = 0; i < creatures.size(); i++){
        if(object == creatures[i]->getName()){
            deleteCreature(object, roomVector);        
            // cout<<"4"<<endl;
            for(int i = 0; i < roomVector.size(); i++){
        cout<<roomVector[i]->getName()<<": ";
        vector<Creature*> qq = roomVector[i]->getCreature();
        
        for(int j = 0; j < qq.size(); j++){
            cout<<qq[j]->getName();
        }
        cout<<endl;
    }
            return;
        }
    }
    
    
}

void deleteRoom(string object, vector<Room*> roomVector){

    if(object == ""){
        return;
    }

    for(int i = 0; i < roomVector.size(); i++){
        vector<Border*> borders = roomVector[i]->getBorder();
        for(int j = 0; j < borders.size(); j++){
        //   cout<<object<<",                                    "<<borders[j]->getDirection()<<endl;
          if(borders[j]->getDirection() == object){
              borders.erase(borders.begin() + j);
              roomVector[i]->setBorder(borders);
              return;
          }
        }
    }
}

vector<Item*> deleteItemFrom(vector<Item*> items, string item){
    
    if(item == ""){
        cout<<"Error\n";
    }

    for(int i = 0; i < items.size(); i++){
        if(item == items[i]->getName()){
            items.erase(items.begin() + i);
        }
    }

    return items;

}

void deleteItem(string object, vector<Room*> roomVector){

    if(object == ""){
        return;
    }

    vector<Item*> temp;
    for(int i = 0; i < roomVector.size(); i++){
        //for rooms itself
        temp = deleteItemFrom(roomVector[i]->getItem(),object);
        roomVector[i]->setItem(temp);
        for(int j = 0; j < ((roomVector[i])->getContainer()).size(); j++){
            temp = deleteItemFrom(((roomVector[i])->getContainer())[j]->getItem(),object);
            ((roomVector[i])->getContainer())[j]->setItem(temp);
        }
    }   

}

void deleteContainer(string object, vector<Room*> roomVector){

    if(object == ""){
        return;
    }
    
    for(int i = 0; i < roomVector.size(); i++){
        
        vector<Container*> container = roomVector[i]->getContainer();
        
        for(int j = 0; j < container.size();j++){
            if(container[j]->getName() == object){
                container.erase(container.begin() + j);
                roomVector[i]->setContainer(container);
            }
        }

    }
}

void deleteCreature(string object, vector<Room*> roomVector){
    if(object == ""){
        return;
    }

    for(int i = 0; i < roomVector.size(); i++){
        vector<Creature*> creature = roomVector[i]->getCreature();
        
        for(int j = 0; j < creature.size(); j++){
            if(object == creature[j]->getName()){
                cout<<"deleted "<<creature[j]->getName()<<endl;
                creature.erase(creature.begin() + j);
                roomVector[i]->setCreature(creature);

            }
        }
    }

    // for(int i = 0; i < roomVector.size(); i++){
    //     cout<<roomVector[i]->getName()<<": ";
    //     vector<Creature*> qq = roomVector[i]->getCreature();
        
    //     for(int j = 0; j < qq.size(); j++){
    //         cout<<qq[j]->getName();
    //     }
    //     cout<<endl;
    // }
}

// bool attackCommand(bool checker, string input, string tempCreature, string tempItem, vector<Room*> roomVector, vector<Item*> items, vector<Container*> cnts, vector<Creature*> creatures){
//     bool check = inventoryPresent(tempItem);
//     if(check == false){
//         cout<<"Don't have that item in inventory."<<endl;
//         return checker;
//     }
//     int idx = getRoomIdx(roomState, roomVector);
//     vector<Creature*> creaturesTmp = roomVector[idx]->getCreature();
//     Condition* cond;
//     for(int i = 0; i < creaturesTmp.size(); i++){
//         if(tempCreature == creaturesTmp[i]->getName()){
//             vector<char*> vuln = creaturesTmp[i]->getVulnerability();
//             for(int j = 0; j < vuln.size(); j++){
//                 if(tempItem == vuln[j]){
//                   // CONDITION
//                     cout<<"You assault the "<<creaturesTmp[i]->getName()<<" with "<<tempItem<<"."<<endl;

//                     // if(creaturesTmp[i]->getAttack() == NULL || creaturesTmp[i]->getAttack()->getAction().size() == 0){
//                     //     cout<<"HEre"<<endl;
//                     //     return true;
//                     // }

//                     vector<char*> c = creaturesTmp[i]->getAttack()->getAction();
//                     for(int k = 0; k < c.size(); k++){
//                       string inputTmp = string(c[k]);
//                     //   cout<<inputTmp<<endl;
//                       checker = behindCommand(checker, inputTmp, roomVector, items, cnts, creatures);
//                     }
//                     return checker;
//                 }
//             }
//             cout<<"Not items vulnerability\n";
//         }
//     }
//     cout<<"Creature not found"<<endl;
// }

bool inventoryPresent(string tempItem){
    for(int i = 0; i < inventory.size(); i++){
        if(tempItem == inventory[i]->getName()){
            return true;
        }
    }
    return false;
}

void addCommand(string object, string destination, vector<Room*> rooms, vector<Item*> items, vector<Creature*> creatures, vector<Container*> containers){
    
    if(object == ""){
        return;
    }

    cout <<object << "to " << destination<< endl;

    if(destination == "inventory"){
        cout<<"inventory"<<endl;
        addToItem(object, items);
        return;
    }

    for(int i = 0; i < rooms.size(); i++){
        if(rooms[i]->getName() == destination){
            cout<<"ROOM"<<endl;
            addToRoom(object, rooms[i], items, creatures, containers);
            return;
        }
        
        vector<Container*> c = rooms[i]->getContainer();
        for(int j = 0; j < c.size(); j++){
            if(c[j]->getName() == destination){
                cout<<"Container"<<endl;
                Container* cnn = addToContainer(object, c[j], items);
                if(cnn != NULL){
                    rooms[i]->setContainer(cnn->getName(),containers);
                }
                return;
            }
        }
    }
}

Container* addToContainer(string object, Container* containers, vector<Item*> items){
    
    for(int i = 0; i < items.size(); i++){
        if(object == items[i]->getName()){
            Item* newitm = new Item(*(items[i]));
            vector<Item*> cr = containers->getItem();
            cr.push_back(newitm);
            containers->setItem(cr);
            return containers;
        }
    }

    return NULL;
}

void addToRoom(string object, Room* room, vector<Item*> items, vector<Creature*> creatures, vector<Container*> containers){

    for(int i = 0; i < items.size(); i++){
        if(object == items[i]->getName()){
            cout<<"item\n";
            Item* newitm = new Item(*(items[i]));
            room->setItem(newitm->getName(),items);
            return;
        }
    }

    for(int i = 0; i < creatures.size(); i++){
        if(object == creatures[i]->getName()){
            cout<<"creature\n";
            Creature* newcr = new Creature(*(creatures[i]));
            room->setCreature(newcr->getName(),creatures);
            return;
        }
    }

    for(int i = 0; i < containers.size(); i++){
        if(object == containers[i]->getName()){
            cout<<"container\n";
            Container* newcn = new Container((*containers[i]));
            room->setContainer(newcn->getName(),containers);
            return;
        }
    }
}

void addToItem(string object, vector<Item*> items){
    for(int i = 0; i > items.size();i++){
        if(object == items[i]->getName()){
            inventory.push_back(items[i]);

        }
    }
}

bool isRoom(string destination, Room* room){
	if(destination == roomState){
		return true;
	}

	return false;
}

bool isContainer(string destination, vector<Container*> containers){
	for(int i = 0; i < containers.size(); i++){
		if(destination == containers[i]->getName()){
			return i;
		}
	}

	return -1;
}

bool conditionCheck(string object, Condition* condition, vector<Room*> roomVector){
      // check if there's no condition
      if(condition == NULL){
          return true;
      }
      // check conditions without "owner"
      if(condition->getOwner() == NULL){
        cout<<"no owner"<<endl;
        // check condition's object
        if(condition->getObject() != object){
            return false;
        }
        // check if object used to attack is in inventory
        if(!inventoryPresent(object)){
            return false;
        }
        // check if condition's status meets object's status (object - used to attack)
        Item* itm = inventoryObject(object);
        string one = itm->getStatus();
        char* two = condition->getStatus();
        if(one != two){
            return false;
        }
        // if all is satisfied
        return true;
      } // with "owner"
      else{
          cout<<"owner"<<endl;
          bool hasTmp;
          bool has = condition->getHas();
          string owner = string(condition->getOwner());
          if(owner == "inventory"){
              // cout<<"owner: inventory"<<endl;
              hasTmp = inventoryPresent(condition->getObject());
              return match(has, hasTmp);
          }
          else{
              for(int i = 0; i < roomVector.size(); i++){
                  if(roomVector[i]->getName() == owner){
                      vector<Item*> r_i = roomVector[i]->getItem();
                      for(int ii = 0; ii < r_i.size(); ii++){
                          if(r_i[ii]->getName() == condition->getObject()){
                              hasTmp = true;
                              return match(has, hasTmp);
                          }
                      }
                      hasTmp = false;
                      return match(has, hasTmp);
                  }
                  vector<Container*> c = roomVector[i]->getContainer();
                  for(int j = 0; j < c.size(); j++){
                      if(c[j]->getName() == owner){
                          vector<Item*> r_i = c[j]->getItem();
                          for(int ii = 0; ii < r_i.size(); ii++){
                              if(r_i[ii]->getName() == condition->getObject()){
                                  hasTmp = true;
                                  return match(has, hasTmp);
                              }
                          }
                          hasTmp = false;
                          return match(has, hasTmp);
                      }
                  }
              }
          }
      }
      // every condition meets
      return true;
}

Item* inventoryObject(string obj){
    for(int i = 0; i < inventory.size(); i++){
        if(obj == inventory[i]->getName()){
            return inventory[i];
        }
    }
    return false;
}

bool attackCommand(bool checker, string input, string tempCreature, string tempItem, vector<Room*> roomVector, vector<Item*> items, vector<Container*> cnts, vector<Creature*> creatures){
    bool check = inventoryPresent(tempItem);
    if(check == false){
        cout<<"Don't have that item in inventory."<<endl;
        return checker;
    }
    int idx = getRoomIdx(roomState, roomVector);
    vector<Creature*> creaturesTmp = roomVector[idx]->getCreature();
    Condition* cond;

    for(int i = 0; i < creaturesTmp.size(); i++){
        if(tempCreature == creaturesTmp[i]->getName()){
            vector<char*> vuln = creaturesTmp[i]->getVulnerability();

            if(creaturesTmp[i]->getAttack() == NULL){
                cout<<"Error"<<endl;
                return checker;
            }

            cond = (creaturesTmp[i]->getAttack())->getCondition();
            if(conditionCheck(tempItem, cond, roomVector)){
                cout<<"true"<<endl;
                for(int j = 0; j < vuln.size(); j++){
                    if(tempItem == vuln[j]){
                      //FIXX!!!!! condition returns 1 if it was met
                        cout<<"You assault the "<<creaturesTmp[i]->getName()<<" with "<<tempItem<<"."<<endl;
                        vector<char*> c = creaturesTmp[i]->getAttack()->getAction();
                        for(int k = 0; k < c.size(); k++){
                          string inputTmp = string(c[k]);
                        //   cout<<inputTmp<<endl;
                          checker = behindCommand(checker, inputTmp, roomVector, items, cnts, creatures);
                        }
                        cout<<creaturesTmp[i]->getAttack()->getPrint()<<endl;
                        return checker;
                    }
                }
                cout<<"Not items vulnerability\n";
            }
            cout<<"Condition not met\n";
            return checker;
        }
    }
    cout<<"Creature not found"<<endl;
}

bool checkTriggers(string command, Room* room){
    if(command == ""){
      return false;
    }
    // string tempWord;
    // string tempWord2;
    // istringstream iss(command);
    // iss >> tempWord;

    vector<Trigger*> trigs;
    string cmdTrig;
    bool condPassed;
    trigs = room->getTrigger();
    for(int i = 0; i < trigs.size(); i++){
        cmdTrig = trigs[i]->getCommand();
        if(cmdTrig == command){
            cout<<"room trig"<<endl;
            
            //activate trigger
            return true;
        }
    }
    vector<Item*> itms = room->getItem();
    for(int i = 0; i < itms.size(); i++){
        trigs = itms[i]->getTrigger();
        for(int j = 0; j < trigs.size(); j++){
            cmdTrig = trigs[j]->getCommand();
            if(cmdTrig == command){
                cout<<"item trig"<<endl;
                //activate trigger
                return true;
            }
        }
    }
    vector<Container*> cnts = room->getContainer();
    for(int i = 0; i < cnts.size(); i++){
        trigs = cnts[i]->getTrigger();
        for(int j = 0; j < trigs.size(); j++){
            cmdTrig = trigs[j]->getCommand();
            if(cmdTrig == command){
                cout<<"container trig"<<endl;
                //activate trigger
                return true;
            }
        }
        itms = cnts[i]->getItem();
        for(int k = 0; k < itms.size(); k++){
            trigs = itms[k]->getTrigger();
            for(int l = 0; l < trigs.size(); l++){
                cmdTrig = trigs[l]->getCommand();
                if(cmdTrig == command){
                    cout<<"item in container trig"<<endl;
                    //activate trigger
                    return true;
                }
            }
        }
    }
    vector<Creature*> crts = room->getCreature();
    for(int i = 0; i < crts.size(); i++){
        trigs = crts[i]->getTrigger();
        for(int j = 0; j < trigs.size(); j++){
            cmdTrig = trigs[j]->getCommand();
            if(cmdTrig == command){
                cout<<"creature trig"<<endl;
                //activate trigger
                return true;
            }
        }
    }
}

bool match(bool has, bool hasTmp){
    if((hasTmp && has) || (!hasTmp && !has)){
        return true;
    }
    else{
        return false;
    }
}