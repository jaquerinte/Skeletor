#include "ComponentWireSection.h"
#include <iostream>

ComponentWireSection :: ComponentWireSection()
{

    this -> xInit = 0;
    this -> yInit = 0;
    this -> xEnd = 0;
    this -> yEnd = 0;
}


ComponentWireSection :: ComponentWireSection(int xInit, int yInit, int xEnd, int yEnd)
{
    this -> xInit = xInit;
    this -> yInit = yInit;
    this -> xEnd = xEnd;
    this -> yEnd = yEnd;
}

ComponentWireSection :: ComponentWireSection(const ComponentWireSection &In)
{
    this -> xInit = In.xInit;
    this -> yInit = In.yInit;
    this -> xEnd = In.xEnd;
    this -> yEnd = In.yEnd;
}
ComponentWireSection :: ~ComponentWireSection(){}

ComponentWireSection& ComponentWireSection :: operator = (const ComponentWireSection &In)
{
    if(this != &In)
    {
        ComponentWireSection(In);
        return *this;
    }
}