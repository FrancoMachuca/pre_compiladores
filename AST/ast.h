#ifndef AST
#define AST
#include "../utils/enums.h"

typedef struct Info_ID
{
    char *nombre;
    void *valor;
    Tipo tipo;
} Info_ID;

typedef struct Info_Operador
{
    char *nombre;
    void *valor;
    Tipo tipo;
} Info_Operador;

typedef struct Info_Literal
{
    void *valor;
    Tipo tipo;
} Info_Literal;

typedef struct Info_Union
{
    Info_ID id;
    Info_Operador operador;
    Info_Literal literal;
} Info_Union;

typedef struct Arbol
{
    Info_Union *info;
    Tipo_Info tipo_info;
    struct Arbol *izq;
    struct Arbol *der;
} Arbol;

Arbol *crear_arbol_operador(char *op, void *valor, Arbol *izq, Arbol *der);
Arbol *crear_arbol_id(char *id, Arbol *izq, Arbol *der);
Arbol *crear_arbol_literal(void *valor, Tipo tipo, Arbol *izq, Arbol *der);
Arbol *crear_arbol_nodo(Tipo_Info tipo, Arbol *izq, Arbol *der);
void inorder(Arbol *arbol);
void imprimir_vertical(Arbol *arbol, char *prefijo, int es_ultimo);

#endif