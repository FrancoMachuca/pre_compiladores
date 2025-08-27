#ifndef TS
#define TS

#include "../utils/enums.h"
// no incluyas ast.h aquí

// Forward declaration
typedef struct Info_ID Info_ID;

typedef struct Simbolo {
    Info_ID* simbolo;
    struct Simbolo* next;
} Simbolo;

Simbolo* crearTabla();

void agregarSimbolo(Simbolo* tabla, Info_ID* id);

Simbolo* buscarSimbolo(Simbolo* tabla, char* nombre);

void printTabla(Simbolo* tabla);

#endif
