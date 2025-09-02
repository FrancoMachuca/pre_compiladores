#include <stdio.h>
#include <stdlib.h>
#include "tabla_simbolos.h"
#include <string.h>

Simbolo *crearTabla()
{
  Simbolo *tabla = malloc(sizeof(Simbolo));
  tabla->info = NULL;
  tabla->next = NULL;
  tabla->flag = VACIO;
  return tabla;
}

void agregarSimbolo(Simbolo *tabla, Info_Union *info, Tipo_Info flag)
{
  Simbolo *aux = tabla;

  while (aux->next != NULL)
  {
    aux = aux->next;
  }

  Simbolo *s = malloc(sizeof(Simbolo));

  s->info = info;
  s->next = NULL;
  s->flag = flag;

  aux->next = s;
}

Simbolo *buscarSimbolo(Simbolo *tabla, char *nombre, Tipo_Info flag)
{

  Simbolo *aux = tabla->next;

  while (aux != NULL)
  {
    switch (aux->flag)
    {
    case ID_INFO:
      if (strcmp(aux->info->id.nombre, nombre) == 0)
      {
        return aux;
      }
      break;

    case FUNCION:
      if (strcmp(aux->info->funcion.nombre, nombre) == 0)
      {
        return aux;
      }
      break;

    default:
      break;
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
