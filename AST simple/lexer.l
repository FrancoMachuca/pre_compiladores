%{
#include "parser.tab.h"
%}

digito [0-9]

%%

{digito}+      { yylval.value = atoi(yytext); return NUM; }

[ \t]+         ;              /* Ignora espacios y tabs */

\n             { return '\n'; } /* Enviar fin de línea al parser */

.              { return yytext[0]; }  /* Otros caracteres como +, * */

%%

int yywrap(void) {
    return 1;
}
