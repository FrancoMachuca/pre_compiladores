%{
#include <stdio.h>
#include <stdbool.h>
%}

ID [a-z][a-z0-9]*
TIPO int|bool
TIPO_FUNCION TIPO|void
DIGITO [0-9]+
BOOL true|false
WS [ \t\n]+

%%

6{3} {printf("revivan el jiros \n");}
{DIGITO} {printf("%s numero \n", yytext);}
{TIPO} {printf("%s palabra reservada \n", yytext);}
{BOOL} {printf("%s booleano \n", yytext);}
{ID}   {printf("%s nombre \n", yytext);}
"="    {printf("%s asignacion \n", yytext);}
";"    {printf("%s finalizacion de linea \n", yytext);}
{WS}
.
%%

int main(void) {
    yylex();
}

