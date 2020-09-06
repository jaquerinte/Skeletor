#include "InstanceComponentFunctionSymbol.h"
#include "../objects/FunctionSymbol.h"
#include <iostream>

InstanceComponentFunctionSymbol :: InstanceComponentFunctionSymbol() 
{
    this -> xbaseposition = 0;
    this -> ybaseposition = 0;
    this -> type = 0;
    this -> positionInComponent = 0;
}

InstanceComponentFunctionSymbol :: InstanceComponentFunctionSymbol(int xbaseposition, int ybaseposition, int type, int positionInComponent)
{
    this -> xbaseposition = xbaseposition;
    this -> ybaseposition = ybaseposition;
    this -> type = type;
    this -> positionInComponent = positionInComponent;
}

InstanceComponentFunctionSymbol :: InstanceComponentFunctionSymbol(const InstanceComponentFunctionSymbol &In)
{
    this -> xbaseposition = In.xbaseposition;
    this -> ybaseposition = In.ybaseposition;
    this -> type = In.type;
    this -> positionInComponent = In.positionInComponent;
    this -> componentDesig = In.componentDesig;
}
InstanceComponentFunctionSymbol :: ~InstanceComponentFunctionSymbol(){}

InstanceComponentFunctionSymbol& InstanceComponentFunctionSymbol :: operator = (const InstanceComponentFunctionSymbol &In)
{
    if(this != &In)
    {
        InstanceComponentFunctionSymbol(In);
        return *this;
    }
}

string InstanceComponentFunctionSymbol :: generateSchematicDesing(string projectName, string functionName, string instanceName, ComponentFunctionSymbol* componentDesig)
{
    string output = "";
    if(this -> type == COMPONENT){
        output += "$Comp\n";
        output += "L " + projectName + ":" + functionName +" U" + std::to_string(this -> positionInComponent + 1) + "\n";
        output += "U 1 1 5DC34FD9\n"; // TODO check what does that number
        output += "P " + std::to_string(XPOSITIONBASE + this -> positionInComponent * CLEARANCEBETWEENMODULES) + " " + std::to_string(YPOSITIONBASE) + "\n";
        output += "F 0 \"" + functionName + " U" + std::to_string(this -> positionInComponent + 1) + "\" H " + std::to_string(XPOSITIONBASE + this -> positionInComponent * CLEARANCEBETWEENMODULES + DEFAULTMODULEWIDTH/2)+ " " + std::to_string(YPOSITIONBASE + TOPCLEARANCETEXT1) + " 50  0000 C CNN\n";
        output += "F 1 \""+ instanceName + "\" H " + std::to_string(XPOSITIONBASE + this -> positionInComponent * CLEARANCEBETWEENMODULES + DEFAULTMODULEWIDTH/2) +" "+ std::to_string(YPOSITIONBASE + TOPCLEARANCETEXT2) +" 50  0000 C CNN\n";
        output += "F 2 \"\" H " + std::to_string(XPOSITIONBASE + this -> positionInComponent * CLEARANCEBETWEENMODULES) + " " + std::to_string(YPOSITIONBASE) +" 50  0001 C CNN\n";
        output += "F 3 \"\" H " + std::to_string(XPOSITIONBASE + this -> positionInComponent * CLEARANCEBETWEENMODULES) + " " + std::to_string(YPOSITIONBASE) +" 50  0001 C CNN\n";
        output += "    1    " + std::to_string(XPOSITIONBASE + this -> positionInComponent * CLEARANCEBETWEENMODULES) + " " + std::to_string(YPOSITIONBASE) + "\n";
        output += "    1    0    0    -1 \n";
        output += "$EndComp\n";
        this -> componentDesig = new ComponentFunctionSymbol(*componentDesig);

    }
    return output;
}

