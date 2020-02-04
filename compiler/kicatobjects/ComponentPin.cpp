#include "ComponentPin.h"
#include <iostream>

ComponentPin :: ComponentPin()
{
    this -> position = 0;
    this -> type = 0;
    this -> orientation = 0;
    this -> name = "";
}


ComponentPin :: ComponentPin(int position, int type, int orientation, string name)
{
    this -> position = position;
    this -> type = type;
    this -> orientation = orientation;
    this -> name = name;
}

ComponentPin :: ComponentPin(const ComponentPin &In)
{
    this -> position = In.position;
    this -> type = In.type;
    this -> orientation = In.orientation;
    this -> name = In.name;
}
ComponentPin :: ~ComponentPin(){}

ComponentPin& ComponentPin :: operator = (const ComponentPin &In)
{
    if(this != &In)
    {
        ComponentPin(In);
        return *this;
    }
}

string ComponentPin :: getName(){return this -> name;};
int ComponentPin :: getPosition(){return this -> position;};
int ComponentPin :: getType(){return this -> type;};