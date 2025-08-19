#include <stdio.h>
#include <stdlib.h>
#include "tsa.h"

Arbol *crear_arbol(void *valor, Nodo_Tipo tipo_nodo)
{
    Arbol *arbol = malloc(sizeof(Arbol));
    arbol->valor = valor;
    arbol->tipo_nodo = tipo_nodo;
    arbol->izq = NULL;
    arbol->der = NULL;
    return arbol;
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

    if (arbol->tipo_nodo == NODO_OPERADOR)
    {
        printf(" %c ", *(char *)arbol->valor);
    }
    else if (arbol->tipo_nodo == NODO_ENTERO)
    {
        printf("%d", *(int *)arbol->valor);
    }

    inorder(arbol->der);
}
