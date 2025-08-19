#ifndef TSA
#define TSA

typedef enum
{
    NODO_OPERADOR,
    NODO_ENTERO
} Nodo_Tipo;

typedef struct Arbol
{
    void *valor;
    Nodo_Tipo tipo_nodo;
    struct Arbol *izq;
    struct Arbol *der;
} Arbol;

Arbol *crear_arbol(void *valor, Nodo_Tipo tipo_nodo);
void asignar_hijos(Arbol *padre, Arbol *izq, Arbol *der);
void inorder(Arbol *arbol);

#endif