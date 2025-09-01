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

void recolectarDeclaraciones(Arbol *arbol, Simbolo *tabla)
{
  if (!arbol)
    return;

  switch (arbol->tipo_info)
  {
  case DECLARACION:
    procesarDeclaracion(arbol, tabla);
    break;
  default:
    break;
  }

  recolectarDeclaraciones(arbol->izq, tabla);
  recolectarDeclaraciones(arbol->der, tabla);
}

void chequearTipos(Arbol *arbol, Simbolo *tabla)
{
  if (!arbol)
    return;

  chequearTipos(arbol->izq, tabla);
  chequearTipos(arbol->der, tabla);

  switch (arbol->tipo_info)
  {
  case ASIGNACION:
    procesarAsignacion(arbol, tabla);
    break;
  case OPERADOR_INFO:
    procesarOperador(arbol, tabla);
    break;
  case RETURN_INFO:
    procesarReturn(arbol, tabla);
    break;
  default:
    break;
  }
}

void analisisSemantico(Arbol *arbol, Simbolo *tabla)
{
  if (!arbol)
    return;

  procesarFuncion(arbol, tabla);

  recolectarDeclaraciones(arbol->izq, tabla);

  chequearTipos(arbol->der, tabla);
}

int procesarId(Arbol *hijo, Tipo_Info tipoPadre, Simbolo *tabla)
{
  char *nombre = hijo->info->id.nombre;
  Tipo_Info flag = hijo->tipo_info;
  Simbolo *simbolo = buscarSimbolo(tabla, nombre, flag);

  switch (tipoPadre)
  {
  case DECLARACION:

    if (!simbolo)
    {
      agregarSimbolo(tabla, hijo->info, flag);
    }
    else
    {
      printf("Error: variable '%s' ya declarada.\n", nombre);
    }
    break;

  default:
    if (simbolo)
    {
      hijo->info = simbolo->info;
      return 1;
    }
    else
    {
      printf("Error: variable '%s' no declarada. \n", nombre);
      return 0;
    }
    break;
  }

  return 1;
}

void procesarDeclaracion(Arbol *arbol, Simbolo *tabla)
{
  procesarId(arbol->izq, arbol->tipo_info, tabla);
}

void procesarAsignacion(Arbol *arbol, Simbolo *tabla)
{

  if (!procesarId(arbol->izq, arbol->tipo_info, tabla))
  {
    return;
  }

  Tipo tipoIzq = arbol->izq->info->id.tipo;
  Tipo tipoDer;

  switch (arbol->der->tipo_info)
  {
  case ID_INFO:
  {
    if (!procesarId(arbol->izq, arbol->tipo_info, tabla))
    {
      return;
    }
    tipoDer = arbol->der->info->id.tipo;
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

  if (tipoIzq != tipoDer)
  {
    printf("Error de tipo.\n");
    return;
  }
}

void procesarOperador(Arbol *arbol, Simbolo *tabla)
{
  if (arbol->izq->tipo_info == ID_INFO && !procesarId(arbol->izq, arbol->tipo_info, tabla))
  {
    return;
  }
  else if (arbol->der->tipo_info == ID_INFO && !procesarId(arbol->der, arbol->tipo_info, tabla))
  {
    return;
  }

  Tipo tipoIzq = obtenerTipoNodo(arbol->izq);
  Tipo tipoDer = obtenerTipoNodo(arbol->der);

  if (arbol->izq && arbol->der)
  {
    if (tipoIzq != tipoDer)
    {
      printf("Error de tipo en operador '%s'.\n", arbol->info->operador.nombre);
      return;
    }
    arbol->info->operador.tipo = tipoIzq;
  }
  else if (arbol->izq)
  {
    arbol->info->operador.tipo = tipoIzq;
  }
  else
  {
    arbol->info->operador.tipo = VACIO;
  }
}

void procesarFuncion(Arbol *arbol, Simbolo *tabla)
{
  char *nombre = arbol->info->funcion.nombre;
  Tipo_Info flag = arbol->tipo_info;

  if (buscarSimbolo(tabla, nombre, flag) == NULL)
  {
    agregarSimbolo(tabla, arbol->info, flag);
  }
  else
  {
    printf("Error: funcion '%s' ya declarada.\n", nombre);
  }
  return;
}

void procesarReturn(Arbol *arbol, Simbolo *tabla)
{

  Simbolo *simbolo_funcion = buscarSimbolo(tabla, "main", FUNCION);
  Tipo tipo_funcion = simbolo_funcion->info->funcion.tipo;

  if (!arbol->izq && tipo_funcion == VACIO)
  {
    return;
  }
  else if (!arbol->izq && tipo_funcion != VACIO)
  {
    printf("Error de tipos en return, tipo_funcion no void\n");
    return;
  }

  Tipo_Info flag = arbol->izq->tipo_info;
  Tipo tipo = obtenerTipoNodo(arbol->izq);

  char *nombre;

  switch (flag)
  {
  case ID_INFO:
    procesarId(arbol->izq, arbol->tipo_info, tabla);
    tipo = obtenerTipoNodo(arbol->izq);
    nombre = arbol->info->id.nombre;

    if (tipo_funcion != tipo)
    {
      printf("Error de tipos en return, variable: %s\n", nombre);
      return;
    }

    break;

  case OPERADOR_INFO:
    nombre = arbol->izq->info->operador.nombre;

    if (tipo_funcion != tipo)
    {
      printf("Error de tipos en return, operacion: %s\n", nombre);
    }

    break;

  case LITERAL_INFO:
    if (tipo_funcion != tipo)
    {
      printf("Error de tipos en return, literal: ");
    }

    break;
  default:
    break;
  }

  arbol->info = simbolo_funcion->info;
}

Tipo obtenerTipoNodo(Arbol *nodo)
{
  if (!nodo)
    return VACIO;

  switch (nodo->tipo_info)
  {
  case OPERADOR_INFO:
    return nodo->info->operador.tipo;
  case LITERAL_INFO:
    return nodo->info->literal.tipo;
  case ID_INFO:
    return nodo->info->id.tipo;
  case FUNCION:
    return nodo->info->funcion.tipo;
  default:
    return VACIO;
  }
}
