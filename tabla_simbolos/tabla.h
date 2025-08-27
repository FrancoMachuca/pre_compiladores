#ifndef TS
#define TS

#include "../AST/ast.h"

typedef struct Simbolo
{
    Info_Union *simbolo;
    struct Simbolo *next;
} Simbolo;

Simbolo *crearTabla();

void agregarSimbolo(Simbolo *tabla, Info_Union *info);

Simbolo *buscarSimbolo(Simbolo *tabla, char *nombre);

void printTabla(Simbolo *tabla);

void crearTablas(Arbol *arbol, Simbolo *tabla);

#endif
