#ifndef COMPONETFUNCTIONSYMBOL_H
#define COMPONETFUNCTIONSYMBOL_H


#include "ComponentPin.h"

#include <sys/stat.h>



using namespace std;


class ComponentFunctionSymbol
{
	public:
		ComponentFunctionSymbol();
	    ComponentFunctionSymbol(int heigh, int width);
		ComponentFunctionSymbol(const ComponentFunctionSymbol &In);
		~ComponentFunctionSymbol();
		ComponentFunctionSymbol& operator = (const ComponentFunctionSymbol &In);

		void addNewPin(int position, int type, int orientation, string name);

		std::vector<ComponentPin> v_pins;
		int getWidth();
		int getHeigh();

	private:
		int heigh;
		int width;



};



#endif