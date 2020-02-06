#ifndef COMPONETLABEL_H
#define COMPONETLABEL_H


#include <string.h>
#include <string>
#include <vector>
#include <sys/stat.h>

using namespace std;

const int GLABEL=1;
const int HLABEL=1;

class ComponentLabel
{
	public:
		ComponentLabel();
	    ComponentLabel(int typeOfLabel, int type, string name, int xCoordinate, int yCoordinate);
		ComponentLabel(const ComponentLabel &In);
		~ComponentLabel();
		ComponentLabel& operator = (const ComponentLabel &In);
		string getName();
		int getXPosition();
        int getYPosition();
		int getTypeOfLabel();
        int getTypeLabel();

	private:
		int typeOfLabel;
		int type;
		string name;
        int xCoordinate;
        int yCoordinate;
};



#endif