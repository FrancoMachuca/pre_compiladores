#include <stdio.h>
#include <stdlib.h>
#include "tabla_simbolos.h"
#include <string.h>

Simbolo *crearTabla()
{
  Simbolo *tabla = malloc(sizeof(Simbolo));
  tabla->info = NULL;
  tabla->next = NULL;
  return tabla;
}

void agregarSimbolo(Simbolo *tabla, Info_Union *info)
{
  Simbolo *aux = tabla;

  while (aux->next != NULL)
  {
    aux = aux->next;
  }

  Simbolo *s = malloc(sizeof(Simbolo));

  s->info = info;
  s->next = NULL;

  aux->next = s;
}

Simbolo *buscarSimbolo(Simbolo *tabla, char *nombre)
{
  Simbolo *aux = tabla->next;

  while (aux != NULL)
  {
    if (strcmp(aux->info->id.nombre, nombre) == 0)
    {
      return aux;
    }
    aux = aux->next;
  }

  return NULL;
}

void printTabla(Simbolo *tabla)
{
  Simbolo *aux = tabla->next;
  while (aux != NULL)
  {
    printf("%s ", aux->info->id.nombre);

    int tipo = aux->info->id.tipo;
    switch (tipo)
    {
    case 0:
      printf("Entero\n");
      break;
    case 1:
      printf("Bool\n");
      break;
    }

    aux = aux->next;
  }
}

void analisisSemantico(Arbol *arbol, Simbolo *tabla)
{
  if (arbol == NULL) return;

  analisisSemantico(arbol->izq, tabla);
  analisisSemantico(arbol->der, tabla);

  switch (arbol->tipo_info) {
    case DECLARACION:
      procesarDeclaracion(arbol, tabla);
      break;
    case ASIGNACION:
      procesarAsignacion(arbol, tabla);
      break;
    case OPERADOR_INFO:
      procesarOperador(arbol);
      break;
    default:
      break;
  }
}

void procesarDeclaracion(Arbol *arbol, Simbolo *tabla)
{
  char *nombre = arbol->izq->info->id.nombre;

  if (buscarSimbolo(tabla, nombre) == NULL) {
    agregarSimbolo(tabla, arbol->izq->info);
  } else {
    printf("Error: variable '%s' ya declarada.\n", nombre);
  }
}

void procesarAsignacion(Arbol *arbol, Simbolo *tabla)
{
  char *nombre = arbol->izq->info->id.nombre;
  Simbolo *simbolo = buscarSimbolo(tabla, nombre);

  if (!simbolo) {
    printf("Variable %s no declarada.\n", nombre);
    return;
  }

  Tipo tipoIzq = simbolo->info->id.tipo;
  Tipo tipoDer;

  switch (arbol->der->tipo_info) {
    case ID_INFO: {
      char *nombreDerecho = arbol->der->info->id.nombre;
      Simbolo *simDerecho = buscarSimbolo(tabla, nombreDerecho);
      if (!simDerecho) {
        printf("Variable %s no declarada.\n", nombreDerecho);
        return;
      }
      tipoDer = simDerecho->info->id.tipo;
      arbol->der->info = simDerecho->info;
      break;
    }
    case LITERAL_INFO:
      tipoDer = arbol->der->info->literal.tipo;
      break;
    case OPERADOR_INFO:
      tipoDer = arbol->der->info->operador.tipo;
      break;
    default:
      printf("Error: tipo de nodo derecho no válido.\n");
      return;
  }

  if (tipoIzq != tipoDer) {
    printf("Error de tipo.\n");
    return;
  }

  arbol->izq->info = simbolo->info;
}


void procesarOperador(Arbol *arbol)
{
  Tipo tipoIzq = obtenerTipoNodo(arbol->izq);
  Tipo tipoDer = obtenerTipoNodo(arbol->der);

  if (arbol->izq && arbol->der) {
    if (tipoIzq != tipoDer) {
      printf("Error de tipo en operador '%s'.\n", arbol->info->operador.nombre);
      return;
    }
    arbol->info->operador.tipo = tipoIzq;
  }
  else if (arbol->izq) {
    arbol->info->operador.tipo = tipoIzq;
  }
  else {
    arbol->info->operador.tipo = VACIO;
  }
}


Tipo obtenerTipoNodo(Arbol *nodo) {
  if (!nodo) return VACIO;

  switch (nodo->tipo_info) {
    case OPERADOR_INFO: return nodo->info->operador.tipo;
    case LITERAL_INFO:  return nodo->info->literal.tipo;
    case ID_INFO:       return nodo->info->id.tipo;
    default: return VACIO;
  }
}
