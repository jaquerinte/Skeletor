#ifndef COMPONETWIRE_H
#define COMPONETWIRE_H



using namespace std;

#include "ComponentWireSection.h"

class ComponentWire
{
	public:
		ComponentWire();
		ComponentWire(const ComponentWire &In);
		~ComponentWire();
		ComponentWire& operator = (const ComponentWire &In);
		void addLink(int xInit, int yInit, int xEnd, int yEnd);

	private:
		std::vector<ComponentWireSection> v_link;

};



#endif