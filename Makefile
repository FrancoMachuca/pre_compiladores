CC = gcc
CFLAGS = -g -Wall
LEX = flex
YACC = bison -d
LDFLAGS = -lfl

# Fuentes comunes
COMMON_SRC = parser.tab.c lex.yy.c AST/ast.c tabla_simbolos/tabla_simbolos.c
COMMON_OBJ = $(COMMON_SRC:.c=.o)

# Archivos específicos
INTERPRETE_SRC = interprete.c
GENERADOR_SRC = utils/gen_code.c
PROGRAMA_SRC = programa.txt

INTERPRETE_OBJ = $(INTERPRETE_SRC:.c=.o)
GENERADOR_OBJ = $(GENERADOR_SRC:.c=.o)

# Salida del generador
GENERADOR_OUT = assembly.asm

# Ejecutables
INTERPRETE = interprete
GENERADOR = gen_code

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