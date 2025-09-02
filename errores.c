#include "errores.h"
#include <stdio.h>
#include <string.h>

// Arreglo de errores
Error errores[MAX_ERRORES];
int cantErrores = 0;

void reportarError(CodigoError codigo, const char *info, int linea, int colum)
{
    if (cantErrores >= MAX_ERRORES)
        return;

    errores[cantErrores].codigo = codigo;

    switch (codigo)
    {
    case VAR_NO_DECLARADA:
        snprintf(errores[cantErrores].mensaje, MAX_MSG, "Linea %d Col %d\n└──Error: variable '%s' no declarada", linea, colum, info);
        break;
    case VAR_YA_DECLARADA:
        snprintf(errores[cantErrores].mensaje, MAX_MSG, "Linea %d Col %d\n└──Error: variable '%s' ya declarada", linea, colum, info);
        break;
    case FUN_NO_DECLARADA:
        snprintf(errores[cantErrores].mensaje, MAX_MSG, "Linea %d Col %d\n└──Error: función '%s' no declarada", linea, colum, info);
        break;
    case FUN_YA_DECLARADA:
        snprintf(errores[cantErrores].mensaje, MAX_MSG, "Linea %d Col %d\n└──Error: función '%s' ya declarada", linea, colum, info);
        break;
    case TIPO_INCOMPATIBLE:
        snprintf(errores[cantErrores].mensaje, MAX_MSG, "Linea %d Col %d\n└──Error: tipo incompatible '%s'", linea, colum, info);
        break;
    }

    cantErrores++;
}

void mostrarErrores(void)
{
    for (int i = 0; i < cantErrores; i++)
    {
        printf("%s\n", errores[i].mensaje);
    }
}