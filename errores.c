#include "errores.h"
#include <stdio.h>
#include <string.h>

// Arreglo de errores
Error errores[MAX_ERRORES];
int cantErrores = 0;

void reportarError(CodigoError codigo, const char *info) {
    if (cantErrores >= MAX_ERRORES) return;

    errores[cantErrores].codigo = codigo;

    switch(codigo) {
        case VAR_NO_DECLARADA:
            snprintf(errores[cantErrores].mensaje, MAX_MSG, "Error: variable '%s' no declarada", info);
            break;
        case VAR_YA_DECLARADA:
            snprintf(errores[cantErrores].mensaje, MAX_MSG, "Error: variable '%s' ya declarada", info);
            break;
        case FUN_NO_DECLARADA:
            snprintf(errores[cantErrores].mensaje, MAX_MSG, "Error: función '%s' no declarada", info);
            break;
        case FUN_YA_DECLARADA:
            snprintf(errores[cantErrores].mensaje, MAX_MSG, "Error: función '%s' ya declarada", info);
            break;    
        case TIPO_INCOMPATIBLE:
            snprintf(errores[cantErrores].mensaje, MAX_MSG, "Error: tipo incompatible '%s'", info);
            break;
    }

    cantErrores++;
}

void mostrarErrores(void) {
    for (int i = 0; i < cantErrores; i++) {
        printf("%s\n", errores[i].mensaje);
    }
}