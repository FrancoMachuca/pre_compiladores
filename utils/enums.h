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
    ENTERO,
    BOOL,
    VOID
} Tipo_Funcion;

typedef enum
{
    ID_INFO,
    OPERADOR_INFO,
    LITERAL_INFO,
    SENTENCIA_INFO,
    DECLARACION_INFO,
    INSTRUCCION_INFO
} Tipo_Info;

typedef enum
{
    VARIABLE
} Flag;

#endif