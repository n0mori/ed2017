#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "modules/geo/geo.h"
#include "modules/nick_string/nick_string.h"

int busca_id(void **elementos, int n, int buscado) {
  int i, id_atual;
  int *p;
  for (i = 0; i < n; i++) {
    if (elementos[i] == NULL) {
      break;
    }
    p = (int*) elementos[i];
    id_atual = *p;
    if (id_atual == buscado) {
      return i;
    }
  }
  return -1;
}

void limpa_vetor(void **elementos, char *tipos, int n) {
  int i;
  for (i = 0; i < n; i++) {
    if (elementos[i] != NULL) {
      free(elementos[i]);
      tipos[i] = 0;
    }
  }
}

int main(int argc, char *argv[]) {
  int i, j, k, d, n, id;
  n = -1;
  double x, y, raio, height, width;
  char *filein, *buffer, cor[100];
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
  if (n < 0) {
    puts("Digite o valor de n no argumento -n!");
    exit(0);
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
  FILE *fsvg = fopen(saida_svg, "w");
  fprintf(fsvg, "<svg xmlns=\"http://www.w3.org/2000/svg\">\n");
  FILE *ftxt = fopen(saida_txt, "w");
  while (!feof(in)) {
    buffer = le_linha(in);
    circ *aux_circ;
    rect *aux_rect;
    switch (buffer[0]) {
      case 'c':
        sscanf(buffer, "c %d %lf %lf %lf %s", &id, &raio, &x, &y, cor);
        elementos[i] = new_circ(id, raio, x, y, cor);
        aux_circ = (circ*) elementos[i];
        fprintf(fsvg, "<circle cx=\"%lf\" cy=\"%lf\" r=\"%lf\" fill=\"%s\"/>\n", aux_circ->x, aux_circ->y, aux_circ->raio, aux_circ->cor);
        tipos[i] = 'c';
        i++;
        break;
      case 'r':
        sscanf(buffer, "r %d %lf %lf %lf %lf %s", &id, &width, &height, &x, &y, cor);
        elementos[i] = new_rect(id, width, height, x, y, cor);
        aux_rect = (rect*) elementos[i];
        fprintf(fsvg, "<rect x=\"%lf\" y=\"%lf\" width=\"%lf\" height=\"%lf\" fill=\"%s\"/>\n", aux_rect->x, aux_rect->y, aux_rect->width, aux_rect->height, aux_rect->cor);
        tipos[i] = 'r';
        i++;
        break;
      case 'o':
        sscanf(buffer, "o %d %d", &j, &k);
        fputs(buffer, ftxt);
        int id_1, id_2, bool_inter;
        bool_inter = 0;
        double extremidades[4];
        id_1 = busca_id(elementos, n, j);
        id_2 = busca_id(elementos, n, k);
        if (tipos[id_1] == 'c' && tipos[id_2] == 'c') {
          circ *a, *b;
          a = elementos[id_1];
          b = elementos[id_2];
          if (intersec_cc(*a, *b) == 1) {
            /* up, left, down, right */
            extremidades_cc(*a, *b, extremidades);
            bool_inter = 1;
          }
        } else if (tipos[id_1] == 'r' && tipos[id_2] == 'r') {

        }
        if (bool_inter) {
          fputs("sim", ftxt);
          fputc('\n', ftxt);
          fprintf(fsvg, "<rect x=\"%lf\" y=\"%lf\" width=\"%lf\" height=\"%lf\" fill=\"none\" style=\"stroke:pink;stroke-width:3;stroke-dasharray:5,5;z-index:1000\"/>\n", extremidades[1], extremidades[0], extremidades[3] - extremidades[1], extremidades[2] - extremidades[0]);
          fprintf(fsvg, "<text x=\"%lf\" y=\"%lf\" fill=\"red\" font-size=\"16\" style=\"z-index:100\">sobrepoe</text>\n", extremidades[1], extremidades[0] + 16);
        } else {
          fputs("nao", ftxt);
          fputc('\n', ftxt);
        }
        break;
      case 'i':
        sscanf(buffer, "i %d %lf %lf", &d, &x, &y);
        id = busca_id(elementos, n, d);
        fputs(buffer, ftxt);
        if (id == -1) {
          puts("nao existe item com esse id");
          break;
        }
        if (tipos[id] == 'c') {
          aux_circ = elementos[id];
          if (circ_interno(*aux_circ, x, y) == 1) {
            fputs("sim\n", ftxt);
          } else {
            fputs("nao\n", ftxt);
          }
        } else if (tipos[id] == 'r') {
          aux_rect = elementos[id];
          if (rect_interno(*aux_rect, x, y) == 1) {
            fputs("sim\n", ftxt);
          } else {
            fputs("nao\n", ftxt);
          }
        } else {
          printf("%c\n", tipos[id]);
        }
        break;
      case 'd':
        break;
      case 'a':
        break;
    }

    free(buffer);
  }
  fclose(in);
  fclose(ftxt);
  fprintf(fsvg, "</svg>");
  fclose(fsvg);

  limpa_vetor(elementos, tipos, n);

  free(dir);
  free(nome);
  free(saida_txt);
  free(saida_svg);

  return 0;
}
