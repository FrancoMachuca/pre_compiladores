#ifndef HELPERS_H
#define HELPERS_H
#include "enums.h"
#include "../AST/ast.h"

void print_valor(Tipo tipo, void *valor, const char *prefix);
Tipo obtenerTipoNodo(Arbol *nodo);
void *obtener_valor(Arbol *nodo);
void *calcular_op(char *op, void *valor_izq, void *valor_der, Tipo tipo);

#endif