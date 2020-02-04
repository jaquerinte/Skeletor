#include "ComponentWire.h"
#include <iostream>

ComponentWire :: ComponentWire(){}

ComponentWire :: ComponentWire(const ComponentWire &In)
{
    this -> v_link = In.v_link;
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
