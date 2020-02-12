#ifndef COMPONETWIRE_H
#define COMPONETWIRE_H



using namespace std;

#include "ComponentWireSection.h"

class ComponentWire
{
	public:
		ComponentWire();
		ComponentWire(int startPositionX, int startPositionY, int endPositionX, int endPositionY, string startInstance, string endInstance);
		ComponentWire(const ComponentWire &In);
		~ComponentWire();
		ComponentWire& operator = (const ComponentWire &In);
		void addLink(int xInit, int yInit, int xEnd, int yEnd);
		std::vector<ComponentWireSection> v_link;
		int getStartX();
		int getStartY();
		int getEndX();
		int getEndY();
		string getInstanceNameStart();
		string getInstanceNameEnd();

	private:
		
		int startPositionX;
		int startPositionY;
		int endPositionX;
		int endPositionY;

		string startInstance;
		string endInstance;
		

};



#endif