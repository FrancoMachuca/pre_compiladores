#ifndef TS
#define TS

#include "../AST/ast.h"

typedef struct Simbolo
{
    Info_Union *info;
    struct Simbolo *next;
    Tipo_Info flag;
} Simbolo;

Simbolo *crearTabla();

void agregarSimbolo(Simbolo *tabla, Info_Union *info, Tipo_Info flag);

Simbolo *buscarSimbolo(Simbolo *tabla, char *nombre, Tipo_Info flag);

void printTabla(Simbolo *tabla);

void recolectarDeclaraciones(Arbol *arbol, Simbolo *tabla);

void chequearTipos(Arbol *arbol, Simbolo *tabla);

void analisisSemantico(Arbol *arbol, Simbolo *tabla);

int procesarId(Arbol *hijo, Tipo_Info tipoPadre, Simbolo *tabla);

void procesarAsignacion(Arbol *arbol, Simbolo *tabla);

void procesarDeclaracion(Arbol *arbol, Simbolo *tabla);

void procesarOperador(Arbol *arbol, Simbolo *tabla);

void procesarFuncion(Arbol *arbol, Simbolo *tabla);

void procesarReturn(Arbol *arbol, Simbolo *tabla);

Tipo obtenerTipoNodo(Arbol *nodo);

#endif
