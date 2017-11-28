#include "Room.h"

Room::Room(){
    vector<Container*> cntnot;
    vector<Item*> itmnot;
    vector<Creature*> crsnot;
    setName(NULL);
    setStatus(NULL);
    setType("regular");
    setDescription(NULL);
    setBorder(NULL);
    setContainer(NULL,cntnot);
    setItem(NULL,itmnot);
    setCreature(NULL,crsnot);
    setTrigger(NULL);
}

Room::Room(xml_node<>* node, vector<Container*> cnts, vector<Item*> itm, vector<Creature*> crs){
    setName(NULL);
    setStatus(NULL);
    setType("regular");
    setDescription(NULL);
    setBorder(NULL);
    setContainer(NULL,cnts);
    setItem(NULL,itm);
    setCreature(NULL,crs);
    setTrigger(NULL);

    if(node == NULL){
        return;
    }

    xml_node<>* temp = node->first_node();

    while(temp != NULL){
        if(strcmp(temp->name(), "name") == 0){
            setName(temp->value());
        }
        else if(strcmp(temp->name(), "status") == 0){
            setStatus(temp->value());
        }
        else if(strcmp(temp->name(), "type") == 0){
            setType(temp->value());
        }
        else if(strcmp(temp->name(),"description") == 0){
            setDescription(temp->value());
        }
        else if(strcmp(temp->name(),"border") == 0){
            setBorder(temp);
        }
        else if(strcmp(temp->name(),"container") == 0){
            setContainer(temp->value(), cnts);
        }
        else if(strcmp(temp->name(), "item") == 0){
            setItem(temp->value(), itm);
        }
        else if(strcmp(temp->name(), "creature") == 0){
            setCreature(temp->value(),crs);
        }
        else if(strcmp(temp->name(), "trigger") == 0){
            setTrigger(temp);
        }

        temp = temp->next_sibling();
    }
}

Room::Room(Room& rm){
    this->name = rm.name;
    this->status = rm.status;
    this->type = rm.type;
    this->description = rm.description;
    
    for(int i = 0; i < (rm.borders).size(); i++){
        Border* newbrdr = new Border(*(rm.borders[i]));
        this->borders.push_back(newbrdr);
    }

    for(int i = 0; i < (rm.containers).size(); i++){
        Container* newcnt = new Container(*(rm.containers[i]));
        this->containers.push_back(newcnt);
    }

    for(int i = 0; i < (rm.items).size(); i++){
        Item* newitm = new Item(*(rm.items[i]));
        this->items.push_back(newitm);
    }

    for(int i = 0; i < (rm.creatures).size(); i++){
        Creature* newcr = new Creature(*(rm.creatures[i]));
        this->creatures.push_back(newcr);
    }

    for(int i = 0; i < (rm.triggers).size(); i++){
        Trigger* newtrig = new Trigger(*(rm.triggers[i]));
        this->triggers.push_back(newtrig);
    }
}

Room::~Room(){
    for(int i = 0; i < borders.size(); i++){
        delete borders[i];
    }

    for(int i = 0; i < containers.size(); i++){
        delete containers[i];
    }

    for(int i = 0; i < items.size(); i++){
        delete items[i];
    }

    for(int i = 0; i < creatures.size(); i++){
        delete creatures[i];
    }

    for(int i = 0; i < triggers.size(); i++){
        delete triggers[i];
    }
}

void Room::setType(const char* ty){
    // cout<<"FINAL:             Set Type"<<endl;
    type = ty;
}      

void Room::setName(char* nm){
    // cout<< "FINAL:             Set Name\n";
    name = nm;
}

void Room::setStatus(const char* stat){
    // cout<< "FINAL:             Set Status\n";
    status = stat;
}

void Room::setDescription(char* ds){
    // cout<< "FINAL:             Set Description\n";
    description = ds;
}

void Room::setBorder(xml_node<>* node){
    // cout<<"FINAL:             Set Border\n";

    if(node == NULL){
        return;
    }

    Border* newborder = new Border(node);
    borders.push_back(newborder);
}

void Room::setBorder(vector<Border*> border){
  borders.clear();

  if(border.size() == 0){
    return;
  }

  for(int i = 0; i < border.size(); i++){
    Border* brdr = new Border(*border[i]);
    borders.push_back(brdr);
  }
}

void Room::setContainer(char* container, vector<Container*> cnts){
    
    // cout<<"FINAL:             Set Container\n";

    if(container == NULL){
        return;
    }


    for(int i = 0; i < cnts.size(); i++){
        if(strcmp(cnts[i]->getName(),container) == 0){
            Container* newmem = new Container(*(cnts[i]));
            // cout<<newmem->getName()<<endl;
            containers.push_back(newmem);
            return;
        }
    }
}

void Room::setItem(char* item, vector<Item*> itm){
    // cout<<"FINAL:             Set Item\n";
    if(item == NULL){
        return;
    }

    for(int i = 0; i < itm.size(); i++){
        if(strcmp(itm[i]->getName(), item) == 0){
            Item* newitm = new Item(*(itm[i]));
            // cout<<newitm->getName()<<endl;
            items.push_back(newitm);
            return;
        }
    }
}

void Room::setCreature(char* cr, vector<Creature*> crs){
    // cout<<"FINAL:             Set Creature\n";

    if(cr == NULL){
        return;
    }

    for(int i = 0; i < crs.size(); i++){
        if(strcmp(crs[i]->getName(), cr) == 0){
            Creature* newcr = new Creature(*(crs[i]));
            // cout<<newcr->getName()<<endl;
            creatures.push_back(newcr);
            return;
        }
    }
}

void Room::setTrigger(xml_node<>* node){
    // cout<<"FINAL:             SET TRIGGER\n";

    if(node == NULL){
        return;
    }

    Trigger* newtrig = new Trigger(node);
    triggers.push_back(newtrig);
}

char* Room::getName(){
    return name;
}

const char* Room::getStatus(){
    return status;
}

const char* Room::getType(){
    return type;
}

char* Room::getDescription(){
    return description;
}

vector<Border*> Room::getBorder(){
    return borders;
}

vector<Item*> Room::getItem(){
    return items;
}

vector<Container*> Room::getContainer(){
    return containers;
}

vector<Creature*> Room::getCreature(){
    return creatures;
}

vector<Trigger*> Room::getTrigger(){
    return triggers;
}