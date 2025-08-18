%{
#include <stdio.h>
#include <stdbool.h>
%}

LETRA [a-zA-Z]
DIGITO [0-9]
TIPO int|bool|void
ADD "+"
SUBSTR "-"
MULT "*"
DIV "/"
EQ "="
PA "("
PC  ")"
CA "{"
CC "}"
WS [ \t\n]+

%%
{TIPO} { return TIPO; }
"return" { return RETURN; }
"main" { return MAIN; }
{LETRA}({LETRA}|{DIGITO})* {return ID;}
{ADD} { return ADD; }
{SUBSTR} { return SUBSTR; }
{DIV} { return DIV; }
{MULT} { return MULT; }
{EQ} { return EQ; }
{PA} { return PA; }
{PC} { return PC; }
{CA} { return CA; }
{CC} { return CC; }
";"    { return SCOLON}
{WS}
.
%%

int main(void) {
    yylex();
}

