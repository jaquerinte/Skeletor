#ifndef COMPONENTWIREMANAGER_H
#define COMPONENTWIREMANAGER_H


using namespace std;

#include "ComponentWire.h"
#include <map>
#include "../common.h"

class ComponentWireManager
{
	public:
		ComponentWireManager();
		ComponentWireManager(const ComponentWireManager &In);
		~ComponentWireManager();
		ComponentWireManager& operator = (const ComponentWireManager &In);
        void addComponetWire(int startPositionX, int startPositionY, int endPositionX, int endPositionY, string startInstance, string endInstance);
        string generateWires();
	private:
        std::vector<ComponentWire> v_kicad_wires;
		
		

};



#endif