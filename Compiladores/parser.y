%{
	#include <stdio.h>
	int yylex(void);
	void yyerror(const char *s);
%}

%token TIPO MAIN RETURN ID NUM

%%

programa: TIPO MAIN '('')' '{' listaInstrucciones '}'


// listaInstrucciones permite primero declaraciones y luego sentencias

listaInstrucciones: declaraciones sentencias
        ;

declaraciones: /* vacio */
             | declaraciones d ';'
             ;

d: TIPO ID                     
 ;


// s puede ser asignacion o return

sentencias: /* vacio */
          | sentencias s ';'
          ;

s: ID '=' expresion
 | RETURN
 | RETURN expresion
 ;

expresion: ID
         | NUM
         | expresion '+' expresion
         | expresion '*' expresion
         ;  

%%

int main() {
    return yyparse();
}

void yyerror(const char *s) {
    fprintf(stderr, "Error: %s\n", s);
}
         