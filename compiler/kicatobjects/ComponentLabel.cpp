#include "ComponentLabel.h"
#include <iostream>
ComponentLabel :: ComponentLabel()
{
    this -> typeOfLabel = 0;
    this -> type = 0;
    this -> xCoordinate = 0;
    this -> yCoordinate = 0;
    this -> name = "";
}
ComponentLabel :: ComponentLabel(int typeOfLabel, int type, string name, int xCoordinate, int yCoordinate)
{
    this -> typeOfLabel = typeOfLabel;
    this -> type = type;
    this -> xCoordinate = xCoordinate;
    this -> yCoordinate = yCoordinate;
    this -> name = name;
}
ComponentLabel :: ComponentLabel(const ComponentLabel &In)
{
    this -> typeOfLabel = In.typeOfLabel;
    this -> type = In.type;
    this -> xCoordinate = In.xCoordinate;
    this -> yCoordinate = In.yCoordinate;
    this -> name = In.name;
}
ComponentLabel :: ~ComponentLabel(){}

ComponentLabel& ComponentLabel :: operator = (const ComponentLabel &In)
{
    if(this != &In)
    {
        ComponentLabel(In);
        return *this;
    }
}

string ComponentLabel :: getName() {return this->name;};
int ComponentLabel :: getXPosition(){return this->xCoordinate;};
int ComponentLabel :: getYPosition(){return this->yCoordinate;};
int ComponentLabel :: getTypeOfLabel(){return this->typeOfLabel;};
int ComponentLabel :: getTypeLabel(){return this->type;};