#ifndef COMMON_H
#define COMMON_H
typedef struct {
   char *lexeme;
   int nlin,ncol;
   string trad;
   string ph;
   int size;
   int type;    //Translation from integer to type in vc.y. 
                    //INTEGER=1 
                    //REGISTER=2
                    //STRING=3
                    //LOGIC=5
   int counter; // counts the number of parameters of a instance
} BASETYPE;

#define YYSTYPE BASETYPE

#define ERRLEXIC        1
#define ERRSINT         2
#define ERREOF          3

/* GENERAL ERRORS */
#define ERRNODEC        4 // ERROR Var not declared 
#define ERRALDEC        5 // ERROR Var already declared
#define ERRFUNODEC      6 // ERROR Module not declared
#define ERRFUNALDEC     7 // ERROR Module already declared
#define ERRNEEDBOOL     8 // ERROR Bool required but something else founded
#define ERRNEEDDEF      9 // ERROR DEFINITION or DEFINITIONVERILOG needed but something else founded 
#define ERRORSIMALDEC   10 // ERROR Simbol already defined
#define ERRORSIMBNODEC  11 // ERROR Simbol not defined

/* MODULE ERRORS */
#define ERRCONNDEC     20 // ERROR Connection already declared
#define ERRCONNNODEC   21 // ERROR Connection not declared
#define ERRPARAMDEC    22 // ERROR Param module already declared
#define ERRPARAMNODEC  23 // ERROR param no declared

/* MODULE DEFINTION ERRORS */
#define ERRFUNCDEFALDEC  50  // ERROR Function module definition already define
#define ERRDESCDEFALDEC  51  // ERROR Description module definition already define
#define ERRORCODDEFALDEC 52  // ERROR Coder module definition already define
#define ERRORDEFIALDEC   53  // ERROR References module definition already define

/* MODULE SIGNAL ERRORS */
#define ERRTYPEARGS      80 // ERROR ilegal type for port size
#define ERRTYPEBOOL      81 // ERROR ilegal type for bool operation
#define ERRTYPEINTEGER      82 // ERROR ilegal type for integer operation
#define ERRTYPEMISMATCH  83 // ERROR Logic comparation of different types
/* INSTANCE ERROR */
#define ERRINSNOTFOUND   100 // ERROR Instance not found
/* ARGUMENTS ERROR */
#define ERRARGUMENTPOSNONAME 120 // ERROR positional ARGUMENT un a name argument

/* SYSTEM CONSTANTS */
#define IN 1
#define OUT 2
#define INOUT 3

#define COMPONENT 1
#define SHEET 2

/* KICAT CONSTANTS */
#define DEFAULTMODULEWIDTH 1500 // 800 2500
#define DEFAULTMODULEHEIGHT 500
#define CRERANCEINTOP 100
#define DISTANCEBETWEENPINS 100

#define PINLENGH 100

#define XPOSITIONBASE 1500  
#define YPOSITIONBASE 3000 // 3000 5000
#define CLEARANCEBETWEENMODULES 3000 // 1500 3500
#define TOPCLEARANCETEXT1 -115
#define TOPCLEARANCETEXT2 -175

#define XLABELBASEINPUT 1200
#define XLABELBASEOUTPUT 10250
#define YLABELBASE 800
#define CLEARANCEBETWEENLABELS 200


// wiring constants 
#define NUMBEROFBASEINPUTCHANELS 5
#define NUMBEROFOUTPUTCHANELS 5
#define NUMBEROFBOTTOMCHANELS 15
#define SPACEBEWEENWIRES 50
#define MINIMUNCLEARANCE 10
#define OFFSETCLEARANCE 12

#define FIRSTBOTTOMCHANELYCORDINATE 3200

#define ENABLENOCONNECTION false

void msgError(int nerror,int nlin,int ncol,const char *s);
#endif