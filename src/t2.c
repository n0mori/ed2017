#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "modules/ListaEstatica/ListaEstatica.h"
#include "modules/Nick_string/Nick_string.h"
#include "modules/svg/svg.h"

int main(int argc, char *argv[]) {
  int i, j, k, d, n, id;
  double raio, height, width;
  char *filein, buffer[MAX_BUFFER], cor[100], sufixo[MAX_BUFFER], *nome_sufixo;
  char *dir = alloc_inicial();
  char *nome = alloc_inicial();
  char *saida_txt;
  char *saida_svg;
  ListaEstatica elementos;
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
  elementos = cria_lista_estatica(n);

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
    fgets(buffer, MAX_BUFFER, in);
    switch (buffer[0]) {
      int bool_inter;
      double x, y;
      Elemento *a, *b;
      double extremidades[4];
      case 'c':
        if (i >= n) {
          puts("voce excedeu o numero de elementos");
          break;
        }
        sscanf(buffer, "c %d %lf %lf %lf %s", &id, &raio, &x, &y, cor);
        adiciona_lista_estatica(elementos, i, novo_elemento(id, 'c', new_circ(raio, x, y, cor)));
        print_svg_circ(fsvg, (Circ*) get_elemento_dado(elementos[i]));
        i++;
        break;
      case 'r':
        if (i >= n) {
          puts("voce excedeu o numero de elementos");
          break;
        }
        sscanf(buffer, "r %d %lf %lf %lf %lf %s", &id, &width, &height, &x, &y, cor);
        adiciona_lista_estatica(elementos, i, novo_elemento(id, 'r', new_rect(width, height, x, y, cor)));
        print_svg_rect(fsvg, (Rect*) get_elemento_dado(elementos[i]));
        i++;
        break;
      case 'o':
        sscanf(buffer, "o %d %d", &j, &k);
        fputs(buffer, ftxt);
        bool_inter = 0;
        a = busca_id(elementos, n, j);
        b = busca_id(elementos, n, k);
        if (a == NULL || b == NULL) {
          fputs("id invalido\n", ftxt);
          break;
        }
        if (get_elemento_tipo(*a) == 'c' && get_elemento_tipo(*b) == 'c') {
          Circ *c1, *c2;
          c1 = (Circ*) get_elemento_dado(*a);
          c2 = (Circ*) get_elemento_dado(*b);
          if (intersec_cc(*c1, *c2) == 1) {
            /* up, left, down, right */
            extremidades_cc(*c1, *c2, extremidades);
            bool_inter = 1;
          }
        } else if (get_elemento_tipo(*a) == 'r' && get_elemento_tipo(*b) == 'r') {
          Rect *r1, *r2;
          r1 = (Rect*) get_elemento_dado(*a);
          r2 = (Rect*) get_elemento_dado(*b);
          if (intersec_rr(*r1, *r2) == 1) {
            extremidades_rr(*r1, *r2, extremidades);
            bool_inter = 1;
          }
        } else if ((get_elemento_tipo(*a) == 'c' && get_elemento_tipo(*b) == 'r') || (get_elemento_tipo(*a) == 'r' && get_elemento_tipo(*b) == 'c')) {
          Circ *c;
          Rect *r;
          if (get_elemento_tipo(*a) == 'c') {
            c = (Circ*) get_elemento_dado(*a);
            r = (Rect*) get_elemento_dado(*b);
          } else {
            r = (Rect*) get_elemento_dado(*a);
            c = (Circ*) get_elemento_dado(*b);
          }
          if (intersec_cr(*c, *r) == 1) {
            extremidades_cr(*c, *r, extremidades);
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
        fputs(buffer, ftxt);
        a = busca_id(elementos, n, d);
        if (a == NULL) {
          puts("nao existe item com esse id");
          break;
        }
        /*printf("a:%d b_a:%d\n", a->id, d);*/
        if (get_elemento_tipo(*a) == 'c') {
          Circ *aux_circ = (Circ*) get_elemento_dado(*a);
          bool_inter = circ_interno(*aux_circ, x, y);
          if (bool_inter == 1) {
            fputs("sim\n", ftxt);
          } else {
            fputs("nao\n", ftxt);
          }
        } else if (get_elemento_tipo(*a) == 'r') {
          Rect *aux_rect = (Rect*) get_elemento_dado(*a);
          if (rect_interno(*aux_rect, x, y)) {
            fputs("sim\n", ftxt);
          } else {
            fputs("nao\n", ftxt);
          }
        } else {
          printf("%c\n", get_elemento_tipo(*a));
        }
        break;
      case 'd':
        sscanf(buffer, "d %d %d", &j, &k);
        fputs(buffer, ftxt);
        a = busca_id(elementos, n, j);
        b = busca_id(elementos, n, k);
        if (a == NULL || b == NULL) {
          fputs("id invalido\n", ftxt);
          break;
        }
        if (get_elemento_tipo(*a) == get_elemento_tipo(*b)) {
          double dist = 0;
          if (get_elemento_tipo(*a) == 'c') {
            Circ *c1, *c2;
            c1 = (Circ*) get_elemento_dado(*a);
            c2 = (Circ*) get_elemento_dado(*b);
            dist = distancia(c1->x, c1->y, c2->x, c2->y);
          }
          if (get_elemento_tipo(*a) == 'r') {
            Rect *r1, *r2;
            r1 = (Rect*) get_elemento_dado(*a);
            r2 = (Rect*) get_elemento_dado(*b);
            dist = distancia(r1->x + r1->width / 2.0, r1->y + r1->height / 2.0, r2->x + r2->width / 2.0, r2->y + r2->height / 2.0);
          }
          fprintf(ftxt, "%lf\n", dist);
        } else {
          Circ *c;
          Rect *r;
          if (get_elemento_tipo(*a) == 'c') {
            c = (Circ*) get_elemento_dado(*a);
            r = (Rect*) get_elemento_dado(*b);
          } else {
            r = (Rect*) get_elemento_dado(*a);
            c = (Circ*) get_elemento_dado(*b);
          }
          fprintf(ftxt, "%lf\n", distancia(c->x, c->y, r->x + r->width / 2.0, r->y + r->height / 2.0));
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
          if (elementos[id].tipo == 'c') {
            Circ *c = (Circ*) elementos[id].dado;
            print_circ_points(fa, c, cor);
          } else if (elementos[id].tipo == 'r') {
            Rect *r = (Rect*) elementos[id].dado;
            print_rect_points(fa, r, cor);
          }
        }
        fprintf(fa, "</svg>\n");
        fclose(fa);
        free(nome_sufixo);
        break;
      default:
        break;
    }
    buffer[0] = 0;
  }
  fclose(in);
  fclose(ftxt);
  fprintf(fsvg, "</svg>");
  fclose(fsvg);

  limpa_vetor(elementos, n);

  free(dir);
  free(nome);
  free(saida_txt);
  free(saida_svg);
  free(elementos);

  return 0;
}
