#ifndef INSTANCECOMPONETFUNCTIONSYMBOL_H
#define INSTANCECOMPONETFUNCTIONSYMBOL_H


#include "ComponentFunctionSymbol.h"

#include <sys/stat.h>
#include <map>

#include "../common.h"



using namespace std;


class FunctionSymbol;

class InstanceComponentFunctionSymbol
{
    public:
        InstanceComponentFunctionSymbol();
        InstanceComponentFunctionSymbol(int xbaseposition, int ybaseposition, int type, int positionInComponent);
        InstanceComponentFunctionSymbol(const InstanceComponentFunctionSymbol &In);
        ~InstanceComponentFunctionSymbol();
        InstanceComponentFunctionSymbol& operator = (const InstanceComponentFunctionSymbol &In);    
        string generateSchematicDesing(string projectName, string functionName, string instanceName, ComponentFunctionSymbol* componentDesig);
        string generateSchematicDesing(string projectName, string functionName, string instanceName, std::map<string, FunctionSymbol*> mapOfLeafsModules);
        void SetcomponentDesig(ComponentFunctionSymbol* componentDesig);
        ComponentFunctionSymbol* componentDesig;
        int getXBasePosition();
        int getyBasePosition();
        
    private:
        int xbaseposition;
        int ybaseposition;
        int positionInComponent;
        int type;
        


};



#endif