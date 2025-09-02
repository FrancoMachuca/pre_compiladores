#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tabla_simbolos.h"
#include "helpers.h"
#include "errores.h"
#include "semantico.h"
#include "parser.tab.h"
extern FILE *yyin;

/**
 * Recorre el AST y ejecuta la interpretación del programa.
 *
 * Procesa las asignaciones, operaciones y sentencias return.
 * Cada nodo se interpreta recursivamente en postorden (izq → der → raíz).
 *
 * @param arbol Árbol de sintaxis abstracta (AST) a interpretar
 */
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
        Tipo tipo = obtenerTipoNodo(izq);

        printf("[INTERPRETE] Asignación: %s = ",
               izq->info->id.nombre);
        print_valor(tipo, valor, "");

        break;
    }

    case RETURN_INFO:
        void *valor = obtener_valor(arbol->izq);
        Tipo tipo = obtenerTipoNodo(arbol->izq);

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

        Tipo tipo = obtenerTipoNodo(izq);
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
        yyin = archivo;
    }

    Arbol *arbol = NULL;

    if (yyparse(&arbol) != 0)
    {
        fprintf(stderr, "Error en el parseo.\n");
        return 1;
    }

    Simbolo *tabla = crearTabla();
    analisisSemantico(arbol, tabla);
    mostrarErrores();

    interprete(arbol);

    if (argc > 1)
        fclose(yyin); // cerramos el archivo si lo abrimos

    return 0;
}