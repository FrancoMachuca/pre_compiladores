#ifndef ERRORES_H
#define ERRORES_H

#define MAX_ERRORES 100
#define MAX_MSG 100

typedef enum {
    VAR_NO_DECLARADA,
    VAR_YA_DECLARADA,
    FUN_NO_DECLARADA,
    FUN_YA_DECLARADA,
    TIPO_INCOMPATIBLE
} CodigoError;

typedef struct {
    CodigoError codigo;
    char mensaje[MAX_MSG];
} Error;

// Funciones
void reportarError(CodigoError codigo, const char *info);
void mostrarErrores(void);

#endif