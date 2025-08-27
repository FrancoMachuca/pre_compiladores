#include <stdio.h>
#include <stdlib.h>
#include "ast.h"
#include <string.h>
#include "../tabla_simbolos/tabla.h"

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

Arbol *crear_arbol_nodo(Tipo_Info tipo, Arbol *izq, Arbol *der)
{
    Arbol *arbol = malloc(sizeof(Arbol));
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
        printf("RETURN\n");
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


void crearTablas(Arbol* arbol, Simbolo* tabla) {
    if (arbol == NULL)
        return;

    crearTablas(arbol->izq, tabla);
    crearTablas(arbol->der, tabla);

    if (arbol->tipo_info == DECLARACION) {
        Arbol* id = arbol->izq;

        char* nombre = id->info_id.id;

        if (buscarSimbolo(tabla, nombre) == NULL) {
            agregarSimbolo(tabla, &id->info_id);
        } else {
            printf("Variable %s ya declarada.\n", nombre);
            return;
        }
    }


    if (arbol->tipo_info == ASIGNACION) {
        char* nombre = arbol->izq->info_id.id;

        Simbolo* s = buscarSimbolo(tabla, nombre);

        if (s == NULL) {
            printf("Variable %s no declarada.\n", nombre);
            return;
        }

        Tipo tipo = s->simbolo->tipo;

        if (arbol->der->tipo_info == OPERADOR_INFO) {
            Tipo t = arbol->der->info_operador.tipo;

            if (tipo != t) {
                printf("Error de tipo.\n");
                return;
            }

        } else if (arbol->der->tipo_info == LITERAL_INFO) {
            Tipo t = arbol->der->info_literal.tipo;

            if (tipo != t) {
                printf("Error de tipo.\n");
                return;
            }
        }
        else if (arbol->der->tipo_info == ID_INFO) {
            char* nombre2 = arbol->der->info_id.id;
            Simbolo* q = buscarSimbolo(tabla, nombre2);

            Tipo t1 = q->simbolo->tipo;

            if (tipo != t1) {
                printf("Error de tipo.\n");
                return;
            }
        }
    }

    if (arbol->tipo_info == OPERADOR_INFO) {
        Tipo izq = arbol->izq->info_operador.tipo;

        Tipo der = arbol->der->info_operador.tipo;

        if (izq != der) {
            printf("Error de tipo.\n");
            return;
        } else {
            arbol->info_operador.tipo = izq;
        }
    
    }
}
