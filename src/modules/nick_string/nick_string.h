#ifndef MAX_BUFFER
#define MAX_BUFFER 100000
#endif
#ifndef NICK_STRING__H
#define NICK_STRING__H value
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char *le_linha(FILE *f);
int interpreta(char *str);
char *pega_string(char *str);
char *concatena(char *inicio, char *fim);
char *alloc_inicial();
char *limpa(char *x);
char *substitui_str(char *str, char *new);
char *pega_path(char *str);
char *monta_arquivo(char *dir, char *a, char *e);
char *arruma_dir(char *dir);
char *verifica_quebras(char *str);

#endif
