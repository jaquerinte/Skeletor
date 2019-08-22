# CONFIGURATION DIRECTIVES
# Compilers 
CC = g++
# the build target executable:
TARGET = verilog_connector
# YACC FILE
YFILE = vc.y
# LEX FILE
LFILE = vc.l
# FLAGS 
# CC compiler flags:
CFLAGS  = -std=c++11
# YACC compiler flags:
YFLAGS = -Wconflicts-sr
# OBJECTS FOLDER
OBJECTSFOLDER = ./objects/
# OUTPUT FOLDER
OUTPUTFOLDER = ./bin/

# COMPILER MAIN
all:main
	
# End Main
# Object compilation
WireSymbol.o: $(OBJECTSFOLDER)WireSymbol.cpp
	$(CC) -c $(OBJECTSFOLDER)WireSymbol.cpp -o $(OBJECTSFOLDER)WireSymbol.o $(CFLAGS)

VWireSymbol.o: $(OBJECTSFOLDER)VWireSymbol.cpp
	$(CC) -c $(OBJECTSFOLDER)VWireSymbol.cpp -o $(OBJECTSFOLDER)VWireSymbol.o $(CFLAGS)

Symbol.o: $(OBJECTSFOLDER)Symbol.cpp
	$(CC) -c $(OBJECTSFOLDER)Symbol.cpp -o $(OBJECTSFOLDER)Symbol.o $(CFLAGS)

TableSymbols.o: $(OBJECTSFOLDER)TableSymbols.cpp
	$(CC) -c $(OBJECTSFOLDER)TableSymbols.cpp -o $(OBJECTSFOLDER)TableSymbols.o $(CFLAGS)

InoutSymbol.o: $(OBJECTSFOLDER)InoutSymbol.cpp
	$(CC) -c $(OBJECTSFOLDER)InoutSymbol.cpp -o $(OBJECTSFOLDER)InoutSymbol.o $(CFLAGS)

FunctionSymbolParam.o: $(OBJECTSFOLDER)FunctionSymbolParam.cpp
	$(CC) -c $(OBJECTSFOLDER)FunctionSymbolParam.cpp -o $(OBJECTSFOLDER)FunctionSymbolParam.o $(CFLAGS)

InstanceSymbol.o: $(OBJECTSFOLDER)InstanceSymbol.cpp
	$(CC) -c $(OBJECTSFOLDER)InstanceSymbol.cpp -o $(OBJECTSFOLDER)InstanceSymbol.o $(CFLAGS)

FunctionSymbol.o: $(OBJECTSFOLDER)FunctionSymbol.cpp
	$(CC) -c $(OBJECTSFOLDER)FunctionSymbol.cpp -o $(OBJECTSFOLDER)FunctionSymbol.o $(CFLAGS)

TableFunctionSymbols.o: $(OBJECTSFOLDER)TableFunctionSymbols.cpp
	$(CC) -c $(OBJECTSFOLDER)TableFunctionSymbols.cpp -o $(OBJECTSFOLDER)TableFunctionSymbols.o $(CFLAGS)

main: InoutSymbol.o FunctionSymbolParam.o FunctionSymbol.o TableFunctionSymbols.o Symbol.o TableSymbols.o WireSymbol.o VWireSymbol.o InstanceSymbol.o
	mkdir -p $(OUTPUTFOLDER)
	rm -f *.tab.*
	rm -f lex.yy.c
	flex  $(LFILE) 
	bison -d $(YFILE) $(YFLAGS)
	# compile objects
	$(CC) -o $(OUTPUTFOLDER)$(TARGET) vc.tab.c lex.yy.c $(OBJECTSFOLDER)InoutSymbol.o $(OBJECTSFOLDER)FunctionSymbolParam.o $(OBJECTSFOLDER)FunctionSymbol.o $(OBJECTSFOLDER)TableFunctionSymbols.o $(OBJECTSFOLDER)Symbol.o $(OBJECTSFOLDER)TableSymbols.o $(OBJECTSFOLDER)WireSymbol.o $(OBJECTSFOLDER)VWireSymbol.o $(OBJECTSFOLDER)InstanceSymbol.o

# Clean
.PHONY: clean
clean:
	rm -rf OUTPUT/
	rm -f *.tab.*
	rm -f lex.yy.c
	rm -rf *.o
	rm -rf $(OBJECTSFOLDER)*.o
	rm -rf $(OUTPUTFOLDER)$(TARGET)
