%{
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "parser.tab.h"
%}

LETRA           [a-zA-Z]
DIGITO          [0-9]
ADD             \+
MULT            \*
EQ              =
WS              [ \t\n]+

%%
"main"                              { return MAIN; }
"return"                            { return RETURN; }
"int"                               { yylval.tipo = ENTERO; return TIPO; }
"bool"                              { yylval.tipo = BOOL; return TIPO; }
{DIGITO}+                            { yylval.num = atoi(yytext); return DIGITO; }
{LETRA}({LETRA}|{DIGITO})*          { yylval.id = strdup(yytext); return ID; }
{ADD}                               { return ADD; }
{MULT}                              { return MULT; }
{EQ}                                { return EQ; }
"("                                 { return PA; }
")"                                 { return PC; }
"{"                                 { return CA; }
"}"                                 { return CC; }
";"                                 { return SCOLON; }
{WS}
.                                   { printf("Caracter no reconocido. \n"); exit(1); }                                    
%%

