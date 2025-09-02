#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../AST/ast.h"
#include "../tabla_simbolos/tabla_simbolos.h"
#include "../parser.tab.h"
extern FILE *yyin;

void gen_code(Arbol *ast, FILE *file, Tipo_Info context)
{
    if (!ast)
        return;
    char s[128];
    switch (ast->tipo_info)
    {
    case PROGRAMA:
        fputs("section .data\n", file);
        gen_code(ast->izq, file, DECLARACIONES);
        fputs("section .text\nglobal _main\n   _main:\n", file);
        gen_code(ast->der, file, SENTENCIAS);
        break;

    case DECLARACIONES:
        gen_code(ast->izq, file, DECLARACIONES);
        gen_code(ast->der, file, DECLARACIONES);
        break;
    case DECLARACION:
        gen_code(ast->izq, file, DECLARACIONES);
        break;

    case SENTENCIAS:
        gen_code(ast->izq, file, SENTENCIAS);
        gen_code(ast->der, file, SENTENCIAS);
        break;

    case ASIGNACION:
        if (ast->der->tipo_info == OPERADOR_INFO)
        {
            gen_code(ast->der, file, SENTENCIAS);
        }
        strcpy(s, "MOV ");
        strcat(s, ast->izq->info->id.nombre);
        strcat(s, ", ");
        fwrite(s, sizeof(char), strlen(s), file);
        if (ast->der->tipo_info == LITERAL_INFO || ast->der->tipo_info == ID_INFO)
        {
            gen_code(ast->der, file, SENTENCIAS);
        }
        else
        {
            fputs("eax", file);
        }
        fwrite("\n", sizeof(char), 1, file);
        break;

    case ID_INFO:
    {
        if (context == DECLARACIONES)
        {

            if (ast->info->id.valor)
            {
                snprintf(s, sizeof(s), "%s dw %d\n",
                         ast->info->id.nombre,
                         *(int *)ast->info->id.valor);
            }
            else
            {
                snprintf(s, sizeof(s), "%s resdw 10\n", ast->info->id.nombre);
            }
            fwrite(s, sizeof(char), strlen(s), file);
        }
        else
        {
            fputs(ast->info->id.nombre, file);
        }
        break;
    }
    case LITERAL_INFO:
        if (ast->info->literal.tipo == ENTERO)
        {
            snprintf(s, sizeof(s), "%d", *(int *)ast->info->literal.valor);
        }
        else
        {
            snprintf(s, sizeof(s), "%d", *(bool *)ast->info->literal.valor);
        }
        fwrite(s, sizeof(char), strlen(s), file);
        break;
    case OPERADOR_INFO: // Se asume que todas las operaciones guardan su resultado en eax.
        char op[2];
        strcpy(op, (ast->info->operador.nombre));
        if (strcmp(op, "+") == 0)
        {
            fputs("ADD ", file);
            gen_code(ast->izq, file, SENTENCIAS);
            fputs(", ", file);
            gen_code(ast->der, file, SENTENCIAS);
            fputs("\n", file);
        }
        else if (strcmp(op, "*") == 0)
        {
            fputs("MUL ", file);
            gen_code(ast->izq, file, SENTENCIAS);
            fputs(", ", file);
            gen_code(ast->der, file, SENTENCIAS);
            fputs("\n", file);
        }
        else if (strcmp(op, "&&") == 0)
        {
            fputs("TEST ", file);
            gen_code(ast->izq, file, SENTENCIAS);
            fputs(", ", file);
            gen_code(ast->izq, file, SENTENCIAS);
            fputs("\n", file);
            fputs("SETNE al\n", file);

            fputs("TEST ", file);
            gen_code(ast->der, file, SENTENCIAS);
            fputs(", ", file);
            gen_code(ast->der, file, SENTENCIAS);
            fputs("\n", file);
            fputs("SETNE bl\n", file);
            fputs("AND al, bl\n", file);
            fputs("MOVZX eax, al\n", file);
        }
        else if (strcmp(op, "||") == 0)
        {
            fputs("TEST ", file);
            gen_code(ast->izq, file, SENTENCIAS);
            fputs(", ", file);
            gen_code(ast->izq, file, SENTENCIAS);
            fputs("\n", file);
            fputs("SETNE al\n", file);

            fputs("TEST ", file);
            gen_code(ast->der, file, SENTENCIAS);
            fputs(", ", file);
            gen_code(ast->der, file, SENTENCIAS);
            fputs("\n", file);
            fputs("SETNE bl \nOR al, bl \nMOVZX eax, al\n", file);
        }
        else if (strcmp(op, "==") == 0)
        {
            fputs("CMP ", file);
            gen_code(ast->izq, file, SENTENCIAS);
            fputs(", ", file);
            gen_code(ast->der, file, SENTENCIAS);
            fputs("\nSETZ al \nMOVZX eax, al\nMOV z, eax\n", file);
            
        }
        else if (strcmp(op, "!") == 0)
        {
            fputs("TEST ", file);
            gen_code(ast->izq, file, SENTENCIAS);
            fputs(", ", file);
            gen_code(ast->izq, file, SENTENCIAS);
            fputs("\n", file);
            fputs("SETZ al \nMOVZX eax, al\n", file);
        }
        break;
    default:
        break;
    }
}

int main(int argc, char **argv)
{
    if (argc > 2)
    {
        FILE *archivo = fopen(argv[1], "r");
        if (!archivo)
        {
            perror("No se pudo abrir el archivo");
            return 1;
        }
        yyin = archivo; // importante: yyin es global de Flex
    }

    Arbol *arbol = NULL;

    if (yyparse(&arbol) != 0)
    {
        fprintf(stderr, "Error en el parseo.\n");
        return 1;
    }

    Simbolo *tabla = crearTabla();
    analisisSemantico(arbol, tabla);
    FILE *assembly = fopen(argv[2], "w+");
    if (!assembly)
    {
        perror("No se pudo abrir el archivo para generar el código.");
        return 1;
    }
    gen_code(arbol, assembly, PROGRAMA);

    if (argc > 2)
    {
        fclose(yyin);
        fclose(assembly);
    }

    return 0;
}
