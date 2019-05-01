D    [0-9]
L    [a-zA-Z]
LD   [0-9a-zA-Z]
name ({L}|\$)({L}|{D}|[_.\-/$])*

%{
#include <string.h> 
#include <string>
#include <iostream>

using namespace std;

#include "common.h"
#include "rtl_wiring.tab.h"

int ncol = 1,
    nlin = 1;

int findefichero = 0;

int ret(int token);  
// función que actualiza 'nlin' y 'ncol' y devuelve el token

void msgError(int nerror, int nlin,int ncol,const char *s);
// función para producir mensajes de error


%}

%x COMENTARIO

%%
%{
/* codigo local */
%}

" "                     {ncol++;}
[\t]                    {ncol++;}
[\n]                    {nlin++;ncol=1;}
"//"(.)*                {; /* comentarios de una linea, no hacer nada */} 
"/*"                    {ncol += strlen(yytext);BEGIN(COMENTARIO);}
<COMENTARIO>[^/*\n]+    {ncol += strlen(yytext);}
<COMENTARIO>\n          {nlin++;ncol=1;}
<COMENTARIO><<EOF>>     {msgError(ERREOF,-1,-1,"");}
<COMENTARIO>"*/"        {ncol+=strlen(yytext); BEGIN(INITIAL);}
<COMENTARIO>[*/]        {ncol += strlen(yytext);}
"block"					{return ret(blockdefinition);}
{name}					{return ret(id);}
{D}+               		{return ret(ninteger);}
{D}+(\.){D}+       		{return ret(nfloat);}
"+"                		{return ret(opas);}
"-"                		{return ret(opas);}
"++"               		{return ret(opasinc);}
"--"               		{return ret(opasinc);}
"("                		{return ret(parl);}
")"                		{return ret(parr);}
";"                		{return ret(pyc);}
","                		{return ret(coma);}
"=="               		{return ret(oprel);}
"!="               		{return ret(oprel);}
"<"                		{return ret(oprel);}
">"                		{return ret(oprel);}
"<="               		{return ret(oprel);}
">="               		{return ret(oprel);}
"*"                		{return ret(opmd);}
"/"                		{return ret(opmd);}
"="                		{return ret(opasig);}
"["                		{return ret(bral);}
"]"                		{return ret(brar);}
"{"                		{return ret(cbl);}
"}"                		{return ret(cbr);}
"&"                		{return ret(amp);}
"&&"               		{return ret(ybool);}
"||"               		{return ret(obool);}
"!"                		{return ret(nobool);}


%%

int yywrap(void) {findefichero=1; return 1;} /* para no tener que linkar con la
                                libreria del lex */


int ret(int token)
{
   yylval.lexema=strdup(yytext);
   yylval.nlin=nlin;
   yylval.ncol=ncol;
   ncol+=(strlen(yytext));
   return(token);
}