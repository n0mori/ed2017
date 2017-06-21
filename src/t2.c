#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "modules/coord/coord.h"
#include "modules/circ/circ.h"
#include "modules/rect/rect.h"
#include "modules/nick_string/nick_string.h"

int main(int argc, char *argv[]) {
  int i, n;
  n = 0;
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

  if (strlen(filein) == 0) {
    puts("Digite o arquivo de entrada no argumento -f!");
    exit(1);
  }
  if (strlen(dir) == 0) {
    puts("Digite o diretorio no argumento -o!");
    exit(1);
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
  //FILE *ftxt = fopen(saida_txt, "w");
  while (!feof(in)) {
    buffer = le_linha(in);
    circ *aux_circ;
    rect *aux_rect;
    switch (buffer[0]) {
      case 'c':
        aux_circ = alloc_circ();
        sscanf(buffer, "c %d %lf %lf %lf %s", &(aux_circ->id), &(aux_circ->raio), &(aux_circ->ancora.x), &(aux_circ->ancora.y), aux_circ->cor);
        elementos[i] = aux_circ;
        tipos[i] = 'c';
        i++;
        break;
      case 'r':
        aux_rect = alloc_rect();
        sscanf(buffer, "r %d %lf %lf %lf %lf %s", &(aux_rect->id), &(aux_rect->width), &(aux_rect->height), &(aux_rect->ancora.x), &(aux_rect->ancora.y), aux_rect->cor);
        elementos[i] = aux_rect;
        tipos[i] = 'r';
        i++;
        break;
      case 'o':
        break;
      case 'i':
        break;
      case 'd':
        break;
      case 'a':
        break;
    }

    free(buffer);
  }
  fclose(in);

  FILE *fsvg = fopen(saida_svg, "w");
  fprintf(fsvg, "<svg xmlns=\"http://www.w3.org/2000/svg\">\n");
  for (i = 0; i < n; i++) {
    if (tipos[i] == 0) {
      break;
    } else if (tipos[i] == 'c') {
      circ *c = (circ*) elementos[i];
      fprintf(fsvg, "<circle cx=\"%lf\" cy=\"%lf\" r=\"%lf\" fill=\"%s\"/>\n", c->ancora.x, c->ancora.y, c->raio, c->cor);
    } else if (tipos[i] == 'r') {
      rect *r = (rect*) elementos[i];
      fprintf(fsvg, "<rect x=\"%lf\" y=\"%lf\" width=\"%lf\" height=\"%lf\" fill=\"%s\"/>\n", r->ancora.x, r->ancora.y, r->width, r->height, r->cor);
    }
  }
  fprintf(fsvg, "</svg>");
  fclose(fsvg);

  for (i = 0; i < n; i++) {
    if (tipos[i]) {
      free(elementos[i]);
      tipos[i] = 0;
    }
  }

  free(dir);
  free(nome);
  free(saida_txt);
  free(saida_svg);

  return 0;
}
