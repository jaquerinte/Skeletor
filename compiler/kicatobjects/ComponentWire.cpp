#include "ComponentWire.h"
#include <iostream>

ComponentWire :: ComponentWire(){}

ComponentWire :: ComponentWire(int startPositionX, int startPositionY, int endPositionX, int endPositionY, string startInstance, string endInstance)
{
    this -> startPositionX = startPositionX;
    this -> startPositionY = startPositionY;
    this -> endPositionX = endPositionX;
    this -> endPositionY = endPositionY;
    this -> startInstance = startInstance;
    this -> endInstance = endInstance;
}
ComponentWire :: ComponentWire(const ComponentWire &In)
{
    this -> v_link = In.v_link;
    this -> startPositionX = In.startPositionX;
    this -> startPositionY = In.startPositionY;
    this -> endPositionX = In.endPositionX;
    this -> endPositionY = In.endPositionY;
    this -> startInstance = In.startInstance;
    this -> endInstance = In.endInstance;

}
ComponentWire :: ~ComponentWire(){}

void ComponentWire :: addLink(int xInit, int yInit, int xEnd, int yEnd){
    ComponentWireSection s(xInit, yInit, xEnd, yEnd);
    this -> v_link.push_back(s);
}

ComponentWire& ComponentWire :: operator = (const ComponentWire &In)
{
    if(this != &In)
    {
        ComponentWire(In);
        return *this;
    }
}


int ComponentWire :: getStartX(){return this -> startPositionX;}
int ComponentWire :: getStartY(){return this -> startPositionY;}
int ComponentWire :: getEndX(){return this -> endPositionX;}
int ComponentWire :: getEndY(){return this -> endPositionY;}
string ComponentWire :: getInstanceNameStart(){return this -> startInstance;}
string ComponentWire :: getInstanceNameEnd(){return this -> endInstance;}
