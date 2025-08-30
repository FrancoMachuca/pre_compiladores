%{
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "parser.tab.h"
%}

%option yylineno

LETRA           [a-zA-Z]
DIGITO          [0-9]
VERDAD          "true"|"false"
ADD             \+
MULT            \*
EQ              =
AND             "&&"
OR              "\|\|"
COMP            "=="
NOT             "!"
WS              [ \t\n]+

%%
"main"                              { return MAIN; }
"return"                            { return RETURN; }
"int"                               { yylval.tipo = ENTERO; return TIPO; }
"bool"                              { yylval.tipo = BOOL; return TIPO; }
{DIGITO}+                           { yylval.num = atoi(yytext); return DIGITO; }
{VERDAD}                            { yylval.b = strcmp(yytext, "true") == 0 ? true : false; return VERDAD; }
{LETRA}({LETRA}|{DIGITO})*          { yylval.id = strdup(yytext); return ID; }
{ADD}                               { return ADD; }
{MULT}                              { return MULT; }
{EQ}                                { return EQ; }
{AND}                               { return AND; }
{OR}                                { return OR; }
{COMP}                              { return COMP; }
{NOT}                               { return NOT; }
"("                                 { return PA; }
")"                                 { return PC; }
"{"                                 { return CA; }
"}"                                 { return CC; }
";"                                 { return SCOLON; }
{WS}
.                                   { printf("Caracter no reconocido. \n"); exit(1); }                               
%%
/*
void yyerror(){
	printf("%s%d\n","-> Error de sintaxis en linea: ", yylineno);
}     
*/
