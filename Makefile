CC = gcc
CFLAGS = -g -Wall
LEX = flex
YACC = bison -d
LDFLAGS = -lfl

# Fuentes
SRC = parser.tab.c lex.yy.c AST/ast.c tabla_simbolos/tabla.c interprete.c
OBJ = $(SRC:.c=.o)

# Ejecutables
PROG = programa

all: $(PROG)

$(PROG): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $(OBJ) $(LDFLAGS)

parser.tab.c parser.tab.h: parser.y
	$(YACC) parser.y

lex.yy.c: ej1.l
	$(LEX) ej1.l

# Reglas genéricas para compilar .c a .o
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) parser.tab.c parser.tab.h lex.yy.c $(PROG)
