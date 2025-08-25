#ifndef AST
#define AST
#include "utils/enums.h"

typedef struct Info_ID
{
    char *id;
    void *valor;
    Tipo tipo;
} Info_ID;

typedef struct Info_Operador
{
    char op;
    Tipo tipo;
} Info_Operador;

typedef struct Info_Literal
{
    void *valor;
    Tipo tipo;
} Info_Literal;

typedef struct Arbol
{
    union
    {
        Info_ID info_id;
        Info_Operador info_operador;
        Info_Literal info_literal;
    };
    Tipo_Info tipo_info;
    struct Arbol *izq;
    struct Arbol *der;
} Arbol;

Arbol *crear_arbol_operador(char op, Tipo tipo, Tipo_Info tipo_info);
Arbol *crear_arbol_id(char *id, Tipo tipo, Tipo_Info tipo_info);
Arbol *crear_arbol_literal(void *valor, Tipo tipo, Tipo_Info tipo_info);
void asignar_valor_id(Arbol *arbol, void *valor);
void asignar_hijos(Arbol *padre, Arbol *izq, Arbol *der);
void inorder(Arbol *arbol);

#endif