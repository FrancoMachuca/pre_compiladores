CC = gcc
CFLAGS = -g -Wall -I./AST -I./tabla_simbolos -I./utils
LEX = flex
YACC = bison -d
LDFLAGS = -lfl

# -------------------------
# Fuentes comunes
COMMON_SRC = parser.tab.c lex.yy.c \
             AST/ast.c \
             tabla_simbolos/tabla_simbolos.c \
             utils/helpers.c \
			 errores.c \
			 semantico.c
COMMON_OBJ = $(COMMON_SRC:.c=.o)

# -------------------------
# Intérprete
INTERPRETE_SRC = interprete.c
INTERPRETE_OBJ = $(INTERPRETE_SRC:.c=.o)
INTERPRETE = interprete

# -------------------------
# Generador
GENERADOR_SRC = utils/gen_code.c
GENERADOR_OBJ = $(GENERADOR_SRC:.c=.o)
GENERADOR = generador

# -------------------------
# Archivos
PROGRAMA_SRC = programa.txt   
GENERADOR_OUT = programa.asm       

# -------------------------
# Targets principales
all: $(INTERPRETE) $(GENERADOR)

$(INTERPRETE): $(COMMON_OBJ) $(INTERPRETE_OBJ)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

$(GENERADOR): $(COMMON_OBJ) $(GENERADOR_OBJ)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

# Ejecutar generador con un programa de prueba
run_interprete: $(INTERPRETE) 
	./$(INTERPRETE) $(PROGRAMA_SRC)

run_gen_code: $(GENERADOR) $(PROGRAMA_SRC)
	./$(GENERADOR) $(PROGRAMA_SRC) $(GENERADOR_OUT)

# -------------------------
# Reglas para parser y lexer
parser.tab.c parser.tab.h: parser.y
	$(YACC) parser.y

lex.yy.c: lexer.l
	$(LEX) lexer.l

# -------------------------
# Regla genérica para .o
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# -------------------------
clean:
	rm -f $(COMMON_OBJ) $(INTERPRETE_OBJ) $(GENERADOR_OBJ) \
	      parser.tab.c parser.tab.h lex.yy.c \
	      $(INTERPRETE) $(GENERADOR) $(GENERADOR_OUT)
