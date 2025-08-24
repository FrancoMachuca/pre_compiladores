#include <stdio.h>
#include <stdlib.h>
#include "simbolo.h"
#include <string.h>

Simbolo *crear_simbolo(char *nombre, Tipo tipo, void *valor, Flag flag)
{
    Simbolo *resultado = malloc(sizeof(Simbolo));
    resultado->nombre = strdup(nombre);
    resultado->tipo = tipo;
    resultado->valor = valor;
    resultado->flag = flag;

    return resultado;
}