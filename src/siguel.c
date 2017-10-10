#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "modules/Cidade/Cidade.h"
#include "modules/svg/svg.h"
#include "modules/Nick_string/Nick_string.h"
#include "modules/Elemento/Elemento.h"
#include "modules/Sorting/Sorting.h"
#include "modules/Comparacao/Comparacao.h"
#include "modules/Convex/Convex.h"
#include "modules/Quadtree/Quadtree.h"

int main(int argc, char *argv[]) {
  int i, acc0, acc, ins, cpi, del, cpd, bool_qry, bool_f;
  char *bsd = alloc_inicial();
  char *bed = alloc_inicial();
  char *geo_name, *full_name, buffer[MAX_BUFFER], *txt, *svg, *res, *geo_saida, *qry_name;
  char cfq[100], csq[100], cfh[100], csh[100], cfs[100], css[100], cft[100], cst[100];
  char *geo = alloc_inicial();
  char *qry = alloc_inicial();
  FILE *in, *file_txt, *file_qry, *file_svg;
  Cidade city = new_cidade();

  acc0 = 0;
  acc = 0;
  ins = 0;
  cpi = 0;
  del = 0;
  cpd = 0;
  bool_qry = 0;
  bool_f = 0;
  sprintf(cfq, "white");
  sprintf(csq, "black");
  sprintf(cfh, "white");
  sprintf(csh, "black");
  sprintf(cfs, "white");
  sprintf(css, "black");
  sprintf(cft, "white");
  sprintf(cst, "black");


  for (i = 0; i < argc; i++) {
    if (!strcmp("-f", argv[i])) {
      geo_name = argv[++i];
      bool_f = 1;
    } else if (!strcmp("-o", argv[i])) {
      bsd = concatena(bsd, argv[++i]);
    } else if (!strcmp("-e", argv[i])) {
      bed = concatena(bed, argv[++i]);
    } else if (!strcmp("-acc0", argv[i])) {
      acc0 = 1;
    } else if (!strcmp("-acc", argv[i])) {
      acc = 1;
    } else if (!strcmp("-q", argv[i])) {
      qry_name = argv[++i];
      bool_qry = 1;
    } else if (!strcmp("-id", argv[i])) {
      puts("Nicolas Jashchenko Omori - 201600560295");
    }
  }

  if (!bool_f) {
    puts("Digite o arquivo de entrada no argumento -f!");
    exit(1);
  }
  if (strlen(bsd) == 0) {
    puts("Digite o diretorio no argumento -o!");
    exit(1);
  }
  if (strlen(bed) != 0) {
    bed = arruma_dir(bed);
  }

  bsd = arruma_dir(bsd);
  geo = concatena(geo, geo_name);
  retira_extensao(geo);
  geo_saida = alloc_inicial();
  geo_saida = concatena(geo_saida, geo);
  if (bool_qry) {
    qry = concatena(qry, qry_name);
    retira_path(qry);
    geo_saida = concatena(geo_saida, "-");
    geo_saida = concatena(geo_saida, qry);
  }

  /*
  O próximo loop irá interpretar todos os comandos do arquivo geo, salvando os
  elementos na lista e já escrevendo os resultados de operações requisitadas no
  arquivo de saída .txt
  */

  full_name = monta_arquivo(bed, geo, "geo");
  txt = monta_arquivo(bsd, geo_saida, "txt");
  in = fopen(full_name, "r");
  file_txt = fopen(txt, "a+");
  if (in == NULL) {
    puts("Não consegui encontrar o arquivo geo! Saindo...");
    exit(1);
  }
  if (file_txt == NULL) {
    puts("Não consegui criar o arquivo de saída txt. Saindo...");
    exit(1);
  }
  fclose(file_txt);
  while (!feof(in)) {
    fgets(buffer, MAX_BUFFER, in);
    if (buffer[0] == 'c' && buffer[1] == ' ') {
      int id;
      double raio, x, y;
      char cor[100];
      sscanf(buffer, "c %d %lf %lf %lf %s", &id, &raio, &x, &y, cor);
      insere_forma(city, new_elemento(id, 'c', new_circ(raio, x, y, cor)));
    } else if (buffer[0] == 'r') {
      int id;
      double width, height, x, y;
      char cor[100];
      sscanf(buffer, "r %d %lf %lf %lf %lf %s", &id, &width, &height, &x, &y, cor);
      insere_forma(city, new_elemento(id, 'r', new_rect(width, height, x, y, cor)));
    } else if (buffer[0] == 'o') {
      int id_j, id_k, overlap;
      Elemento *ej, *ek;
      double extremidades[4];
      file_txt = fopen(txt, "a+");
      fputs(buffer, file_txt);
      sscanf(buffer, "o %d %d", &id_j, &id_k);
      ej = search_forma(city, id_j);
      ek = search_forma(city, id_k);
      if (ej == NULL || ek == NULL) {
        fputs("id invalido\n", file_txt);
      } else {
        overlap = 0;
        if (get_elemento_tipo(*ej) == 'c') {
          Circ *c1 = (Circ*) get_elemento_dado(*ej);
          if (get_elemento_tipo(*ek) == 'c') {
            Circ *c2 = (Circ*) get_elemento_dado(*ek);
            overlap = intersec_cc(*c1, *c2);
            extremidades_cc(*c1, *c2, extremidades);
          } else if (get_elemento_tipo(*ek) == 'r') {
            Rect *r1 = (Rect*) get_elemento_dado(*ek);
            overlap = intersec_cr(*c1, *r1);
            extremidades_cr(*c1, *r1, extremidades);
          }
        } else if (get_elemento_tipo(*ej) == 'r') {
          Rect *r1 = (Rect*) get_elemento_dado(*ej);
          if (get_elemento_tipo(*ek) == 'c') {
            Circ *c1 = (Circ*) get_elemento_dado(*ek);
            overlap = intersec_cr(*c1, *r1);
            extremidades_cr(*c1, *r1, extremidades);
          } else if (get_elemento_tipo(*ek) == 'r') {
            Rect *r2 = (Rect*) get_elemento_dado(*ek);
            overlap = intersec_rr(*r1, *r2);
            extremidades_rr(*r1, *r2, extremidades);
          }
        }
        if (overlap) {
          fputs("sim\n", file_txt);
          insere_forma(city, new_elemento(-1, 'e', new_rect(extremidades[3] - extremidades[1], extremidades[2] - extremidades[0], extremidades[1], extremidades[0], "")));
        } else {
          fputs("nao\n", file_txt);
        }
      }
      fclose(file_txt);
    } else if (buffer[0] == 'i') {
      int id;
      double x, y;
      Elemento *e;
      file_txt = fopen(txt, "a+");
      sscanf(buffer, "i %d %lf %lf", &id, &x, &y);
      fputs(buffer, file_txt);
      e = search_forma(city, id);
      if (e == NULL) {
        fputs("id nao encontrado!\n", file_txt);
      } else if (get_elemento_tipo(*e) == 'c') {
        Circ *c = (Circ*) get_elemento_dado(*e);
        if (circ_interno(*c, x, y)) {
          fputs("sim\n", file_txt);
        } else {
          fputs("nao\n", file_txt);
        }
      } else if (get_elemento_tipo(*e) == 'r') {
        Rect *r = (Rect*) get_elemento_dado(*e);
        if (rect_interno(*r, x, y)) {
          fputs("sim\n", file_txt);
        } else {
          fputs("nao\n", file_txt);
        }
      }
      fclose(file_txt);
    } else if (buffer[0] == 'd') {
      int id_j, id_k;
      double x, y, x0, y0;
      Elemento *ej, *ek;
      file_txt = fopen(txt, "a+");
      sscanf(buffer, "d %d %d", &id_j, &id_k);
      fputs(buffer, file_txt);
      ej = search_forma(city, id_j);
      ek = search_forma(city, id_k);
      if (ej == NULL || ek == NULL) {
        fputs("id invalido\n", file_txt);
      } else {
        if (get_elemento_tipo(*ej) == 'c') {
          Circ *c = (Circ*) get_elemento_dado(*ej);
          x = c->x;
          y = c->y;
        } else if (get_elemento_tipo(*ej) == 'r') {
          Rect *r = (Rect*) get_elemento_dado(*ej);
          x = r->x + r->width / 2;
          y = r->y + r->height / 2;
        }
        if (get_elemento_tipo(*ek) == 'c') {
          Circ *c = (Circ*) get_elemento_dado(*ek);
          x0 = c->x;
          y0 = c->y;
        } else if (get_elemento_tipo(*ek) == 'r') {
          Rect *r = (Rect*) get_elemento_dado(*ek);
          x0 = r->x + r->width / 2;
          y0 = r->y + r->height / 2;
        }
        fprintf(file_txt, "%f\n", distancia(x, y, x0, y0));
      }
      fclose(file_txt);
    } else if (buffer[0] == 'a') {
      char cor[100], sufixo[MAX_BUFFER], *nome_sufixo, *full_sufixo;
      Node *n;
      sscanf(buffer, "a %[^ ] %s", sufixo, cor);
      nome_sufixo = alloc_inicial();
      nome_sufixo = concatena(nome_sufixo, geo);
      nome_sufixo = concatena(nome_sufixo, "-");
      nome_sufixo = concatena(nome_sufixo, sufixo);
      full_sufixo = monta_arquivo(bsd, nome_sufixo, "svg");
      file_svg = fopen(full_sufixo, "w+");
      fprintf(file_svg, "<svg xmlns=\"http://www.w3.org/2000/svg\">\n");
      for (n = get_first(city.formas); n != NULL; n = get_next(city.formas, n)) {
        Elemento *e = get(city.formas, n);
        if (get_elemento_tipo(*e) == 'c') {
          Circ *c = (Circ*) get_elemento_dado(*e);
          print_circ_points(file_svg, c, cor);
        } else if (get_elemento_tipo(*e) == 'r') {
          Rect *r = (Rect*) get_elemento_dado(*e);
          print_rect_points(file_svg, r, cor);
        }
      }
      fprintf(file_svg, "</svg>");
      free(nome_sufixo);
      free(full_sufixo);
      fclose(file_svg);
    } else if (buffer[0] == 'q') {
      char cep[100];
      double x, y, width, height;
      sscanf(buffer, "q %lf %lf %lf %lf %s", &x, &y, &width, &height, cep);
      insere_quadra(city, new_quadra(x, y, width, height, cep, cfq, csq), &cpi, &ins);
    } else if (buffer[0] == 'h') {
      char id[100];
      double x, y;
      sscanf(buffer, "h %lf %lf %s", &x, &y, id);
      insere_hidrante(city, new_hidrante(x, y, id, cfh, csh));
    } else if (buffer[0] == 's') {
      char id[100];
      double x, y;
      sscanf(buffer, "s %lf %lf %s", &x, &y, id);
      insere_semaforo(city, new_semaforo(x, y, id, cfs, css));
    } else if (buffer[0] == 't') {
      char id[100];
      double x, y;
      sscanf(buffer, "t %lf %lf %s", &x, &y, id);
      insere_torre(city, new_torre(x, y, id, cft, cst));
    } else if (buffer[0] == 'c' && buffer[1] == 'q') {
      sscanf(buffer, "cq %[^ ] %s", cfq, csq);
    } else if (buffer[0] == 'c' && buffer[1] == 'h') {
      sscanf(buffer, "ch %[^ ] %s", cfh, csh);
    } else if (buffer[0] == 'c' && buffer[1] == 's') {
      sscanf(buffer, "cs %[^ ] %s", cfs, css);
    } else if (buffer[0] == 'c' && buffer[1] == 't') {
      sscanf(buffer, "ct %[^ ] %s", cft, cst);
    }
    buffer[0] = 0;
  }
  fclose(in);
  free(full_name);

  if (bool_qry) {
    full_name = alloc_inicial();
    full_name = concatena(full_name, bed);
    full_name = concatena(full_name, qry_name);
    file_qry = fopen(full_name, "r");
    if (file_qry == NULL) {
      puts("Não consegui encontrar o arquivo qry! Saindo...");
      exit(1);
    }

    while (!feof(file_qry)) {
      fgets(buffer, MAX_BUFFER, file_qry);
      if (buffer[0] == 'd') {
        Rect *r;
        double x, y, width, height;
        sscanf(buffer, "d%*c %lf %lf %lf %lf", &x, &y, &width, &height);
        r = new_rect(width, height, x, y, "");
        file_txt = fopen(txt, "a+");
        fputs(buffer, file_txt);
        if (buffer[1] == 'q') {
          remove_quadras_in_rect(city, file_txt, r, &cpd, &del);
        } else if (buffer[1] == 'h') {
          remove_hidrantes_in_rect(city, file_txt, r);
        } else if (buffer[1] == 's') {
          remove_semaforos_in_rect(city, file_txt, r);
        } else if (buffer[1] == 't') {
          remove_torres_in_rect(city, file_txt, r);
        }
        fclose(file_txt);
        free(r);
      } else if (buffer[0] == 'D') {
        Circ *ci;
        double x, y, raio;
        sscanf(buffer, "D%*c %lf %lf %lf", &x, &y, &raio);
        ci = new_circ(raio, x, y, "");
        file_txt = fopen(txt, "a+");
        fputs(buffer, file_txt);
        if (buffer[1] == 'q') {
          remove_quadras_in_circ(city, file_txt, ci, &cpd, &del);
        } else if (buffer[1] == 'h') {
          remove_hidrantes_in_circ(city, file_txt, ci);
        } else if (buffer[1] == 's') {
          remove_semaforos_in_circ(city, file_txt, ci);
        } else if (buffer[1] == 't') {
          remove_torres_in_circ(city, file_txt, ci);
        }
        fclose(file_txt);
        free(ci);
      } else if (buffer[0] == 'c') {
        char id[100];
        sscanf(buffer, "crd? %s", id);
        file_txt = fopen(txt, "a+");
        fputs(buffer, file_txt);
        search_cep_or_id(city, file_txt, id);
        fclose(file_txt);
      }
      buffer[0] = 0;
    }

    fclose(file_qry);
    free(full_name);
  }

  svg = monta_arquivo(bsd, geo_saida, "svg");
  print_svg_cidade(svg, city);


  res = monta_arquivo(bsd, "resumo", "txt");
  if (acc0) {
    FILE *file_res = fopen(res, "w+");
    geo_saida = concatena(geo_saida, ".geo");
  	fprintf(file_res, "%s\t%d\t%d\t%d\t%d\n", geo_name, cpi, ins, cpd, del);
    fclose(file_res);
  } else if (acc) {
    FILE *file_res = fopen(res, "a+");
    geo_saida = concatena(geo_saida, ".geo");
  	fprintf(file_res, "%s\t%d\t%d\t%d\t%d\n", geo_name, cpi, ins, cpd, del);
    fclose(file_res);
  }
  free(res);

  free_cidade(city);

  free(txt);
  free(svg);
  free(qry);
  free(geo);
  free(geo_saida);
  free(bsd);
  free(bed);

  return 0;
}
