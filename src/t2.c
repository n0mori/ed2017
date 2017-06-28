#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "modules/nick_string/nick_string.h"
#include "modules/svg/svg.h"

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
  double x, y, raio, height, width;
  char *filein, *buffer, cor[100], sufixo[MAX_BUFFER], *nome_sufixo;
  char *dir = alloc_inicial();
  char *nome = alloc_inicial();
  char *saida_txt;
  char *saida_svg;
  void **elementos;
  char *tipos;
  FILE *in, *fsvg, *ftxt, *fa;
  n = -1;

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

  elementos = malloc(sizeof(void*) * (n+1));
  tipos = malloc(sizeof(char) * (n+1));
  for (i = 0; i < n; i++) {
    elementos[i] = NULL;
    tipos[n] = 0;
  }

  if (dir[strlen(dir) - 1] != '/') {
    dir = concatena(dir, "/");
  }

  if (last_slash(filein) == NULL) {
    nome = concatena(nome, filein);
  } else {
    nome = concatena(nome, last_slash(filein));
  }
  nome[strlen(nome) - 4] = 0;

  saida_txt = monta_arquivo(dir, nome, "txt");
  saida_svg = monta_arquivo(dir, nome, "svg");

  i = 0;
  in = fopen(filein, "r");
  fsvg = fopen(saida_svg, "w");
  fprintf(fsvg, "<svg xmlns=\"http://www.w3.org/2000/svg\">\n");
  ftxt = fopen(saida_txt, "w");
  while (!feof(in)) {
    buffer = le_linha(in);
    switch (buffer[0]) {
      int id_1, id_2, bool_inter;
      double extremidades[4];
      case 'c':
        if (i >= n) {
          puts("voce excedeu o numero de elementos");
          break;
        }
        sscanf(buffer, "c %d %lf %lf %lf %s", &id, &raio, &x, &y, cor);
        elementos[i] = new_circ(id, raio, x, y, cor);
        tipos[i] = 'c';
        print_svg_circ(fsvg, (circ*) elementos[i]);
        i++;
        break;
      case 'r':
        if (i >= n) {
          puts("voce excedeu o numero de elementos");
          break;
        }
        sscanf(buffer, "r %d %lf %lf %lf %lf %s", &id, &width, &height, &x, &y, cor);
        elementos[i] = new_rect(id, width, height, x, y, cor);
        print_svg_rect(fsvg, (rect*) elementos[i]);
        tipos[i] = 'r';
        i++;
        break;
      case 'o':
        sscanf(buffer, "o %d %d", &j, &k);
        fputs(buffer, ftxt);
        bool_inter = 0;
        id_1 = busca_id(elementos, n, j);
        id_2 = busca_id(elementos, n, k);
        if (id_1 < 0 || id_2 < 0) {
          fputs("id invalido\n", ftxt);
          break;
        }
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
          rect *a, *b;
          a = elementos[id_1];
          b = elementos[id_2];
          if (intersec_rr(*a, *b) == 1) {
            extremidades_rr(*a, *b, extremidades);
            bool_inter = 1;
          }
        }
        if (bool_inter) {
          fputs("sim", ftxt);
          fputc('\n', ftxt);
          print_sobreposto(fsvg, extremidades);
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
          circ *aux_circ = (circ*) elementos[id];
          if (circ_interno(*aux_circ, x, y) == 1) {
            fputs("sim\n", ftxt);
          } else {
            fputs("nao\n", ftxt);
          }
        } else if (tipos[id] == 'r') {
          rect *aux_rect = (rect*) elementos[id];
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
        sscanf(buffer, "o %d %d", &j, &k);
        fputs(buffer, ftxt);
        bool_inter = 0;
        id_1 = busca_id(elementos, n, j);
        id_2 = busca_id(elementos, n, k);
        if (id_1 < 0 || id_2 < 0) {
          fputs("id invalido\n", ftxt);
          break;
        }
        if (tipos[id_1] == tipos[id_2]) {
          double distancia = 0;
          if (tipos[id_1] == 'c') {
            circ *a, *b;
            a = (circ*) elementos[id_1];
            b = (circ*) elementos[id_2];
            distancia = dist(a->x, a->y, b->x, b->y);
          }
          if (tipos[id_1] == 'r') {
            rect *a, *b;
            a = (rect*) elementos[id_1];
            b = (rect*) elementos[id_2];
            distancia = dist(a->x + a->width / 2.0, a->y + a->height / 2.0, b->x + b->width / 2.0, b->y + b->height / 2.0);
          }
          fprintf(ftxt, "%lf\n", distancia);
        } else {
          circ *c;
          rect *r;
          if (tipos[id_1] == 'c') {
            c = (circ*) elementos[id_1];
            r = (rect*) elementos[id_2];
          } else {
            r = (rect*) elementos[id_1];
            c = (circ*) elementos[id_2];
          }
          fprintf(ftxt, "%lf\n", dist(c->x, c->y, r->x + r->width / 2.0, r->y + r->height / 2.0));
        }
        break;
      case 'a':
        sscanf(buffer, "a %[^ ] %s", sufixo, cor);
        nome_sufixo = alloc_inicial();
        nome_sufixo = concatena(nome_sufixo, dir);
        nome_sufixo = concatena(nome_sufixo, nome);
        nome_sufixo = concatena(nome_sufixo, "-");
        nome_sufixo = concatena(nome_sufixo, sufixo);
        nome_sufixo = concatena(nome_sufixo, ".svg");
        fa = fopen(nome_sufixo, "w");
        fprintf(fa, "<svg xmlns=\"http://www.w3.org/2000/svg\">\n");
        for (id = 0; id < i; id++) {
          if (tipos[id] == 'c') {
            circ *c = (circ*) elementos[id];
            print_circ_points(fa, c, cor);
          } else if (tipos[id] == 'r') {
            rect *r = (rect*) elementos[id];
            print_rect_points(fa, r, cor);
          }
        }
        fprintf(fa, "</svg>\n");
        fclose(fa);
        free(nome_sufixo);
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
  free(elementos);
  free(tipos);

  return 0;
}
