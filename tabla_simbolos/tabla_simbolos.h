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

#endif
