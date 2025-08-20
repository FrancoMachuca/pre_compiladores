#include <stdio.h>
#include <stdlib.h>
#include "tsa.h"

Arbol *crear_arbol_operador(char op, Tipo tipo, Tipo_Info tipo_info)
{
    Arbol *arbol = malloc(sizeof(Arbol));
    arbol->tipo_info = tipo_info;
    arbol->info_operador.op = op;
    arbol->info_operador.tipo = tipo;
    arbol->izq = NULL;
    arbol->der = NULL;
    
    return arbol;
}

Arbol *crear_arbol_id(char* id, Tipo tipo, Tipo_Info tipo_info)
{
    Arbol *arbol = malloc(sizeof(Arbol));
    arbol->tipo_info = tipo_info;
    arbol->info_id.id = id;
    arbol->info_id.tipo = tipo;
    arbol->izq = NULL;
    arbol->der = NULL;
    
    return arbol;
}

Arbol *crear_arbol_literal(void *valor, Tipo tipo, Tipo_Info tipo_info)
{
    Arbol *arbol = malloc(sizeof(Arbol));
    arbol->tipo_info = tipo_info;
    arbol->info_literal.valor = valor;
    arbol->info_literal.tipo = tipo;
    arbol->izq = NULL;
    arbol->der = NULL;

    return arbol;
}

void asignar_valor_id(Arbol* arbol, void* valor)
{
    if (arbol->tipo_info != ID_INFO)
    {
        printf("No es tipo id");
        return;
    }
    
    arbol->info_id.valor = valor;
}

void asignar_hijos(Arbol *padre, Arbol *izq, Arbol *der)
{
    padre->izq = izq;
    padre->der = der;
}

void inorder(Arbol *arbol)
{
    if (arbol == NULL)
        return;

    inorder(arbol->izq);

    if (arbol->tipo_info == ID_INFO)
    {
        printf("ID: %s\n", arbol->info_id.id);
    }
    else if (arbol->tipo_info == OPERADOR_INFO)
    {
        printf("Operador: %c\n", arbol->info_operador.op);
    }
    else if (arbol->tipo_info == LITERAL_INFO)
    {
        if (arbol->info_literal.tipo == ENTERO)
        {
            printf("Literal: %d\n", *(int *)arbol->info_literal.valor);
        }
        else if (arbol->info_literal.tipo == BOOL)
        {
            printf("Literal: %s\n", (*(int *)arbol->info_literal.valor) ? "true" : "false");
        }
    }

    inorder(arbol->der);
}

