#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#ifndef MAX_BUFFER
#define MAX_BUFFER 80
#endif

char *le_linha(FILE *f, char *str);
int interpreta(char *str);

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
    default:
      return 0;
  }
}

char *le_linha(FILE *f, char *str) {
  str = malloc(MAX_BUFFER * sizeof(char));
  fgets(str, MAX_BUFFER, f);
  return str;
}

int main(int argc, char *argv[]) {
  if (argc < 5) {
    printf("como executar: t1 -f arquivo -o dir\n");
    return 0;
  }

  char *x, *y, *z, *f, *dir, *a, *e, *buffer;
  f = argv[2];

  FILE *file = fopen(f, "r");
  while (!feof(file)) {
    buffer = le_linha(file, buffer);
    int comando = interpreta(buffer);
    //interpretar
    if (comando) {
      printf("%d - ", comando);
    }
    printf("%s", buffer);
    free(buffer);
  }
  fclose(file);

  return 0;
}
