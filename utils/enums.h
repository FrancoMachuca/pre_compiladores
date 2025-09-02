#ifndef ENUMS_H
#define ENUMS_H

// Tipos de datos posibles
typedef enum
{
    VACIO = -1,
    ENTERO,
    BOOL
} Tipo;

// Tipos de nodos en el AST
typedef enum
{
    ID_INFO,
    OPERADOR_INFO,
    LITERAL_INFO,
    DECLARACION,
    ASIGNACION,
    PROGRAMA,
    SENTENCIAS,
    RETURN_INFO,
    DECLARACIONES,
    FUNCION
} Tipo_Info;

#endif