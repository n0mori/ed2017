#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "nick_string.h"
#include "nick_string.c"

int main(int argc, char *argv[]) {
  char *x, *y, *z, *dir, *a, *e, *buffer, *str, *entrada;
  x = alloc_inicial();
  y = alloc_inicial();
  z = alloc_inicial();
  a = alloc_inicial();
  e = alloc_inicial();
  dir = NULL;
  entrada = NULL;

  int i = 1;
  while (i < argc) {
    if (!strcmp("-f", argv[i])) {
      i++;
      entrada = argv[i];
    } else if (!strcmp("-o", argv[i])) {
      i++;
      dir = malloc(sizeof(char) * (strlen(argv[i]) + 1));
      strcpy(dir, argv[i]);
    }
    i++;
  }

  if (entrada == NULL) {
    puts("Por favor escreva um arquivo de entrada após o -f ao executar o arquivo");
    return 0;
  }
  if (dir == NULL) {
    dir = alloc_inicial();
  }

  dir = arruma_dir(dir);

  FILE *f = NULL;
  FILE *file = fopen(entrada, "r");
  while (!feof(file)) {
    buffer = le_linha(file);
    int comando = interpreta_t1(buffer);
    if (comando) {
      switch (comando) {
        case 1:
          str = pega_string(buffer);
          x = concatena(x, str);
          //verifica_quebras(x);
          free(str);
          break;
        case 2:
          str = pega_string(buffer);
          y = concatena(y, str);
          //verifica_quebras(y);
          free(str);
          break;
        case 3:
          str = pega_string(buffer);
          z = concatena(z, str);
          //verifica_quebras(z);
          free(str);
          break;
        case 4:
          x = limpa(x);
          break;
        case 5:
          y = limpa(y);
          break;
        case 6:
          z = limpa(z);
          break;
        case 7:
          if (buffer[2] != '#') {
            str = pega_path(buffer);
            dir = substitui_str(dir, str);
            free(str);
          } else {
            switch (buffer[3]) {
              case 'x':
                dir = substitui_str(dir, x);
                break;
              case 'y':
                dir = substitui_str(dir, y);
                break;
              case 'z':
                dir = substitui_str(dir, z);
                break;
            }
          }
          dir = arruma_dir(dir);
          break;
        case 8:
          if (buffer[2] == '"') {
            str = pega_string(buffer);
            a = substitui_str(a, str);
            free(str);
          } else if (buffer[2] == '#') {
            switch (buffer[3]) {
              case 'x':
                a = substitui_str(a, x);
                break;
              case 'y':
                a = substitui_str(a, y);
                break;
              case 'z':
                a = substitui_str(a, z);
                break;
            }
          }
          break;
        case 9:
          if (buffer[2] == '"') {
            str = pega_string(buffer);
            e = substitui_str(e, str);
            free(str);
          } else if (buffer[2] == '#') {
            switch (buffer[3]) {
              case 'x':
                e = substitui_str(e, x);
                break;
              case 'y':
                e = substitui_str(e, y);
                break;
              case 'z':
                e = substitui_str(e, z);
                break;
            }
          }
          break;
        case 10:
          str = monta_arquivo(dir, a, e);
          if (f != NULL) {
            fclose(f);
          }
          f = fopen(str, "w+");
          free(str);
          break;
        case 11:
          str = monta_arquivo(dir, a, e);
          if (f != NULL) {
            fclose(f);
          }
          f = fopen(str, "a+");
          break;
        case 12:
          if (f != NULL) {
            if (buffer[2] != '#') {
              fputs(buffer + 2, f);
            } else {
              switch (buffer[3]) {
                case 'x':
                  fputs(x, f);
                  break;
                case 'y':
                  fputs(y, f);
                  break;
                case 'z':
                  fputs(z, f);
                  break;
              }
            }
          } else {
            puts("Erro! Não há nenhum arquivo aberto!");
          }
          break;
        case 13:
          if (f != NULL) fclose(f);
          f = NULL;
          break;
      }
    }
    str = alloc_inicial();
    free(buffer);
  }
  if (f != NULL) {
    fclose(f);
  }
  fclose(file);

  /* para debug:
  puts(x);
  puts(y);
  puts(z);
  puts(dir);
  puts(monta_arquivo(dir, a, e));
  */
  return 0;
}
