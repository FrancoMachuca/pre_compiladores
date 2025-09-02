%{
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "parser.tab.h"
int yycolumn = 1;
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

%%
"main"                              { yycolumn += yyleng; return MAIN; }
"return"                            { yycolumn += yyleng; return RETURN; }
"int"                               { yycolumn += yyleng; yylval.tipo = ENTERO; return TIPO; }
"bool"                              { yycolumn += yyleng; yylval.tipo = BOOL; return TIPO; }
"void" 								{ yycolumn += yyleng; yylval.tipo = VACIO; return TIPO;}
{DIGITO}+                           { yycolumn += yyleng; yylval.num = atoi(yytext); return DIGITO; }
{VERDAD}                            { yycolumn += yyleng; yylval.b = strcmp(yytext, "true") == 0 ? true : false; return VERDAD; }
{LETRA}({LETRA}|{DIGITO})*          { yycolumn += yyleng; yylval.id = strdup(yytext); return ID; }
{ADD}                               { yycolumn += yyleng; return ADD; }
{MULT}                              { yycolumn += yyleng; return MULT; }
{EQ}                                { yycolumn += yyleng; return EQ; }
{AND}                               { yycolumn += yyleng; return AND; }
{OR}                                { yycolumn += yyleng; return OR; }
{COMP}                              { yycolumn += yyleng; return COMP; }
{NOT}                               { yycolumn += yyleng; return NOT; }
"("                                 { yycolumn += yyleng; return PA; }
")"                                 { yycolumn += yyleng; return PC; }
"{"                                 { yycolumn += yyleng; return CA; }
"}"                                 { yycolumn += yyleng; return CC; }
";"                                 { yycolumn += yyleng; return SCOLON; }
[ ]+        						{ yycolumn += yyleng; }
\t+         						{ yycolumn += 4 * yyleng; }
\n          						{ yycolumn = 1; }
\r          						
.                                   { printf("Caracter no reconocido. \n"); exit(1); }                               
%%

void yyerror(){
	printf("Linea %d Col %d\n└──Error de sintaxis. \n", yylineno, yycolumn);
}     

