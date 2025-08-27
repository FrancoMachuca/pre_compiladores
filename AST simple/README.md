# Archivos

## 1. Lexer

Reconoce:

* Números enteros (`NUM`)
* Operadores `+` y `*`
* Saltos de línea (`\n`) como final de expresión
* Ignora espacios y tabulaciones

---

## 2. Parser

El parser define la **gramática** y cómo se deben combinar los tokens.
Construye un **Árbol Sintáctico Abstracto (AST)** donde:

* Los **nodos hoja** son números
* Los **nodos internos** son operadores (`+`, `*`) con hijos izquierdo y derecho

La raíz del árbol representa toda la expresión, y se puede **evaluar recursivamente** para obtener el resultado final.
Respeta la **precedencia** (`*` antes de `+`).

---

## 3. Árbol Sintáctico Abstracto (AST)

El AST se define con nodos que pueden ser:

* **Número (TNUM)** → almacena un valor entero
* **Operador (TOP)** → almacena el operador y apunta a los hijos izquierdo y derecho

Este árbol permite evaluar correctamente la expresión.
Por ejemplo, para la expresión `3 + 5 * 2`, el AST sería:

```
      +
     / \
    3   *
       / \
      5   2
```

Se evalúa primero `5 * 2` y luego se suma `3`.
