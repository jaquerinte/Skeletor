#include "ComponentFunctionSymbol.h"
#include <iostream>

ComponentFunctionSymbol :: ComponentFunctionSymbol()
{
    this -> width = 0;
    this -> heigh = 0;
}


ComponentFunctionSymbol :: ComponentFunctionSymbol(int heigh, int width)
{
    this -> width = width;
    this -> heigh = heigh;
}

ComponentFunctionSymbol :: ComponentFunctionSymbol(const ComponentFunctionSymbol &In)
{
    this -> width = In.width;
    this -> heigh = In.heigh;
    this -> v_pins = In.v_pins;
}
ComponentFunctionSymbol :: ~ComponentFunctionSymbol(){}

ComponentFunctionSymbol& ComponentFunctionSymbol :: operator = (const ComponentFunctionSymbol &In)
{
    if(this != &In)
    {
        ComponentFunctionSymbol(In);
        return *this;
    }
}

void ComponentFunctionSymbol :: addNewPin(int position, int type, int orientation, string name){
     ComponentPin s(position, type, orientation, name);
     this -> v_pins.push_back(s);
}

int ComponentFunctionSymbol :: getWidth(){return this -> width;};
int ComponentFunctionSymbol :: getHeigh(){return this -> heigh;};