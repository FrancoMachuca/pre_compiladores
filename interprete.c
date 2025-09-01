#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tabla_simbolos/tabla_simbolos.h"
#include "parser.tab.h"
extern FILE *yyin;

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

Tipo obtener_tipo(Arbol *nodo)
{
    if (!nodo)
        return -1; // cuidado: antes devolvías NULL que es puntero

    switch (nodo->tipo_info)
    {
    case LITERAL_INFO:
        return nodo->info->literal.tipo;
    case OPERADOR_INFO:
        return nodo->info->operador.tipo;
    case ID_INFO:
        return nodo->info->id.tipo;
    default:
        return -1;
    }
}

void *obtener_valor(Arbol *nodo)
{
    if (!nodo)
        return NULL;

    Tipo tipo;
    void *valor;

    switch (nodo->tipo_info)
    {
    case LITERAL_INFO:
        tipo = obtener_tipo(nodo);
        valor = nodo->info->literal.valor;
        print_valor(tipo, valor, "[INTERPRETE] obtener_valor: literal = ");
        break;
    case OPERADOR_INFO:
        tipo = obtener_tipo(nodo);
        valor = nodo->info->operador.valor;
        print_valor(tipo, valor, "[INTERPRETE] obtener_valor: operador = ");
        break;
    case ID_INFO:
        tipo = obtener_tipo(nodo);
        valor = nodo->info->id.valor;
        print_valor(tipo, valor, "[INTERPRETE] obtener_valor: id = ");
        break;
    default:
        return NULL;
    }

    return valor;
}

void *calcular_op(char *op, void *valor_izq, void *valor_der, Tipo tipo)
{
    switch (tipo)
    {
    case ENTERO:
        printf("[INTERPRETE] calcular_op: %s con tipo %s\n", op, "Entero");
        break;
    case BOOL:
        printf("[INTERPRETE] calcular_op: %s con tipo %s\n", op, "Booleano");
        break;
    default:
        break;
    }

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

void interprete(Arbol *arbol)
{
    if (arbol == NULL)
        return;

    interprete(arbol->izq);
    interprete(arbol->der);

    Tipo_Info tipo_raiz = arbol->tipo_info;

    switch (tipo_raiz)
    {
    case ASIGNACION:
    {
        Arbol *izq = arbol->izq;
        Arbol *der = arbol->der;

        void *valor = obtener_valor(der);
        izq->info->id.valor = valor;
        Tipo tipo = obtener_tipo(izq);

        printf("[INTERPRETE] Asignación: %s = ",
               izq->info->id.nombre);
        print_valor(tipo, valor, "");

        break;
    }

    case RETURN_INFO:
        void *valor = obtener_valor(arbol->izq);
        Tipo tipo = obtener_tipo(arbol->izq);

        if (tipo == VACIO)
        {
            printf("[INTERPRETE] RETURN void\n");
            return;
        }

        print_valor(tipo, valor, "[INTERPRETE] RETURN ");

        break;

    case OPERADOR_INFO:
    {
        Arbol *izq = arbol->izq;
        Arbol *der = arbol->der;

        void *valor_izq = obtener_valor(izq);
        void *valor_der = obtener_valor(der);

        Tipo tipo = obtener_tipo(izq);
        char *op = strdup(arbol->info->operador.nombre);

        arbol->info->operador.valor = calcular_op(op, valor_izq, valor_der, tipo);
        void *valor = arbol->info->operador.valor;

        printf("[INTERPRETE] operador %s aplicado -> ", op);
        print_valor(tipo, valor, "");

        free(op);
        break;
    }

    default:
        break;
    }
}

int main(int argc, char **argv)
{
    if (argc > 1)
    {
        FILE *archivo = fopen(argv[1], "r");
        if (!archivo)
        {
            perror("No se pudo abrir el archivo");
            return 1;
        }
        yyin = archivo; // importante: yyin es global de Flex
    }

    Arbol *arbol = NULL;

    if (yyparse(&arbol) != 0)
    {
        fprintf(stderr, "Error en el parseo.\n");
        return 1;
    }

    Simbolo *tabla = crearTabla();
    analisisSemantico(arbol, tabla);

    interprete(arbol);

    if (argc > 1)
        fclose(yyin); // cerramos el archivo si lo abrimos

    return 0;
}