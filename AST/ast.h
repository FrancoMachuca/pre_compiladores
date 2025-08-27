#ifndef AST
#define AST
#include "../utils/enums.h"
#include "../tabla_simbolos/tabla.h"

typedef struct Info_ID
{
    char *id;
    void *valor;
    Tipo tipo;
} Info_ID;

typedef struct Info_Operador
{
    char op;
    void *valor;
    Tipo tipo;
} Info_Operador;

typedef struct Info_Literal
{
    void *valor;
    Tipo tipo;
} Info_Literal;

typedef struct Info_Nodo
{
    char *nodo;
} Info_Nodo;

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

Arbol *crear_arbol_operador(char op, void *valor, Arbol *izq, Arbol *der);
Arbol *crear_arbol_id(char *id, Arbol *izq, Arbol *der);
Arbol *crear_arbol_literal(void *valor, Tipo tipo, Arbol *izq, Arbol *der);
Arbol *crear_arbol_nodo(Tipo_Info tipo, Arbol *izq, Arbol *der);
void inorder(Arbol *arbol);
void imprimir_vertical(Arbol *arbol, char *prefijo, int es_ultimo);
void crearTablas(Arbol* arbol, Simbolo* tabla);

#endif