#ifndef COMPONETPIN_H
#define COMPONETPIN_H


#include <string.h>
#include <string>
#include <vector>
#include <sys/stat.h>

using namespace std;

const int LEFT=1;
const int RIGHT=2;
const int TOP=3;
const int BOTTOM=4;

class ComponentPin
{
	public:
		ComponentPin();
	    ComponentPin(int position, int type, int orientation, string name);
		ComponentPin(int position, int type, int orientation, string name, bool flop);
		ComponentPin(const ComponentPin &In);
		~ComponentPin();
		ComponentPin& operator = (const ComponentPin &In);
		string getName();
		int getPosition();
		int getType();
		bool getFlop();
		void setFlop(bool flop);

	private:
		int position;
		int type;
		int orientation;
		string name;
		bool flop;
};



#endif