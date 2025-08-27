#include <stdio.h>
#include <stdlib.h>
#include "tabla.h"
#include <string.h>

Simbolo *crearTabla()
{
  Simbolo *tabla = malloc(sizeof(Simbolo));
  tabla->simbolo = NULL;
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

  s->simbolo = info;
  s->next = NULL;

  aux->next = s;
}

Simbolo *buscarSimbolo(Simbolo *tabla, char *nombre)
{
  Simbolo *aux = tabla->next;

  while (aux != NULL)
  {
    if (strcmp(aux->simbolo->info_id.id, nombre) == 0)
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
    printf("%s ", aux->simbolo->info_id.id);

    int tipo = aux->simbolo->info_id.tipo;
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

void crearTablas(Arbol *arbol, Simbolo *tabla)
{
  if (arbol == NULL)
    return;

  crearTablas(arbol->izq, tabla);
  crearTablas(arbol->der, tabla);

  if (arbol->tipo_info == DECLARACION)
  {
    Arbol *id = arbol->izq;

    char *nombre = id->info->info_id.id;

    if (buscarSimbolo(tabla, nombre) == NULL)
    {
      agregarSimbolo(tabla, id->info);
    }
    else
    {
      printf("Variable %s ya declarada.\n", nombre);
      return;
    }
  }

  if (arbol->tipo_info == ASIGNACION)
  {
    char *nombre = arbol->izq->info->info_id.id;

    Simbolo *s = buscarSimbolo(tabla, nombre);

    if (s == NULL)
    {
      printf("Variable %s no declarada.\n", nombre);
      return;
    }

    Tipo tipo = s->simbolo->info_id.tipo;

    if (arbol->der->tipo_info == OPERADOR_INFO)
    {
      Tipo t = arbol->der->info->info_operador.tipo;

      if (tipo != t)
      {
        printf("Error de tipo.\n");
        return;
      }
    }
    else if (arbol->der->tipo_info == LITERAL_INFO)
    {
      Tipo t = arbol->der->info->info_literal.tipo;

      if (tipo != t)
      {
        printf("Error de tipo.\n");
        return;
      }
    }
    else if (arbol->der->tipo_info == ID_INFO)
    {
      char *nombre2 = arbol->der->info->info_id.id;
      Simbolo *q = buscarSimbolo(tabla, nombre2);

      Tipo t1 = q->simbolo->info_id.tipo;

      if (tipo != t1)
      {
        printf("Error de tipo.\n");
        return;
      }

      arbol->der->info = q->simbolo;
    }

    arbol->izq->info = s->simbolo;
  }

  if (arbol->tipo_info == OPERADOR_INFO)
  {
    Tipo izq = arbol->izq->info->info_operador.tipo;

    Tipo der = arbol->der->info->info_operador.tipo;

    if (izq != der)
    {
      printf("Error de tipo.\n");
      return;
    }
    else
    {
      arbol->info->info_operador.tipo = izq;
    }
  }
}
