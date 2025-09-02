#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "helpers.h"

void print_valor(Tipo tipo, void *valor, const char *prefix)
{
    if (!valor)
    {
        printf("%s(null)\n", prefix ? prefix : "");
        return;
    }

    switch (tipo)
    {
    case ENTERO:
        printf("%s%d\n", prefix ? prefix : "", *(int *)valor);
        break;

    case BOOL:
        printf("%s%s\n", prefix ? prefix : "",
               (*(bool *)valor) ? "true" : "false");
        break;

    default:
        printf("%s<?> (tipo desconocido)\n", prefix ? prefix : "");
        break;
    }
}

Tipo obtenerTipoNodo(Arbol *nodo)
{
    if (!nodo)
        return VACIO;

    switch (nodo->tipo_info)
    {
    case OPERADOR_INFO:
        return nodo->info->operador.tipo;
    case LITERAL_INFO:
        return nodo->info->literal.tipo;
    case ID_INFO:
        return nodo->info->id.tipo;
    case FUNCION:
        return nodo->info->funcion.tipo;
    default:
        return VACIO;
    }
}

void *obtener_valor(Arbol *nodo)
{
    if (!nodo)
        return NULL;

    void *valor;

    switch (nodo->tipo_info)
    {
    case LITERAL_INFO:
        valor = nodo->info->literal.valor;
        break;
    case OPERADOR_INFO:
        valor = nodo->info->operador.valor;
        break;
    case ID_INFO:
        valor = nodo->info->id.valor;
        break;
    default:
        return NULL;
    }

    return valor;
}

void *calcular_op(char *op, void *valor_izq, void *valor_der, Tipo tipo)
{

    if (strcmp(op, "+") == 0)
    {
        int *valor = malloc(sizeof(int));
        *valor = *(int *)valor_izq + *(int *)valor_der;
        return valor;
    }
    else if (strcmp(op, "*") == 0)
    {
        int *valor = malloc(sizeof(int));
        *valor = *(int *)valor_izq * *(int *)valor_der;
        return valor;
    }
    else if (strcmp(op, "&&") == 0)
    {
        bool *valor = malloc(sizeof(bool));
        *valor = *(bool *)valor_izq && *(bool *)valor_der;
        return valor;
    }
    else if (strcmp(op, "||") == 0)
    {
        bool *valor = malloc(sizeof(bool));
        *valor = *(bool *)valor_izq || *(bool *)valor_der;
        return valor;
    }
    else if (strcmp(op, "==") == 0)
    {
        bool *valor = malloc(sizeof(bool));
        *valor = *(bool *)valor_izq == *(bool *)valor_der;
        return valor;
    }
    else if (strcmp(op, "!") == 0)
    {
        bool *valor = malloc(sizeof(bool));
        *valor = !*(bool *)valor_izq;
        return valor;
    }

    return NULL;
}