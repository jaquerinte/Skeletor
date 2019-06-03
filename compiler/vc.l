D    [0-9]
L    [a-zA-Z]
LD   [0-9a-zA-Z]
name ({L}|\$)({L}|{D}|[_.$])*
stringtext  \"[^\n"]+\"

%{
#include <string.h> 
#include <string>
#include <iostream>

using namespace std;

#include "common.h"
#include "vc.tab.h"

int ncol = 1,
    nlin = 1;

int endfile = 0;

int ret(int token);  
// function to update 'nlin' y 'ncol' yand return token

void msgError(int nerror, int nlin,int ncol,const char *s);
// function to print error


%}

%x COMMENT

%%

" "                     	{ncol++;}
[\t]                    	{ncol++;}
[\n]                    	{nlin++;ncol=1;}
"//"(.)*                	{; /* one line comment*/} 
"/*"                    	{ncol += strlen(yytext);BEGIN(COMMENT);}
<COMMENT>[^/*\n]+    		{ncol += strlen(yytext);}
<COMMENT>\n          		{nlin++;ncol=1;}
<COMMENT><<EOF>>     		{msgError(ERREOF,-1,-1,"");}
<COMMENT>"*/"        		{ncol+=strlen(yytext); BEGIN(INITIAL);}
<COMMENT>[*/]        		{ncol += strlen(yytext);}
"module"					{return ret(moduledefinition);}
"in"						{return ret(intype);}
"int"						{return ret(inttype);}
"out"						{return ret(outtype);}
"inout"						{return ret(inouttype);}
"`define"					{return ret(definevalueverilog);}
"#define"					{return ret(definevalue);}
"#function"					{return ret(functionmodule);}
"#description"				{return ret(descriptionmodule);}
"#coder"					{return ret(codermodule);}
"#references"				{return ret(referencesmodule);}
"true"						{return ret(booltokentrue);}
"false"						{return ret(booltokenfalse);}
"wire"						{return ret(wiretipe);}
"->"						{return ret(connectwire);}
"top"						{return ret (mainmodule);}

{name}						{return ret(id);}
{stringtext}				{return ret(stringtext);}
{D}+               			{return ret(ninteger);}
"+"                			{return ret(opas);}
"-"                			{return ret(opas);}
"++"               			{return ret(opasinc);}
"--"               			{return ret(opasinc);}
"("                			{return ret(parl);}
")"                			{return ret(parr);}
";"                			{return ret(pyc);}
":"							{return ret(twopoints);}
"~"							{return ret(nyooperator);}
","                			{return ret(coma);}
"=="               			{return ret(oprel);}
"!="               			{return ret(oprel);}
"<"                			{return ret(oprel);}
">"                			{return ret(oprel);}
"<="               			{return ret(oprel);}
">="               			{return ret(oprel);}
"*"                			{return ret(opmd);}
"/"                			{return ret(opmd);}
"="                			{return ret(opasig);}
"["                			{return ret(bral);}
"]"                			{return ret(brar);}
"{"                			{return ret(cbl);}
"}"                			{return ret(cbr);}
"&"                			{return ret(amp);}
"&&"               			{return ret(ybool);}
"||"               			{return ret(obool);}
"!"                			{return ret(nobool);}
%%

int yywrap(void) {endfile=1; return 1;} /* for not to link with the lex lib*/


int ret(int token)
{
   yylval.lexeme=strdup(yytext);
   yylval.nlin=nlin;
   yylval.ncol=ncol;
   ncol+=(strlen(yytext));
   return(token);
}
