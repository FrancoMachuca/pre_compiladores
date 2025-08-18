all:
	bison -d parser.y
	flex ej1.lex
	gcc parser.tab.c lex.yy.c -o programa -lfl