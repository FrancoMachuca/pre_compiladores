#include <stdio.h>
#include <stdlib.h>
#include "tabla.h"
#include <string.h>
#include "../AST/ast.h"


Simbolo* crearTabla() {
  Simbolo* tabla = malloc(sizeof(Simbolo));
  tabla->simbolo = NULL;
  tabla->next = NULL;
  return tabla;
}


void agregarSimbolo(Simbolo* tabla, Info_ID* id) {
  Simbolo* aux = tabla;

  while (aux->next != NULL) {
  	aux = aux->next;
  }

  Simbolo* s = malloc(sizeof(Simbolo));

  s->simbolo = id;
  s->next = NULL;

  aux->next = s;
}

Simbolo* buscarSimbolo(Simbolo* tabla, char* nombre) {
	Simbolo* aux = tabla->next;

	while (aux != NULL) {
		if (strcmp(aux->simbolo->id, nombre) == 0) {
			return aux;
		}
		aux = aux->next;
	}

	return NULL;
}

void printTabla(Simbolo* tabla) {
  Simbolo* aux = tabla->next;
  while (aux != NULL) {
    printf("%s ", aux->simbolo->id);

    int tipo = aux->simbolo->tipo;
    switch (tipo) {
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

