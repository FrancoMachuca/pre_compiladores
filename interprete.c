#include <stdio.h>
#include <stdlib.h>
#include "tabla_simbolos/tabla.h"
#include "parser.tab.h"
extern FILE *yyin;

void *obtener_valor(Arbol *nodo)
{
    if (!nodo)
        return NULL;

    switch (nodo->tipo_info)
    {
    case LITERAL_INFO:
        printf("[DEBUG] obtener_valor: literal = %d\n", *(int *)nodo->info->info_literal.valor);
        return nodo->info->info_literal.valor;
    case OPERADOR_INFO:
        printf("[DEBUG] obtener_valor: operador = %d\n", *(int *)nodo->info->info_operador.valor);
        return nodo->info->info_operador.valor;
    case ID_INFO:
        printf("[DEBUG] obtener_valor: id %s = %d\n", nodo->info->info_id.id, *(int *)nodo->info->info_id.valor);
        return nodo->info->info_id.valor;
    default:
        return NULL;
    }
}

Tipo obtener_tipo(Arbol *nodo)
{
    if (!nodo)
        return -1; // cuidado: antes devolvías NULL que es puntero

    switch (nodo->tipo_info)
    {
    case LITERAL_INFO:
        return nodo->info->info_literal.tipo;
    case OPERADOR_INFO:
        return nodo->info->info_operador.tipo;
    case ID_INFO:
        return nodo->info->info_id.tipo;
    default:
        return -1;
    }
}

void *calcular_op_suma(void *valor_izq, void *valor_der, Tipo tipo)
{
    switch (tipo)
    {
    case ENTERO:
    {
        int *result = malloc(sizeof(int));
        *result = *(int *)valor_izq + *(int *)valor_der;
        printf("[DEBUG] suma ENTERO: %d + %d = %d\n",
               *(int *)valor_izq, *(int *)valor_der, *result);
        return result;
    }
    case BOOL:
    {
        int *result = malloc(sizeof(int));
        *result = (*(int *)valor_izq != 0) && (*(int *)valor_der != 0);
        printf("[DEBUG] suma BOOL (&&): %d && %d = %d\n",
               *(int *)valor_izq, *(int *)valor_der, *result);
        return result;
    }
    default:
        return NULL;
    }
}

void *calcular_op_mult(void *valor_izq, void *valor_der, Tipo tipo)
{
    switch (tipo)
    {
    case ENTERO:
    {
        int *result = malloc(sizeof(int));
        *result = *(int *)valor_izq * *(int *)valor_der;
        printf("[DEBUG] mult ENTERO: %d * %d = %d\n",
               *(int *)valor_izq, *(int *)valor_der, *result);
        return result;
    }
    case BOOL:
    {
        int *result = malloc(sizeof(int));
        *result = (*(int *)valor_izq != 0) || (*(int *)valor_der != 0);
        printf("[DEBUG] mult BOOL (||): %d || %d = %d\n",
               *(int *)valor_izq, *(int *)valor_der, *result);
        return result;
    }
    default:
        return NULL;
    }
}

void *calcular_op(char op, void *valor_izq, void *valor_der, Tipo tipo)
{
    printf("[DEBUG] calcular_op: %c con tipo %d\n", op, tipo);

    switch (op)
    {
    case '+':
        return calcular_op_suma(valor_izq, valor_der, tipo);
    case '*':
        return calcular_op_mult(valor_izq, valor_der, tipo);
    default:
        printf("[DEBUG] calcular_op: operador desconocido %c\n", op);
        return NULL;
    }
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

        izq->info->info_id.valor = obtener_valor(der);

        printf("[DEBUG] Asignación: %s = %d\n",
               izq->info->info_id.id,
               *(int *)izq->info->info_id.valor);
        break;
    }

    case RETURN_INFO:
        printf("[DEBUG] RETURN encontrado (sin implementar)\n");
        break;

    case OPERADOR_INFO:
    {
        Arbol *izq = arbol->izq;
        Arbol *der = arbol->der;

        void *valor_izq = obtener_valor(izq);
        void *valor_der = obtener_valor(der);

        Tipo tipo = obtener_tipo(izq);
        char op = arbol->info->info_operador.op;

        arbol->info->info_operador.valor = calcular_op(op, valor_izq, valor_der, tipo);

        printf("[DEBUG] operador %c aplicado -> %d\n",
               op, *(int *)arbol->info->info_operador.valor);
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
    crearTablas(arbol, tabla);

    interprete(arbol);

    if (argc > 1)
        fclose(yyin); // cerramos el archivo si lo abrimos

    return 0;
}