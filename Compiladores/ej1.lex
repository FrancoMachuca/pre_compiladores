%{
#include <stdio.h>
#include <stdbool.h>
%}

ID [a-z][a-z0-9]*
TIPO int|bool
TIPO_FUNCION TIPO|void
DIGITO [0-9]+
BOOL true|false
OPERADOR "+"|"++"|"-"|"*"|"/"|"="|"=="|"||"|"&&"|"!"|"+="|"-="|"/="|"*="
DELIMITADOR "("|")"|"{"|"}"
RESERVADA "if"|"while"|"do"|"else"|"for"|"break"|"continue"|TIPO_FUNCION
WS [ \t\n]+

%%
{TIPO} {printf("%s tipo \n", yytext);}
{RESERVADA} {printf("%s palabra reservada \n", yytext);}
{DIGITO} {printf("%s numero \n", yytext);}
{BOOL} {printf("%s booleano \n", yytext);}
{ID}   {printf("%s nombre \n", yytext);}
{OPERADOR} {printf("%s operador \n", yytext);}
{DELIMITADOR} {printf("%s delimitador \n", yytext);}
";"    {printf("%s finalizacion de linea \n", yytext);}
{WS}
.
%%

int main(void) {
    yylex();
}

