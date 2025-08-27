all:
	bison -d parser.y
	flex lexer.l
	gcc parser.tab.c lex.yy.c ast.c -o programa