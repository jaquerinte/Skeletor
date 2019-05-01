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
InoutSymbol.o: $(OBJECTSFOLDER)InoutSymbol.cpp
	$(CC) -c $(OBJECTSFOLDER)InoutSymbol.cpp -o $(OBJECTSFOLDER)InoutSymbol.o $(CFLAGS)

FunctionSymbolParam.o: $(OBJECTSFOLDER)FunctionSymbolParam.cpp
	$(CC) -c $(OBJECTSFOLDER)FunctionSymbolParam.cpp -o $(OBJECTSFOLDER)FunctionSymbolParam.o $(CFLAGS)

FunctionSymbol.o: $(OBJECTSFOLDER)FunctionSymbol.cpp
	$(CC) -c $(OBJECTSFOLDER)FunctionSymbol.cpp -o $(OBJECTSFOLDER)FunctionSymbol.o $(CFLAGS)

TableFunctionSymbols.o: $(OBJECTSFOLDER)TableFunctionSymbols.cpp
	$(CC) -c $(OBJECTSFOLDER)TableFunctionSymbols.cpp -o $(OBJECTSFOLDER)TableFunctionSymbols.o $(CFLAGS)

main: InoutSymbol.o FunctionSymbolParam.o FunctionSymbol.o TableFunctionSymbols.o
	mkdir -p $(OUTPUTFOLDER)
	rm -f *.tab.*
	rm -f lex.yy.c
	flex  $(LFILE) 
	bison -d $(YFILE) $(YFLAGS)
	# compile objects
	g++ -o $(OUTPUTFOLDER)$(TARGET) vc.tab.c lex.yy.c $(OBJECTSFOLDER)InoutSymbol.o $(OBJECTSFOLDER)FunctionSymbolParam.o $(OBJECTSFOLDER)FunctionSymbol.o $(OBJECTSFOLDER)TableFunctionSymbols.o

# Clean
.PHONY: clean
clean:
	rm -f *.tab.*
	rm -f lex.yy.c
	rm -rf *.o
	rm -rf $(OBJECTSFOLDER)*.o
	rm -rf $(OUTPUTFOLDER)$(TARGET)
