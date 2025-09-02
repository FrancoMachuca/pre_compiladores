#ifndef AST
#define AST
#include "enums.h"

/**
 * Información asociada a un identificador en el árbol.
 */
typedef struct Info_ID
{
    char *nombre;
    void *valor;
    Tipo tipo;
} Info_ID;

/**
 * Información asociada a un operador en el árbol.
 */
typedef struct Info_Operador
{
    char *nombre;
    void *valor;
    Tipo tipo;
} Info_Operador;

/**
 * Información asociada a un literal (entero, booleano, etc.).
 */
typedef struct Info_Literal
{
    void *valor;
    Tipo tipo;
} Info_Literal;

/**
 * Información asociada a una función.
 */
typedef struct Info_Funcion
{
    char *nombre;
    void *valor;
    Tipo tipo;
} Info_Funcion;

/**
 * Unión que agrupa la información posible en un nodo del árbol.
 */
typedef struct Info_Union
{
    Info_ID id;
    Info_Operador operador;
    Info_Literal literal;
    Info_Funcion funcion;
} Info_Union;


/**
 * Nodo del árbol de sintaxis abstracta (AST).
 */
typedef struct Arbol
{
    Info_Union *info;
    Tipo_Info tipo_info;
    int linea;
    int colum;
    struct Arbol *izq;
    struct Arbol *der;
} Arbol;

/**
 * Crea un nodo operador del AST.
 *
 * @param op     Nombre del operador
 * @param valor  Valor asociado al operador (si lo hubiera)
 * @param linea  Línea del código fuente
 * @param colum  Columna del código fuente
 * @param izq    Hijo izquierdo
 * @param der    Hijo derecho
 * @return       Puntero al nuevo nodo operador
 */
Arbol *crear_arbol_operador(char *op, void *valor, int linea, int colum, Arbol *izq, Arbol *der);

/**
 * Crea un nodo identificador del AST.
 *
 * @param id     Nombre del identificador
 * @param linea  Línea del código fuente
 * @param colum  Columna del código fuente
 * @param izq    Hijo izquierdo
 * @param der    Hijo derecho
 * @return       Puntero al nuevo nodo identificador
 */
Arbol *crear_arbol_id(char *id, int linea, int colum, Arbol *izq, Arbol *der);

/**
 * Crea un nodo literal del AST.
 *
 * @param valor  Valor del literal
 * @param tipo   Tipo del literal
 * @param linea  Línea del código fuente
 * @param colum  Columna del código fuente
 * @param izq    Hijo izquierdo
 * @param der    Hijo derecho
 * @return       Puntero al nuevo nodo literal
 */
Arbol *crear_arbol_literal(void *valor, Tipo tipo, int linea, int colum, Arbol *izq, Arbol *der);

/**
 * Crea un nodo función del AST.
 *
 * @param nombre Nombre de la función
 * @param tipo   Tipo de retorno de la función
 * @param linea  Línea del código fuente
 * @param colum  Columna del código fuente
 * @param izq    Hijo izquierdo
 * @param der    Hijo derecho
 * @return       Puntero al nuevo nodo función
 */
Arbol *crear_arbol_funcion(char *nombre, Tipo tipo, int linea, int colum, Arbol *izq, Arbol *der);

/**
 * Crea un nodo genérico del AST.
 *
 * @param tipo   Tipo de nodo (ver @ref Tipo_Info)
 * @param linea  Línea del código fuente
 * @param colum  Columna del código fuente
 * @param izq    Hijo izquierdo
 * @param der    Hijo derecho
 * @return       Puntero al nuevo nodo
 */
Arbol *crear_arbol_nodo(Tipo_Info tipo, int linea, int colum, Arbol *izq, Arbol *der);

/**
 * Recorre el árbol en orden e imprime los nodos.
 *
 * @param arbol Raíz del árbol a recorrer
 */
void inorder(Arbol *arbol);

/**
 * Imprime el árbol en forma vertical (formato de árbol).
 *
 * @param arbol     Raíz del árbol a imprimir
 * @param prefijo   Prefijo usado para alinear ramas
 * @param es_ultimo Indica si el nodo es el último hijo
 */
void imprimir_vertical(Arbol *arbol, char *prefijo, int es_ultimo);

#endif