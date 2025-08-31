#include <stdio.h>
#include <stdlib.h>
#include "ast.h"
#include <string.h>
#include <stdbool.h>
#include "../tabla_simbolos/tabla_simbolos.h"

Arbol *crear_arbol_operador(char *op, void *valor, Arbol *izq, Arbol *der)
{
    Arbol *arbol = malloc(sizeof(Arbol));
    arbol->info = malloc(sizeof(Info_Union));
    arbol->tipo_info = OPERADOR_INFO;
    arbol->info->operador.nombre = strdup(op);
    arbol->info->operador.valor = valor;
    arbol->info->operador.tipo = VACIO;
    arbol->izq = izq;
    arbol->der = der;

    return arbol;
}

Arbol *crear_arbol_id(char *id, Arbol *izq, Arbol *der)
{
    Arbol *arbol = malloc(sizeof(Arbol));
    arbol->info = malloc(sizeof(Info_Union));
    arbol->tipo_info = ID_INFO;
    arbol->info->id.nombre = strdup(id);
    arbol->info->id.valor = NULL;
    arbol->info->id.tipo = VACIO;
    arbol->izq = izq;
    arbol->der = der;

    return arbol;
}

Arbol *crear_arbol_literal(void *valor, Tipo tipo, Arbol *izq, Arbol *der)
{
    Arbol *arbol = malloc(sizeof(Arbol));
    arbol->info = malloc(sizeof(Info_Union));
    arbol->tipo_info = LITERAL_INFO;
    arbol->info->literal.valor = valor;
    arbol->info->literal.tipo = tipo;
    arbol->izq = izq;
    arbol->der = der;

    return arbol;
}

Arbol *crear_arbol_funcion(char *nombre, Tipo tipo, Arbol *izq, Arbol *der)
{
    Arbol *arbol = malloc(sizeof(Arbol));
    arbol->info = malloc(sizeof(Info_Union));
    arbol->tipo_info = FUNCION;
    arbol->info->funcion.valor = NULL;
    arbol->info->funcion.nombre = strdup(nombre);
    arbol->info->funcion.tipo = tipo;
    arbol->izq = izq;
    arbol->der = der;

    return arbol;
}

Arbol *crear_arbol_nodo(Tipo_Info tipo, Arbol *izq, Arbol *der)
{
    Arbol *arbol = malloc(sizeof(Arbol));
    arbol->info = malloc(sizeof(Info_Union));
    arbol->tipo_info = tipo;
    arbol->izq = izq;
    arbol->der = der;

    return arbol;
}

void inorder(Arbol *arbol)
{
    if (arbol == NULL)
        return;

    inorder(arbol->izq);

    if (arbol->tipo_info == ID_INFO)
    {
        printf("ID: %s\n", arbol->info->id.nombre);
    }
    else if (arbol->tipo_info == OPERADOR_INFO)
    {
        printf("Operador: %s\n", arbol->info->operador.nombre);
    }
    else if (arbol->tipo_info == LITERAL_INFO)
    {
        if (arbol->info->literal.tipo == ENTERO)
        {
            printf("Literal: %d\n", *(int *)arbol->info->literal.valor);
        }
        else if (arbol->info->literal.tipo == BOOL)
        {
            printf("Literal: %s\n", (*(int *)arbol->info->literal.valor) ? "true" : "false");
        }
    }

    inorder(arbol->der);
}

void imprimir_vertical(Arbol *arbol, char *prefijo, int es_ultimo)
{
    if (arbol == NULL)
        return;

    // imprimir prefijo y rama
    printf("%s", prefijo);

    if (es_ultimo)
    {
        printf("└── ");
    }
    else
    {
        printf("├── ");
    }

    // imprimir el nodo según su tipo
    if (arbol->tipo_info == ID_INFO)
    {
        printf("ID(%s)\n", arbol->info->id.nombre);
    }
    else if (arbol->tipo_info == OPERADOR_INFO)
    {
        printf("Op(%s)\n", arbol->info->operador.nombre);
    }
    else if (arbol->tipo_info == LITERAL_INFO)
    {
        if (arbol->info->literal.tipo == ENTERO)
            printf("Lit(%d)\n", *(int *)arbol->info->literal.valor);
        else if (arbol->info->literal.tipo == BOOL)
            printf("Lit(%s)\n", (*(int *)arbol->info->literal.valor) ? "true" : "false");
    }
    else if (arbol->tipo_info == DECLARACION)
    {
        printf("DECLARACION\n");
    }
    else if (arbol->tipo_info == DECLARACIONES)
    {
        printf("DECLARACIONES\n");
    }
    else if (arbol->tipo_info == SENTENCIAS)
    {
        printf("SENTENCIAS\n");
    }
    else if (arbol->tipo_info == PROGRAMA)
    {
        printf("PROGRAMA\n");
    }
    else if (arbol->tipo_info == RETURN_INFO)
    {
        printf("RETURN_INFO\n");
    }
    else if (arbol->tipo_info == ASIGNACION)
    {
        printf("ASIGNACION\n");
    }

    // nuevo prefijo para los hijos
    char nuevo_prefijo[1024];
    strcpy(nuevo_prefijo, prefijo);
    if (es_ultimo)
        strcat(nuevo_prefijo, "    ");
    else
        strcat(nuevo_prefijo, "│   ");

    // contar hijos (izq + der) para saber cuál es el último
    int hijos = 0;
    if (arbol->izq)
        hijos++;
    if (arbol->der)
        hijos++;

    if (arbol->izq)
        imprimir_vertical(arbol->izq, nuevo_prefijo, (hijos == 1 && !arbol->der));
    if (arbol->der)
        imprimir_vertical(arbol->der, nuevo_prefijo, 1);
}
