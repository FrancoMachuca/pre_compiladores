#include <stdio.h>
#include <stdlib.h>
#include "ast.h"
#include <string.h>

Arbol *crear_arbol_operador(char op, void *valor, Arbol *izq, Arbol *der)
{
    Arbol *arbol = malloc(sizeof(Arbol));
    arbol->tipo_info = OPERADOR_INFO;
    arbol->info_operador.op = op;
    arbol->info_operador.valor = valor;
    arbol->info_operador.tipo = VACIO;
    arbol->izq = izq;
    arbol->der = der;

    return arbol;
}

Arbol *crear_arbol_id(char *id, Arbol *izq, Arbol *der)
{
    Arbol *arbol = malloc(sizeof(Arbol));
    arbol->tipo_info = ID_INFO;
    arbol->info_id.id = strdup(id);
    arbol->info_id.tipo = VACIO;
    arbol->izq = izq;
    arbol->der = der;

    return arbol;
}

Arbol *crear_arbol_literal(void *valor, Tipo tipo, Arbol *izq, Arbol *der)
{
    Arbol *arbol = malloc(sizeof(Arbol));
    arbol->tipo_info = LITERAL_INFO;
    arbol->info_literal.valor = valor;
    arbol->info_literal.tipo = tipo;
    arbol->izq = izq;
    arbol->der = der;

    return arbol;
}

Arbol *crear_arbol_sentencia(char *sentencia, Arbol *izq, Arbol *der)
{
    Arbol *arbol = malloc(sizeof(Arbol));
    arbol->tipo_info = SENTENCIA_INFO;
    arbol->info_sentencia.sentencia = strdup(sentencia);
    arbol->izq = izq;
    arbol->der = der;

    return arbol;
}

Arbol *crear_arbol_declaracion(char *declaracion, Tipo tipo, Arbol *izq, Arbol *der)
{
    Arbol *arbol = malloc(sizeof(Arbol));
    arbol->tipo_info = DECLARACION_INFO;
    arbol->info_declaracion.declaracion = strdup(declaracion);
    arbol->info_declaracion.tipo = tipo;
    arbol->izq = izq;
    arbol->der = der;

    return arbol;
}

Arbol *crear_arbol_instruccion(char *instruccion, Arbol *izq, Arbol *der)
{
    Arbol *arbol = malloc(sizeof(Arbol));
    arbol->tipo_info = DECLARACION_INFO;
    arbol->info_instruccion.instruccion = strdup(instruccion);
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
        printf("ID(%s)\n", arbol->info_id.id);
    }
    else if (arbol->tipo_info == OPERADOR_INFO)
    {
        printf("Op(%c)\n", arbol->info_operador.op);
    }
    else if (arbol->tipo_info == LITERAL_INFO)
    {
        if (arbol->info_literal.tipo == ENTERO)
            printf("Lit(%d)\n", *(int *)arbol->info_literal.valor);
        else if (arbol->info_literal.tipo == BOOL)
            printf("Lit(%s)\n", (*(int *)arbol->info_literal.valor) ? "true" : "false");
    }
    else if (arbol->tipo_info == SENTENCIA_INFO)
    {
        printf("Sent(%s)\n", arbol->info_sentencia.sentencia);
    }
    else if (arbol->tipo_info == DECLARACION_INFO)
    {
        printf("Decl(%s)\n", arbol->info_declaracion.declaracion);
    }
    else if (arbol->tipo_info == INSTRUCCION_INFO)
    {
        printf("Instr(%s)\n", arbol->info_instruccion.instruccion);
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
