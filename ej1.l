%{
#include <stdio.h>
#include <stdbool.h>
#include "parser.tab.h"
%}

LETRA   [a-zA-Z]
DIGITO  [0-9]
TIPO    int|bool|void
ADD     \+
SUBSTR  -
MULT    \*
DIV     \/
EQ      =
PA      \(
PC      \)
CA      \{
CC      \}
SCOLON  ;
MAIN "main"
WS      [ \t\n]+

%%
{TIPO} { return TIPO; }
"return" { return RETURN; }
{MAIN} { return MAIN; }
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
{DIGITO} { return DIGITO; }
{SCOLON}   { return SCOLON; }
{WS}
. { printf("Caracter no reconocido. \n");
    exit(1); }
%%

