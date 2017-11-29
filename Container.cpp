#include "Container.h"

Container::Container(){
    vector<Item*> items;
    // cout<<"Container:";
    setName(NULL);
    // cout<<"Container:";
    setStatus("closed");
    // cout<<"Container:";
    setDescription(NULL);
    // cout<<"Container:";
    setAccept(NULL);
    // cout<<"Container:";
    setItem(NULL,items);
    // cout<<"Container:";
    setTrigger(NULL);
}

Container::Container(xml_node<>* node, vector<Item*> items){
    // cout<<"Container:";
    setName(NULL);
    // cout<<"Container:";
    setStatus("closed");
    // cout<<"Container:";
    setDescription(NULL);
    // cout<<"Container:";
    setAccept(NULL);
    // cout<<"Container:";
    setItem(NULL,items);
    // cout<<"Container:";
    setTrigger(NULL);
    
    if(node == NULL){
        return;
    }

    xml_node<>* temp = node->first_node();

    while(temp != NULL){
        if(strcmp(temp->name(),"name") == 0){
            setName(temp->value());
        }
        else if(strcmp(temp->name(), "status") == 0){
            setStatus(temp->value());
        }
        else if(strcmp(temp->name(), "description") == 0){
            setDescription(temp->value());
        }
        else if(strcmp(temp->name(), "accept") == 0){
            setAccept(temp->value());
        }
        else if(strcmp(temp->name(), "item") == 0){
            setItem(temp->value(), items);
        }
        else if(strcmp(temp->name(), "trigger") == 0){
            setTrigger(temp);
        }
        temp = temp->next_sibling();
    }
}

Container::Container(Container& container){
    this->name = container.name;
    this->status = container.status;
    this->description = container.description;

    for(int i = 0; i < (container.accpt).size(); i++){
        this->accpt.push_back(container.accpt[i]);
    }

    for(int i = 0; i < (container.item).size();i++){
        Item* newitm = new Item(*(container.item[i]));
        this->item.push_back(newitm);
    }

    for(int i = 0; i < (container.trigger).size(); i++){
        Trigger* newtrig = new Trigger(*(container.trigger[i]));
        this->trigger.push_back(newtrig);
    }
}


Container::~Container(){
    for(int i = 0; i < item.size(); i++){
        delete item[i];
    }

    for(int j = 0; j < trigger.size(); j++){
        delete trigger[j];
    }
}

void Container::setName(char* nm){
    // cout<< "Set Name\n";
    name = nm;
}

void Container::setStatus(const char* stat){
    // cout<< "Set Status\n";
    status = stat;
}

void Container::setDescription(char* ds){
    // cout<< "Set Description\n";
    description = ds;
}

void Container::setAccept(char* acpt){
    // cout<<"Set Accept\n";
    
    if(acpt == NULL){
        return;
    }

    accpt.push_back(acpt);
}

void Container::setItem(char* itm, vector<Item*> items){
    // cout<<"Set Item\n";
    if(itm == NULL){
        return;
    }
    
    for(int i = 0; i < items.size(); i++){
        if(strcmp(items[i]->getName(), itm) == 0){
            Item* newitm = new Item(*(items[i]));
            item.push_back(newitm);
            return;
        }
    }

    
}

void Container::setItem(vector<Item*> items){
    item.clear();


    if(items.size() == 0 ){
        return;
    }

    for(int i = 0; i < items.size(); i++){
        Item* itm = new Item(*(items[i]));
        item.push_back(itm);
    }
}



void Container::setTrigger(xml_node<>* node){
    // cout<<"Set Trigger\n";
    if(node == NULL){
        return;
    }

    Trigger* trig = new Trigger(node);
    trigger.push_back(trig);
}

char* Container::getName(){
    // cout<< "Get name\n";
    return name;
}

const char* Container::getStatus(){
    // cout<< "Get status\n";
    return status;
}

char* Container::getDescription(){
    // cout<< "Get Description\n";
    return description;
}

vector<char*> Container::getAccept(){
    return accpt;
}

vector<Item*> Container::getItem(){
    return item;
}

vector<Trigger*> Container::getTrigger(){
    return trigger;
}