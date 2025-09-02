%{
	#include <stdio.h>
    #include <string.h>
    #include "AST/ast.h"
	int yylex(void);
	void yyerror(Arbol** destino, const char *s);
    extern FILE *yyin;
%}

%code requires {
    #include <stdbool.h>
    #include "AST/ast.h"
    #include "tabla_simbolos/tabla_simbolos.h"
}

%parse-param { Arbol **destino }

%union{
    int num;
    bool b;
    char* id;
    Tipo tipo;
    Arbol* ast;
}

%token MAIN RETURN EQ PA PC CA CC SCOLON
%token <num> DIGITO ADD MULT 
%token <b> AND OR COMP NOT VERDAD
%token <id> ID
%token <tipo> TIPO

%type <ast> expresion s sentencias d declaraciones programa

%left ADD
%left MULT
%left NOT
%left AND
%left OR
%left COMP

%%

programa: TIPO MAIN PA PC CA declaraciones sentencias CC { *destino = crear_arbol_funcion("main", $1, $6, $7); 
                                                            imprimir_vertical(*destino, "", 1);}


declaraciones: /* vacio */              { $$ = NULL; }
             | declaraciones d SCOLON   {
                                            if($1 == NULL) {
                                                $$ = $2;
                                            } else {
                                                $$ = crear_arbol_nodo(DECLARACIONES, $1, $2);
                                            }  
                                        }
             ;

d: TIPO ID  { 
                Arbol* id_arbol = crear_arbol_id($2, NULL, NULL);
                printf("%d\n", $1);
                id_arbol->info->id.tipo = $1;
                $$ = crear_arbol_nodo(DECLARACION, id_arbol, NULL);
                
            }                 
 ;


// s puede ser asignacion o return

sentencias: /* vacio */ { $$ = NULL; }
          | sentencias s SCOLON {
                                    if($1 == NULL) {
                                        $$ = $2;
                                    } else {
                                        $$ = crear_arbol_nodo(SENTENCIAS, $1, $2);
                                    }
                                }
          ;

s: ID EQ expresion  {
                        Arbol* id_arbol = crear_arbol_id($1, NULL, NULL);
                        $$ = crear_arbol_nodo(ASIGNACION, id_arbol, $3);
                    }
 | RETURN           {$$ = crear_arbol_nodo(RETURN_INFO, NULL, NULL);}
 | RETURN expresion {$$ = crear_arbol_nodo(RETURN_INFO, $2, NULL);}
 ;

expresion: ID                      {$$ = crear_arbol_id($1, NULL, NULL);}
        | DIGITO                   {int* valor = malloc(sizeof(int)); 
                                    *valor = $1; 
                                    $$ = crear_arbol_literal(valor, ENTERO, NULL, NULL);}
        | VERDAD                   {bool* valor = malloc(sizeof(bool));
                                    *valor = $1;
                                    $$ = crear_arbol_literal(valor, BOOL, NULL, NULL);}
        | expresion ADD expresion  {$$ = crear_arbol_operador("+", NULL, $1, $3);}
        | expresion MULT expresion {$$ = crear_arbol_operador("*", NULL, $1, $3);}
        | expresion AND expresion  {$$ = crear_arbol_operador("&&", NULL, $1, $3);}
        | expresion OR expresion   {$$ = crear_arbol_operador("||", NULL, $1, $3);}
        | expresion COMP expresion {$$ = crear_arbol_operador("==", NULL, $1, $3);}
        | NOT expresion            {$$ = crear_arbol_operador("!", NULL, $2, NULL);}
        ;  

%%
/*
int main(int argc, char **argv) {
    if (argc > 1) {
        FILE *archivo = fopen(argv[1], "r");
        if (!archivo) {
            perror("No se pudo abrir el archivo");
            return 1;
        }
        yyin = archivo;
    }

    Arbol* arbol = NULL;

    return yyparse(&arbol);
}
*/


void yyerror(Arbol** destino, const char *s) {
    fprintf(stderr, "Error: %s\n", s);
}
         