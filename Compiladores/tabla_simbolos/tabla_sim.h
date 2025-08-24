#ifndef TABLA_SIM_H
#define TABLA_SIM_H

#include "simbolo.h"

typedef struct Tabla
{
    Simbolo *simbolo;
    struct Tabla *sig;
} Tabla;

Tabla *crear_tabla(Simbolo *simbolo);
void insertar(Tabla *tabla, Simbolo *simbolo);
Simbolo *buscar(Tabla *tabla, Simbolo *simbolo);

#endif