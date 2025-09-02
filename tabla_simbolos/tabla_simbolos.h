#ifndef TS
#define TS

#include "../AST/ast.h"

/**
 * Representa un símbolo en la tabla de símbolos.
 */
typedef struct Simbolo
{
    Info_Union *info;
    struct Simbolo *next;
    Tipo_Info flag;
} Simbolo;

/**
 * Crea una nueva tabla de símbolos vacía.
 *
 * @return Puntero a la tabla creada.
 */
Simbolo *crearTabla();

/**
 * Agrega un nuevo símbolo a la tabla.
 *
 * @param tabla Puntero a la tabla de símbolos
 * @param info  Información asociada al símbolo
 * @param flag  Tipo de símbolo (ej. ID_INFO, FUNCION)
 */
void agregarSimbolo(Simbolo *tabla, Info_Union *info, Tipo_Info flag);

/**
 * Busca un símbolo en la tabla por nombre.
 *
 * @param tabla  Puntero a la tabla de símbolos
 * @param nombre Nombre del símbolo a buscar
 * @param flag   Tipo de símbolo (ej. ID_INFO, FUNCION)
 * @return       Puntero al símbolo si se encuentra, NULL si no existe
 */
Simbolo *buscarSimbolo(Simbolo *tabla, char *nombre, Tipo_Info flag);

/**
 * Imprime el contenido de la tabla de símbolos.
 *
 * @param tabla Puntero a la tabla de símbolos
 */
void printTabla(Simbolo *tabla);

#endif
