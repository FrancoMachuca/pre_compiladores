#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tabla_sim.h"

Tabla *crear_tabla(Simbolo *simbolo)
{
    Tabla *resultado = malloc(sizeof(Tabla));
    resultado->simbolo = simbolo;
    resultado->sig = NULL;

    return resultado;
}

void insertar(Tabla *tabla, Simbolo *simbolo)
{
    Tabla *actual = tabla;

    while (actual->sig != NULL)
    {
        actual = actual->sig;
    }

    Tabla *nuevo = malloc(sizeof(Tabla));
    nuevo->simbolo = simbolo;
    nuevo->sig = NULL;

    actual->sig = nuevo;
}

Simbolo *buscar(Tabla *tabla, Simbolo *simbolo)
{
    Tabla *actual = tabla;

    while (actual != NULL)
    {
        if (strcmp(actual->simbolo->nombre, simbolo->nombre) == 0)
        {
            return actual->simbolo;
        }
        actual = actual->sig;
    }

    return NULL;
}
