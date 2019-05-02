#ifndef INOUTSYMBOL_H
#define INOUTSYMBOL_H


#include <string.h>
#include <string>
#include <vector>
using namespace std;

const int IN=1;
const int OUT=2;
const int INOUT=3;

class InoutSymbol
{
public:
	InoutSymbol();
	InoutSymbol(const string name,const int typeconnection,const string width);
	InoutSymbol(const InoutSymbol &In);
	~InoutSymbol();
	InoutSymbol& operator = (const InoutSymbol &In);
	// getters
	string getName();
	int getType();
	string getWith();
	void setName(string name);
	void setType(int type);
	void setWith(int width);


private:
	/* Value definitions*/
	string name;
	int typeconnection;
	string width; // TODO CHECK
	
};


#endif