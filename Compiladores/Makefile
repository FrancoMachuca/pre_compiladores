all:
	bison -d parser.y
	flex ej1.l
	gcc parser.tab.c lex.yy.c -o programa -lfl