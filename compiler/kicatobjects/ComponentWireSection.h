#ifndef COMPONENTWIRESECTION_H
#define COMPONENTWIRESECTION_H


#include <string.h>
#include <string>
#include <vector>
#include <sys/stat.h>

using namespace std;


class ComponentWireSection
{
	public:
		ComponentWireSection();
		ComponentWireSection(int xInit, int yInit, int xEnd, int yEnd);
		ComponentWireSection(const ComponentWireSection &In);
		~ComponentWireSection();
		ComponentWireSection& operator = (const ComponentWireSection &In);

	private:
		int xInit;
		int yInit;
		int xEnd;
		int yEnd;
		

};



#endif