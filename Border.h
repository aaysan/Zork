#ifndef BORDER_H
#define BORDER_H
#include "rapidxml.hpp"
#include <string.h>
#include <iostream>
using namespace std;
using namespace rapidxml;

class Border{
private:
    char* direction;
    char* name;
public:
    Border();
    Border(xml_node<>* node);
    Border(Border& brdr);
    void setDirection(char* direc);
    void setName(char* nm);
    char* getDirection();
    char* getName();
};

#endif