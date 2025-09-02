CC = gcc
CFLAGS = -g -Wall -I./AST -I./tabla_simbolos -I./utils
LEX = flex
YACC = bison -d
LDFLAGS = -lfl

# Fuentes
SRC = parser.tab.c lex.yy.c AST/ast.c tabla_simbolos/tabla_simbolos.c interprete.c
OBJ = $(SRC:.c=.o)

# Ejecutables
PROG = programa

all: $(INTERPRETE) $(GENERADOR) run_gen_code

$(INTERPRETE): $(COMMON_OBJ) $(INTERPRETE_OBJ)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

$(GENERADOR): $(COMMON_OBJ) $(GENERADOR_OBJ) 
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

run_gen_code: $(GENERADOR) $(PROGRAMA_SRC)
	./$(GENERADOR) $(PROGRAMA_SRC) $(GENERADOR_OUT)

parser.tab.c parser.tab.h: parser.y
	$(YACC) parser.y

lex.yy.c: lexer.l
	$(LEX) lexer.l

# Reglas genéricas para compilar .c a .o
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(COMMON_OBJ) $(INTERPRETE_OBJ) $(GENERADOR_OBJ) parser.tab.c parser.tab.h lex.yy.c $(INTERPRETE) $(GENERADOR) $(GENERADOR_OUT)