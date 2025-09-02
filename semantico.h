#ifndef SEMANTICO_H
#define SEMANTICO_H

#include "AST/ast.h"
#include "tabla_simbolos/tabla_simbolos.h"
#include "errores.h"

void recolectarDeclaraciones(Arbol *arbol, Simbolo *tabla);
void chequearTipos(Arbol *arbol, Simbolo *tabla);
void analisisSemantico(Arbol *arbol, Simbolo *tabla);
int procesarId(Arbol *hijo, Tipo_Info tipoPadre, Simbolo *tabla);
void procesarAsignacion(Arbol *arbol, Simbolo *tabla);
void procesarDeclaracion(Arbol *arbol, Simbolo *tabla);
void procesarOperador(Arbol *arbol, Simbolo *tabla);
void procesarFuncion(Arbol *arbol, Simbolo *tabla);
void procesarReturn(Arbol *arbol, Simbolo *tabla);

#endif