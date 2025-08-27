#ifndef ENUMS_H
#define ENUMS_H

typedef enum
{
    VACIO = -1,
    ENTERO,
    BOOL
} Tipo;

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
    DECLARACIONES
} Tipo_Info;

typedef enum
{
    VARIABLE
} Flag;

#endif