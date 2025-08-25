#ifndef AST
#define AST
#include "../utils/enums.h"

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

typedef struct Info_Sentencia
{
    char *sentencia;
} Info_Sentencia;

typedef struct Info_Declaracion
{
    char *declaracion;
    Tipo tipo;
} Info_Declaracion;

typedef struct Info_Instruccion
{
    char *instruccion;
} Info_Instruccion;

typedef struct Arbol
{
    union
    {
        Info_ID info_id;
        Info_Operador info_operador;
        Info_Literal info_literal;
        Info_Sentencia info_sentencia;
        Info_Declaracion info_declaracion;
        Info_Instruccion info_instruccion;
    };
    Tipo_Info tipo_info;
    struct Arbol *izq;
    struct Arbol *der;
} Arbol;

Arbol *crear_arbol_operador(char op, void *valor, Arbol *izq, Arbol *der);
Arbol *crear_arbol_id(char *id, Arbol *izq, Arbol *der);
Arbol *crear_arbol_literal(void *valor, Tipo tipo, Arbol *izq, Arbol *der);
Arbol *crear_arbol_sentencia(char *sentencia, Arbol *izq, Arbol *der);
Arbol *crear_arbol_declaracion(char *declaracion, Tipo tipo, Arbol *izq, Arbol *der);
Arbol *crear_arbol_instruccion(char *instruccion, Arbol *izq, Arbol *der);
void inorder(Arbol *arbol);
void imprimir_vertical(Arbol *arbol, char *prefijo, int es_ultimo);

#endif