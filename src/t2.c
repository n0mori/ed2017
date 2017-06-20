#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "modules/coord/coord.h"
#include "modules/circ/circ.h"
#include "modules/rect/rect.h"
#include "modules/nick_string/nick_string.h"

int main(int argc, char *argv[]) {
  int i, n;
  char *filein, *buffer;
  char *dir = alloc_inicial();
  char *nome = alloc_inicial();
  char *saida_txt = alloc_inicial();
  char *saida_svg = alloc_inicial();

  for (i = 0; i < argc; i++) {
    if (!strcmp("-f", argv[i])) {
      filein = argv[++i];
    } else if (!strcmp("-o", argv[i])) {
      dir = concatena(dir, argv[++i]);
    } else if (!strcmp("-n", argv[i])) {
      n = atoi(argv[++i]);
    }
  }

  void *elementos[n];
  char tipos[n];
  for (i = 0; i < n; i++) {
    elementos[i] = NULL;
    tipos[n] = 0;
  }

  if (dir[strlen(dir) - 1] != '/') {
    dir = concatena(dir, "/");
  }

  nome = concatena(nome, filein);
  nome[strlen(nome) - 4] = 0;

  saida_txt = concatena(saida_txt, dir);
  saida_txt = concatena(saida_txt, nome);
  saida_txt = concatena(saida_txt, ".txt");
  saida_svg = concatena(saida_svg, dir);
  saida_svg = concatena(saida_svg, nome);
  saida_svg = concatena(saida_svg, ".svg");

  i = 0;
  FILE *in = fopen(filein, "r");
  while (!feof(in)) {
    buffer = le_linha(in);
    circ *aux_circ;
    switch (buffer[0]) {
      case 'c':
        aux_circ = alloc_circ();
        sscanf(buffer, "c %d %lf %lf %lf %s", &(aux_circ->id), &(aux_circ->raio), &(aux_circ->ancora.x), &(aux_circ->ancora.y), aux_circ->cor);
        elementos[i] = aux_circ;
        tipos[i] = 'c';
        i++;
        break;
    }

    free(buffer);
  }

  FILE *fsvg = fopen(saida_svg, "w");
  fprintf(fsvg, "<svg xmlns=\"http://www.w3.org/2000/svg\">\n");
  for (i = 0; i < n; i++) {
    if (tipos[i] == 0) {
      break;
    } else if (tipos[i] == 'c') {
      circ *c = ((circ*) elementos[i]);
      puts("imprimi");
      fprintf(fsvg, "<circle cx=\"%lf\" cy=\"%lf\" r=\"%lf\" fill=\"%s\"/>\n", c->ancora.x, c->ancora.y, c->raio, c->cor);
    }
  }
  fprintf(fsvg, "</svg>");
  fclose(fsvg);

  for (i = 0; i < n; i++) {
    if (tipos[i]) {
      free(elementos[i]);
      tipos[i] = 0;
    } else {
      break;
    }
  }
  printf("%s%s, n=%d\nnome=%s\nsaida_txt=%s\n", dir, filein, n, nome, saida_txt);

  free(dir);
  free(nome);
  free(saida_txt);
  free(saida_svg);

  return 0;
}