string InstanceComponentFunctionSymbol :: generateSchematicDesing(string projectName, string functionName, string instanceName, std::map<string, FunctionSymbol*> mapOfLeafsModules)
{
    string output = "";
    if (this -> type == SHEET){
        // frist we need to know the max number of imputs for the size
        int number_of_inputs = 0;
        int number_of_outpus = 0;
        for(int w = 0; w < mapOfLeafsModules.at(functionName)->v_inoutwires.size(); ++w){
            if (mapOfLeafsModules.at(functionName)->v_inoutwires.at(this -> positionInComponent).getType() == IN){
                number_of_inputs += 1;
            }
            else{
                number_of_outpus += 1;
            }

        }
        int height_module = std::max(DEFAULTMODULEHEIGHT, (CRERANCEINTOP) + std::max(number_of_inputs,number_of_outpus) * DISTANCEBETWEENPINS);
        int width_module = DEFAULTMODULEWIDTH;
        // create a sheet
        output += "$Sheet\n";
        output += "S " + std::to_string(XPOSITIONBASE + this -> positionInComponent * CLEARANCEBETWEENMODULES) + " " + std::to_string(YPOSITIONBASE-height_module) + " " + std::to_string(width_module) +  " " +std::to_string(height_module)  + "\n"; // todo check with more pins
        output += "U 5E175FE2\n";// TODO check what does that number
        output += "F0 \"" + functionName + "\" 50\n";
        output += "F1 \"" + functionName + ".sch\" 50\n";
        // create the instance and the componet desing of a sheet
        this -> componentDesig = new ComponentFunctionSymbol(height_module, width_module);

        // create connections
        int aux_position_input = YPOSITIONBASE - height_module + CRERANCEINTOP;
        int aux_position_output = YPOSITIONBASE - height_module + CRERANCEINTOP;
        for(int w = 0; w < mapOfLeafsModules.at(functionName)->v_inoutwires.size(); ++w){
            if (mapOfLeafsModules.at(functionName)->v_inoutwires.at(w).getType() == IN){
                output += "F" + std::to_string(w+2) + " \"" + mapOfLeafsModules.at(functionName)->v_inoutwires.at(w).getName() + "\" I L " + std::to_string(XPOSITIONBASE + this -> positionInComponent * CLEARANCEBETWEENMODULES) + " " + std::to_string(aux_position_input)+ " 50\n";
                // add the connections to the desing
                this -> componentDesig -> addNewPin(aux_position_input,mapOfLeafsModules.at(functionName)->v_inoutwires.at(w).getType(),LEFT, mapOfLeafsModules.at(functionName)->v_inoutwires.at(w).getName());
                aux_position_input = aux_position_input + DISTANCEBETWEENPINS;
            }
            else{
                output += "F" + std::to_string(w+2) + " \"" + mapOfLeafsModules.at(functionName)->v_inoutwires.at(w).getName() + "\" O R " + std::to_string(XPOSITIONBASE + this -> positionInComponent * CLEARANCEBETWEENMODULES + DEFAULTMODULEWIDTH) + " " + std::to_string(aux_position_output) + " 50\n";
                if(mapOfLeafsModules.at(functionName)->v_inoutwires.at(w).getFlop())
                {
                    this -> componentDesig -> addNewPin(aux_position_output,mapOfLeafsModules.at(functionName)->v_inoutwires.at(w).getType(),RIGHT, mapOfLeafsModules.at(functionName)->v_inoutwires.at(w).getName());
                }
                else
                {
                    this -> componentDesig -> addNewPin(aux_position_output,mapOfLeafsModules.at(functionName)->v_inoutwires.at(w).getType(),RIGHT, mapOfLeafsModules.at(functionName)->v_inoutwires.at(w).getName());
                }
                
                aux_position_output = aux_position_output + DISTANCEBETWEENPINS;
            }
        }

    }
    return output;
    
}

void InstanceComponentFunctionSymbol :: SetcomponentDesig(ComponentFunctionSymbol* componentDesig){this -> componentDesig = componentDesig;}
int InstanceComponentFunctionSymbol :: getXBasePosition(){return this -> xbaseposition;};
int InstanceComponentFunctionSymbol :: getyBasePosition(){return this -> ybaseposition;};