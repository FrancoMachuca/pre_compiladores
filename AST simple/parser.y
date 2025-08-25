%{
    #include <stdio.h>
    int yylex(void);
    void yyerror(const char *s);
%}

%code requires {
    #include "ast.h"
}

%union {
    int value;
    Nodo* nodo;
}

%token <value> NUM
%type <nodo> expresion programa

%left '+'
%left '*'

%%

programa
    : expresion '\n' { printf("Resultado = %d\n", eval($1)); YYACCEPT; }
    ;

expresion
    : NUM                     { $$ = newNodoNum($1); }
    | expresion '+' expresion { $$ = newNodoOp('+', $1, $3); }
    | expresion '*' expresion { $$ = newNodoOp('*', $1, $3); }
    ;

%%

int main() {
    return yyparse();
}

void yyerror(const char *s) {
    fprintf(stderr, "Error: %s\n", s);
}
