#ifndef SIMBOLO_H
#define SIMBOLO_H
#include "utils/enums.h"

typedef struct Simbolo
{
    char *nombre;
    Tipo tipo;
    void *valor;
    Flag flag;
} Simbolo;

Simbolo *crear_simbolo(char *nombre, Tipo tipo, void *valor, Flag flag);

#endif