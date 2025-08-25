%{
	#include <stdio.h>
	int yylex(void);
	void yyerror(const char *s);
%}

%token TIPO MAIN RETURN ID DIGITO ADD SUBSTR DIV MULT EQ PA PC CA CC SCOLON

%%

programa: TIPO MAIN PA PC CA listaInstrucciones CC


// listaInstrucciones permite primero declaraciones y luego sentencias

listaInstrucciones: declaraciones sentencias
        ;

declaraciones: /* vacio */
             | declaraciones d SCOLON
             ;

d: TIPO ID                   
 ;


// s puede ser asignacion o return

sentencias: /* vacio */
          | sentencias s SCOLON
          ;

s: ID EQ expresion
 | RETURN
 | RETURN expresion
 ;

expresion: ID
         | DIGITO
         | expresion ADD expresion
         | expresion MULT expresion
         ;  

%%

int main() {
    return yyparse();
}

void yyerror(const char *s) {
    fprintf(stderr, "Error: %s\n", s);
}
         