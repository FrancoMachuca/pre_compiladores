all:
	bison -d parser.y
	flex ej1.l
	gcc parser.tab.c lex.yy.c AST/ast.c tabla_simbolos/tabla.c -o programa -lfl
