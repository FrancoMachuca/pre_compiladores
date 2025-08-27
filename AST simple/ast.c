#include <stdio.h>
#include <stdlib.h>
#include "ast.h"

Nodo* newNodoNum(int value) {
    Nodo* n = malloc(sizeof(Nodo));
    n->tipo = TNUM;
    n->info.num = value;
    n->left = NULL;
    n->right = NULL;
    return n;
}

Nodo* newNodoOp(char value, Nodo* left, Nodo* right) {
    Nodo* n = malloc(sizeof(Nodo));
    n->tipo = TOP;
    n->info.op = value;
    n->left = left;
    n->right = right;
    return n;
}

int eval(Nodo* n) {
  switch (n->tipo) {
    case TNUM:
      return n->info.num;

    case TOP: {
      int n1 = eval(n->left);
      int n2 = eval(n->right);

      switch (n->info.op) {
        case '+': return n1 + n2;
        case '*': return n1 * n2;
      }
    }
  }
  return 0;
}