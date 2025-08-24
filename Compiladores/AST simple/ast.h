#ifndef AST_H
#define AST_H

typedef enum { TNUM, TOP } tipoNodo;

typedef struct Nodo {
    tipoNodo tipo;
    union {
        int num;
        char op;
    } info;
    struct Nodo* left;
    struct Nodo* right;
} Nodo;

Nodo* newNodoNum(int value);
Nodo* newNodoOp(char value, Nodo* left, Nodo* right);
int eval(Nodo* n);

#endif
