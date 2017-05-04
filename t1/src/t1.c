#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#ifndef MAX_BUFFER
#define MAX_BUFFER 80
#endif

char *le_linha(FILE *f);
int interpreta(char *str);
char *pega_string(char *str);
char *concatena(char *inicio, char *fim);
char *alloc_inicial();
char *limpa(char *x);
char *substitui_str(char *str, char *new) {
  free(str);
  str = malloc(sizeof(char) * (strlen(new) + 1));
  strcpy(str, new);
  return str;
}

char *limpa(char *str) {
  free(str);
  return alloc_inicial();
}

char *alloc_inicial() {
  char *str = malloc(sizeof(char));
  *str = 0;
  return str;
}

char *concatena(char *inicio, char *fim) {
  inicio = (char *) realloc(inicio, sizeof(char) * (strlen(inicio) + strlen(fim) + 1));
  inicio = strcat(inicio, fim);
  return inicio;
}

char *pega_string(char *str) {
  char *buffer = malloc(MAX_BUFFER * sizeof(char));
  sscanf(str, "%*c%*c\"%[^\"]", buffer);
  return buffer;
}

int interpreta(char *str) {
  //retorna a opcao
  switch (str[0]) {
    case 'x':
      return 1;
      break;
    case 'y':
      return 2;
      break;
    case 'z':
      return 3;
      break;
    case 'l':
      switch (str[1]) {
        case 'x':
          return 4;
          break;
        case 'y':
          return 5;
          break;
        case 'z':
          return 6;
          break;
      }
      break;
    case 'd':
      return 7;
      break;
    case 'a':
      return 8;
      break;
    case 'e':
      return 9;
      break;
    case 'o':
      return 10;
      break;
    case 'w':
      return 11;
      break;
    case 'f':
      return 12;
      break;
    default:
      return 0;
  }
}

char *le_linha(FILE *f) {
  char *str = malloc(MAX_BUFFER * sizeof(char));
  fgets(str, MAX_BUFFER, f);
  return str;
}

int main(int argc, char *argv[]) {
  if (argc < 5) {
    printf("como executar: t1 -f arquivo -o dir\n");
    return 0;
  }

  char *x, *y, *z, *f, *dir, *a, *e, *buffer, *str;
  x = alloc_inicial();
  y = alloc_inicial();
  z = alloc_inicial();
  a = alloc_inicial();
  e = alloc_inicial();
  dir = malloc(sizeof(char) * (strlen(argv[4])) + 1);
  f = argv[2];

  FILE *file = fopen(f, "r");
  while (!feof(file)) {
    buffer = le_linha(file);
    int comando = interpreta(buffer);

    if (comando) {
      switch (comando) {
        case 1:
          str = pega_string(buffer);
          x = concatena(x, str);
          free(str);
          break;
        case 2:
          str = pega_string(buffer);
          y = concatena(y, str);
          free(str);
          break;
        case 3:
          str = pega_string(buffer);
          z = concatena(z, str);
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
          if (buffer[2] == '"') {
            str = pega_string(buffer);
            dir = substitui_str(dir, str);
            free(str);
          } else if (buffer[2] == '#') {
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
          break;
        case 11:
          break;
        case 12:
          break;
      }
    }
    free(buffer);
  }
  fclose(file);

  puts(x);
  puts(y);
  puts(z);
  printf("%s%s.%s", dir, a, e);
  return 0;
}
