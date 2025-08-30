#ifndef TS
#define TS

#include "../AST/ast.h"

typedef struct Simbolo
{
    Info_Union *info;
    struct Simbolo *next;
} Simbolo;

Simbolo *crearTabla();

void agregarSimbolo(Simbolo *tabla, Info_Union *info);

Simbolo *buscarSimbolo(Simbolo *tabla, char *nombre);

void printTabla(Simbolo *tabla);

void analisisSemantico(Arbol *arbol, Simbolo *tabla);

void procesarAsignacion(Arbol *arbol, Simbolo *tabla);

void procesarDeclaracion(Arbol *arbol, Simbolo *tabla);

void procesarOperador(Arbol *arbol);

Tipo obtenerTipoNodo(Arbol *nodo);

#endif
