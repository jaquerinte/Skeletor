#include "ComponentWireManager.h"


ComponentWireManager :: ComponentWireManager(){}

ComponentWireManager :: ComponentWireManager(const ComponentWireManager &In)
{
this -> v_kicad_wires = In.v_kicad_wires;
}
ComponentWireManager :: ~ComponentWireManager(){}

ComponentWireManager& ComponentWireManager :: operator = (const ComponentWireManager &In)
{
    if(this != &In)
    {
        ComponentWireManager(In);
        return *this;
    }
}

void ComponentWireManager :: addComponetWire(int startPositionX, int startPositionY, int endPositionX, int endPositionY, string startInstance, string endInstance)
{
    ComponentWire s(startPositionX, startPositionY, endPositionX, endPositionY ,startInstance, endInstance);
    this -> v_kicad_wires.push_back(s);

}

string ComponentWireManager :: generateWires(){
    int numberOfSubDivisionsOfBottomChannel = 1;
    int availableChannelBottom = 1;
   
    std::map<string, tuple<int,int,int,int >> mapOfSpaces;
    /*
    mapOfSpaces
    Stores the available input and output channels of a instance.
    0: is the input channel available
    1: is the number of subdivisions of input
    2: is the output channel available
    3: is the number of subdivisions of output
    */

    string output = "";
    for(unsigned int i = 0; i < this->v_kicad_wires.size(); ++i){
        // check cases
        if (abs(this->v_kicad_wires.at(i).getEndX() - this->v_kicad_wires.at(i).getStartX()) <= CLEARANCEBETWEENMODULES)
        {
            // only connection between adjacents modules print normaly
            output += "Wire Wire Line\n" + std::to_string(this->v_kicad_wires.at(i).getStartX()) + " "+ std::to_string(this->v_kicad_wires.at(i).getStartY())+ " " + std::to_string(this->v_kicad_wires.at(i).getEndX()) +" " + std::to_string(this->v_kicad_wires.at(i).getEndY()) + "\n";

        }
        else
        {
            // need to use the channels
            int inputChannelAvailable = 1;
            int subdivisonInputChannel = 1;
            // first check the data of the initial module
            if (mapOfSpaces.find(this -> v_kicad_wires.at(i).getInstanceNameStart()) == mapOfSpaces.end()) 
            {
                // not found create initial module
                mapOfSpaces.insert({v_kicad_wires.at(i).getInstanceNameStart(), tuple<int,int,int,int>(2,1,1,1)});
            } 
            else 
            {
                // get the data for the input channel TODO CHANGE FOR THE OUTPUT CHANNEL (the naming)
                // found check get aviable channels
                inputChannelAvailable  = get<0>(mapOfSpaces.at(this -> v_kicad_wires.at(i).getInstanceNameStart()));
                subdivisonInputChannel = get<1>(mapOfSpaces.at(this -> v_kicad_wires.at(i).getInstanceNameStart()));
                // inclement the available channels
                if (inputChannelAvailable >= NUMBEROFBASEINPUTCHANELS)
                {
                    // create a subdivion and reset
                    get<0>(mapOfSpaces.at(this -> v_kicad_wires.at(i).getInstanceNameStart())) = 1;
                    get<1>(mapOfSpaces.at(this -> v_kicad_wires.at(i).getInstanceNameStart())) = subdivisonInputChannel + 1;
                }
                else
                {
                    // increment the available channel
                    get<0>(mapOfSpaces.at(this -> v_kicad_wires.at(i).getInstanceNameStart())) = inputChannelAvailable + 1;
                }
            }
            // get the data for the output channel TODO CHANGE FOR THE INPUT CHANNEL (the naming)
            int outputChannelAvailable = 1;
            int subdivisonOutputChannel = 1;
            if (mapOfSpaces.find(this -> v_kicad_wires.at(i).getInstanceNameEnd()) == mapOfSpaces.end()){
                mapOfSpaces.insert({v_kicad_wires.at(i).getInstanceNameEnd(), tuple<int,int,int,int>(1,1,2,1)});
            }
            else
            {
                outputChannelAvailable  = get<2>(mapOfSpaces.at(this -> v_kicad_wires.at(i).getInstanceNameEnd()));
                subdivisonOutputChannel = get<3>(mapOfSpaces.at(this -> v_kicad_wires.at(i).getInstanceNameEnd()));
                // inclement the available channels
                if (outputChannelAvailable >= NUMBEROFOUTPUTCHANELS)
                {
                    // create a subdivion and reset
                    get<2>(mapOfSpaces.at(this -> v_kicad_wires.at(i).getInstanceNameEnd())) = 1;
                    get<3>(mapOfSpaces.at(this -> v_kicad_wires.at(i).getInstanceNameEnd())) = subdivisonOutputChannel + 1;
                }
                else
                {
                    // increment the available channel
                    get<2>(mapOfSpaces.at(this -> v_kicad_wires.at(i).getInstanceNameEnd())) = outputChannelAvailable + 1;
                }
            }
            

            // create the wires
            // frist wire for grab the channel
            int xPositionEndGrabWire = this->v_kicad_wires.at(i).getStartX() + (MINIMUNCLEARANCE + ((subdivisonInputChannel-1) * OFFSETCLEARANCE)) + (inputChannelAvailable * (SPACEBEWEENWIRES/subdivisonInputChannel)); 
            //output += "Wire Wire Line\n" + std::to_string() + " "+ std::to_string()+ " " + std::to_string() +" " + std::to_string() + "\n";
            output += "Wire Wire Line\n" + std::to_string(this->v_kicad_wires.at(i).getStartX()) + " "+ std::to_string(this->v_kicad_wires.at(i).getStartY())+ " " + std::to_string(xPositionEndGrabWire) +" " + std::to_string(this->v_kicad_wires.at(i).getStartY()) + "\n";
            
            // create the input wire in the channel
            int yPositionEndInputChannel = (FIRSTBOTTOMCHANELYCORDINATE + (MINIMUNCLEARANCE +((numberOfSubDivisionsOfBottomChannel-1) * OFFSETCLEARANCE)) + availableChannelBottom * (SPACEBEWEENWIRES/numberOfSubDivisionsOfBottomChannel) );
            if (availableChannelBottom >= NUMBEROFBOTTOMCHANELS){
                // create a subdivion and reset
                numberOfSubDivisionsOfBottomChannel +=1;
                availableChannelBottom = 1;
            }
            else
            {
                availableChannelBottom += 1;
            }  
            output += "Wire Wire Line\n" + std::to_string(xPositionEndGrabWire) + " "+ std::to_string(this->v_kicad_wires.at(i).getStartY())+ " " + std::to_string(xPositionEndGrabWire) + " " + std::to_string(yPositionEndInputChannel) + "\n";
            // create the bottom wire in the channel
            int xPositionEndFinalWire = this->v_kicad_wires.at(i).getEndX() - (MINIMUNCLEARANCE + ((subdivisonOutputChannel-1) * OFFSETCLEARANCE)) - (outputChannelAvailable * (SPACEBEWEENWIRES/subdivisonOutputChannel)); ;
            int xPositionEndBottomChannel = xPositionEndGrabWire ; 
            output += "Wire Wire Line\n" + std::to_string(xPositionEndGrabWire) + " "+ std::to_string(yPositionEndInputChannel)+ " " + std::to_string(xPositionEndFinalWire) + " " + std::to_string(yPositionEndInputChannel) + "\n";

            // bottom to input wire connection
            output += "Wire Wire Line\n" + std::to_string(xPositionEndFinalWire) + " "+ std::to_string(yPositionEndInputChannel)+ " " + std::to_string(xPositionEndFinalWire) +" " + std::to_string(this->v_kicad_wires.at(i).getEndY()) + "\n";
            // final wire
            output += "Wire Wire Line\n" + std::to_string(xPositionEndFinalWire) + " "+ std::to_string(this->v_kicad_wires.at(i).getEndY())+ " " + std::to_string(this->v_kicad_wires.at(i).getEndX()) +" " + std::to_string(this->v_kicad_wires.at(i).getEndY()) + "\n";
            
            
        }
        
    }

return output;
}