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
  int i, acc0, acc, ins, cpi, del, cpd, bool_qry, bool_f, bool_convex, bool_ec, bool_pm, bool_tm;
  char *bsd = alloc_inicial();
  char *bed = alloc_inicial();
  char *geo_name, *full_name, buffer[MAX_BUFFER], *txt, *svg, *res, *geo_saida, *qry_name, *ec_name, *pm_name, *tm_name;
  char cfq[100], csq[100], cfh[100], csh[100], cfs[100], css[100], cft[100], cst[100];
  char *geo = alloc_inicial();
  char *qry = alloc_inicial();
  char *ec = alloc_inicial();
  char *tm = alloc_inicial();
  char *pm = alloc_inicial();
  FILE *in, *file_txt, *file_qry, *file_svg, *file_ec, *file_pm, *file_tm;
  Cidade city = new_cidade();

  acc0 = 0;
  acc = 0;
  ins = 0;
  cpi = 0;
  del = 0;
  cpd = 0;
  bool_qry = 0;
  bool_f = 0;
  bool_ec = 0;
  bool_pm = 0;
  bool_tm = 0;
  bool_convex = 1;
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
    } else if (!strcmp("-ec", argv[i])) {
      ec_name = argv[++i];
      bool_ec = 1;
    } else if (!strcmp("-pm", argv[i])) {
      pm_name = argv[++i];
      bool_pm = 1;
    } else if (!strcmp("-tm", argv[i])) {
      tm_name = argv[++i];
      bool_tm = 1;
    } else if (!strcmp("-id", argv[i])) {
      puts("Nicolas Jashchenko Omori - 201600560295");
    } else if (!strcmp("-noconvex", argv[i])) {
      bool_convex = 0;
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
    retira_extensao(geo_saida);
  }
  if (bool_ec) {
    ec = concatena(ec, ec_name);
    retira_path(ec);
    geo_saida = concatena(geo_saida, "-");
    geo_saida = concatena(geo_saida, ec);
    retira_extensao(geo_saida);
  }
  if (bool_pm) {
    pm = concatena(pm, pm_name);
    retira_path(pm);
    geo_saida = concatena(geo_saida, "-");
    geo_saida = concatena(geo_saida, pm);
    retira_extensao(geo_saida);
  }
  if (bool_tm) {
    tm = concatena(tm, tm_name);
    retira_path(tm);
    geo_saida = concatena(geo_saida, "-");
    geo_saida = concatena(geo_saida, tm);
    retira_extensao(geo_saida);
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
      ej = search_forma_lista(city, id_j);
      ek = search_forma_lista(city, id_k);
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
      e = search_forma_lista(city, id);
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
      ej = search_forma_lista(city, id_j);
      ek = search_forma_lista(city, id_k);
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
      for (n = get_first(city.lista_formas); n != NULL; n = get_next(city.lista_formas, n)) {
        Elemento *e = get(city.lista_formas, n);
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
      Quadra q;
      sscanf(buffer, "q %lf %lf %lf %lf %s", &x, &y, &width, &height, cep);
      q = new_quadra(x, y, width, height, cep, cfq, csq);
      insere_quadra(city, q, &cpi, &ins);
      hash_insert(city.cep_quadra, cep, q);
    } else if (buffer[0] == 'h' && buffer[1] == ' ') {
      char id[100];
      double x, y;
      sscanf(buffer, "h %lf %lf %s", &x, &y, id);
      insere_hidrante(city, new_hidrante(x, y, id, cfh, csh));
    } else if (buffer[0] == 'h' && buffer[1] == 'I') {
      char id[100];
      double vazao;
      Hidrante h;
      sscanf(buffer, "hI %[^ ] %lf", id, &vazao);
      h = search_lista(city.lista_hidrantes, cmp_hidrante_string, id);
      if (h != NULL) {
        hidrante_set_vazao(h, vazao);
      }
    } else if (buffer[0] == 's' && buffer[1] == ' ') {
      char id[100];
      double x, y;
      sscanf(buffer, "s %lf %lf %s", &x, &y, id);
      insere_semaforo(city, new_semaforo(x, y, id, cfs, css));
    } else if (buffer[0] == 's' && buffer[1] == 'I') {
      char id[100];
      double ciclo;
      Semaforo s;
      sscanf(buffer, "sI %[^ ] %lf", id, &ciclo);
      s = search_lista(city.lista_semaforos, cmp_semaforo_string, id);
      if (s != NULL) {
        semaforo_set_ciclo(s, ciclo);
      }
    } else if (buffer[0] == 't' && buffer[1] == ' ') {
      char id[100];
      double x, y;
      sscanf(buffer, "t %lf %lf %s", &x, &y, id);
      insere_torre(city, new_torre(x, y, id, cft, cst));
    } else if (buffer[0] == 't' && buffer[1] == 'I') {
      char id[100];
      double range;
      Torre t;
      sscanf(buffer, "tI %[^ ] %lf", id, &range);
      t = search_lista(city.lista_torres, cmp_torre_string, id);
      if (t != NULL) {
        torre_set_range(t, range);
      }
    } else if (buffer[0] == 'c' && buffer[1] == 'q') {
      sscanf(buffer, "cq %[^ ] %s", cfq, csq);
    } else if (buffer[0] == 'c' && buffer[1] == 'h') {
      sscanf(buffer, "ch %[^ ] %s", cfh, csh);
    } else if (buffer[0] == 'c' && buffer[1] == 's') {
      sscanf(buffer, "cs %[^ ] %s", cfs, css);
    } else if (buffer[0] == 'c' && buffer[1] == 't') {
      sscanf(buffer, "ct %[^ ] %s", cft, cst);
    } else if (buffer[0] == 's' && buffer[1] == 'u') {
      char id[100];
      Torre t;
      sscanf(buffer, "su %s", id);
      t = search_lista(city.lista_torres, cmp_torre_string, id);
      if (t != NULL) {
        torre_set_operadora(t, 's');
      }
    } else if (buffer[0] == 'u' && buffer[1] == 'm') {
      char id[100];
      Torre t;
      sscanf(buffer, "um %s", id);
      t = search_lista(city.lista_torres, cmp_torre_string, id);
      if (t != NULL) {
        torre_set_operadora(t, 'u');
      }
    }
    buffer[0] = 0;
  }
  fclose(in);
  free(full_name);

  if (bool_ec) {
    full_name = alloc_inicial();
    full_name = concatena(full_name, bed);
    full_name = concatena(full_name, ec_name);
    file_ec = fopen(full_name, "r");
    if (file_ec == NULL) {
      puts("Não consegui encontrar o arquivo ec! Saindo...");
      exit(1);
    }

    while (!feof(file_ec)) {
      fgets(buffer, MAX_BUFFER, file_ec);
      if (buffer[0] == 't') {
        char codt[100], descricao[100];
        char *desc = alloc_inicial();
        sscanf(buffer, "t %s %[^\r\n]", codt, descricao);
        desc = concatena(desc, descricao);
        hash_insert(city.tipo_comercio, codt, desc);
      } else if (buffer[0] == 'e') {
        char codt[100], cep[100], face, nome[100], cnpj[100];
        int numero;
        Comercio c;
        sscanf(buffer, "e %[^ ] %[^ ] %c %d %[^ ] %[^\r\n]", codt, cep, &face, &numero, cnpj, nome);
        c = new_comercio(codt, cep, face, numero, cnpj, nome);
        hash_insert(city.estabelecimentos, cnpj, c);
      }
      buffer[0] = 0;
    }
    fclose(file_ec);
  }

  if (bool_pm) {
    full_name = alloc_inicial();
    full_name = concatena(full_name, bed);
    full_name = concatena(full_name, pm_name);
    file_pm = fopen(full_name, "r");
    if (file_pm == NULL) {
      puts("Não consegui encontrar o arquivo pm! Saindo...");
      exit(1);
    }

    while (!feof(file_pm)) {
      fgets(buffer, MAX_BUFFER, file_pm);

      if (buffer[0] == 'p') {
        char cpf[100], nome[100], sobrenome[100], sexo, nasc[100];
        Pessoa p;
        sscanf(buffer, "p %[^ ] %[^ ] %[^ ] %c %[^\r\n]", cpf, nome, sobrenome, &sexo, nasc);
        p = new_pessoa(cpf, nome, sobrenome, sexo, nasc);
        hash_insert(city.pessoas, cpf, p);
      } else if (buffer[0] == 'm') {
        char cpf[100], cep[100], face, complemento[100];
        int numero;
        Morador m;
        sscanf(buffer, "m %[^ ] %[^ ] %c %d %[^\r\n]", cpf, cep, &face, &numero, complemento);
        m = new_morador(cpf, cep, face, numero, complemento);
        hash_insert(city.moradores, cpf, m);
      }     

      buffer[0] = 0;
    }
    fclose(file_pm);
  }

  if (bool_tm) {
    full_name = alloc_inicial();
    full_name = concatena(full_name, bed);
    full_name = concatena(full_name, tm_name);
    file_tm = fopen(full_name, "r");
    if (file_tm == NULL) {
      puts("Não consegui encontrar o arquivo tm! Saindo...");
      exit(1);
    }

    while (!feof(file_tm)) {
      char cpf[100], numcel[100];
      Celular c;
      fgets(buffer, MAX_BUFFER, file_tm);

      if (buffer[0] == 's' && buffer[1] == 'u') {
        char *pessoa = alloc_inicial();
        sscanf(buffer, "su %[^ ] %s", cpf, numcel);
        concatena(pessoa, cpf);
        c = new_celular(cpf, numcel, 's');
        hash_insert(city.sercomtuel, numcel, c);
        hash_insert(city.numcel_pessoa, numcel, pessoa);
        pessoa_set_celular(hash_get(city.pessoas, cpf), c);
      } else if (buffer[0] == 'u' && buffer[1] == 'm') {
        char *pessoa = alloc_inicial();
        sscanf(buffer, "um %[^ ] %s", cpf, numcel);
        concatena(pessoa, cpf);
        c = new_celular(cpf, numcel, 'u');
        hash_insert(city.uelmobile, numcel, c);
        hash_insert(city.numcel_pessoa, numcel, pessoa);
        pessoa_set_celular(hash_get(city.pessoas, cpf), c);
      }

      buffer[0] = 0;
    }
    fclose(file_tm);
  }

  if (bool_convex) {
    Pilha stk_quadras = new_pilha();
    Pilha stk_hidrantes = new_pilha();
    Pilha stk_semaforos = new_pilha();
    Pilha stk_torres = new_pilha();
    Pilha stk_formas = new_pilha();

    while (length_lista(city.lista_formas) > 0) {
      convex_hull(city.lista_formas, stk_formas, elemento_get_x, elemento_get_y, cmp_elemento_elemento_y0, cmp_elemento_elemento_x0);
    }
    while (!empty(stk_formas)) {
      Elemento *e = pop(stk_formas);
      quadtree_insert(city.qt_formas, e, elemento_get_x(e), elemento_get_y(e));
    }
    free(stk_formas);

    while(length_lista(city.lista_quadras) > 0) {
      convex_hull(city.lista_quadras, stk_quadras, quadra_get_x, quadra_get_y, cmp_quadra_quadra_y0, cmp_quadra_quadra_x0);
    }
    while(!empty(stk_quadras)) {
      Quadra q = pop(stk_quadras);
      quadtree_insert(city.qt_quadras, q, quadra_get_x(q), quadra_get_y(q));
    }
    free(stk_quadras);

    while(length_lista(city.lista_hidrantes) > 0) {
      convex_hull(city.lista_hidrantes, stk_hidrantes, hidrante_get_x, hidrante_get_y, cmp_hidrante_hidrante_y0, cmp_hidrante_hidrante_x0);
    }
    while(!empty(stk_hidrantes)) {
      Hidrante h = pop(stk_hidrantes);
      quadtree_insert(city.qt_hidrantes, h, hidrante_get_x(h), hidrante_get_y(h));
    }
    free(stk_hidrantes);

    while(length_lista(city.lista_semaforos) > 0) {
      convex_hull(city.lista_semaforos, stk_semaforos, semaforo_get_x, semaforo_get_y, cmp_semaforo_semaforo_y0, cmp_semaforo_semaforo_x0);
    }
    while(!empty(stk_semaforos)) {
      Semaforo s = pop(stk_semaforos);
      quadtree_insert(city.qt_semaforos, s, semaforo_get_x(s), semaforo_get_y(s));
    }
    free(stk_semaforos);

    while(length_lista(city.lista_torres) > 0) {
      convex_hull(city.lista_torres, stk_torres, torre_get_x, torre_get_y, cmp_torre_torre_y0, cmp_torre_torre_x0);
    }
    while(!empty(stk_torres)) {
      Torre t = pop(stk_torres);
      quadtree_insert(city.qt_torres, t, torre_get_x(t), torre_get_y(t));
    }
    free(stk_torres);
  } else {

    while (length_lista(city.lista_formas) > 0) {
      Elemento *e = remove_first(city.lista_formas);
      quadtree_insert(city.qt_formas, e, elemento_get_x(e), elemento_get_y(e));
    }

    while (length_lista(city.lista_quadras) > 0) {
      Quadra q = remove_first(city.lista_quadras);
      quadtree_insert(city.qt_quadras, q, quadra_get_x(q), quadra_get_y(q));
    }

    while (length_lista(city.lista_hidrantes) > 0) {
      Hidrante h = remove_first(city.lista_hidrantes);
      quadtree_insert(city.qt_hidrantes, h, hidrante_get_x(h), hidrante_get_y(h));
    }

    while (length_lista(city.lista_semaforos) > 0) {
      Semaforo s = remove_first(city.lista_semaforos);
      quadtree_insert(city.qt_semaforos, s, semaforo_get_x(s), semaforo_get_x(s));
    }

    while (length_lista(city.lista_torres) > 0) {
      Torre t = remove_first(city.lista_torres);
      quadtree_insert(city.qt_torres, t, torre_get_x(t), semaforo_get_y(t));
    }
  }


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
      if (buffer[0] == 'd' 
          && (buffer[1] == 'q'
          || buffer[1] == 'h' 
          || buffer[1] == 's'
          || buffer[1] == 't' )) {
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
      } else if (buffer[0] == 'c' && buffer[1] == 'r' && buffer[2] == 'd' && buffer[3] == '?') {
        char id[100];
        sscanf(buffer, "crd? %s", id);
        file_txt = fopen(txt, "a+");
        fputs(buffer, file_txt);
        search_cep_or_id(city, file_txt, id);
        fclose(file_txt);
      } else if (buffer[0] == 'p' && buffer[1] == 'c' && buffer[2] == '?') {
        FILE *pc_svg;
        char sufixo[100], str_x[100], str_y[100], str_width[100], str_height[100];
        char *str_pc = alloc_inicial();
        double x, y, width, height;
        Lista *towers = create_lista();
        Lista *pts = create_lista();
        Pilha stk_pts = new_pilha();
        Node *n;
        sufixo[0] = 0;
        str_x[0] = 0;
        str_y[0] = 0;
        str_width[0] = 0;
        str_height[0] = 0;

        sscanf(buffer, "pc? %s %s %s %s %s", sufixo, str_x, str_y, str_width, str_height);

        str_pc = concatena(str_pc, bsd);
        str_pc = concatena(str_pc, geo_saida);
        retira_extensao(str_pc);
        str_pc = concatena(str_pc, "-");
        str_pc = concatena(str_pc, sufixo);
        str_pc = concatena(str_pc, ".svg");
        pc_svg = fopen(str_pc, "w+");

        if (pc_svg == NULL) {
          puts("Não consegui criar o arquivo! Verificar casos de testes e diretórios");
          exit(1);
        }

        if (strlen(str_x) > 0) {
          Rect *r;
          sscanf(str_x, "%lf", &x);
          sscanf(str_y, "%lf", &y);
          sscanf(str_width, "%lf", &width);
          sscanf(str_height, "%lf", &height);
          r = new_rect(width, height, x, y, "");
          quadtree_filter_to_list(quadtree_root(city.qt_torres), towers, torre_inside_rect, r);
          free(r);
        } else {
          quadtree_filter_to_list(quadtree_root(city.qt_torres), towers, cmp_true, NULL);
        }

        for (n = get_first(towers); n != NULL; n = get_next(towers, n)) {
          torre_range_pontos(get(towers, n), pts);
        }

        convex_hull(pts, stk_pts, get_x, get_y, cmp_ponto_y0, cmp_ponto_x0);

        fprintf(pc_svg, "<svg xmlns=\"http://www.w3.org/2000/svg\">\n");
        quadtree_percorre_print(quadtree_root(city.qt_quadras), pc_svg, print_svg_quadra);
        quadtree_percorre_print(quadtree_root(city.qt_hidrantes), pc_svg, print_svg_hidrante);
        quadtree_percorre_print(quadtree_root(city.qt_semaforos), pc_svg, print_svg_semaforo);
        quadtree_percorre_print(quadtree_root(city.qt_torres), pc_svg, print_svg_torre);
        quadtree_percorre_print(quadtree_root(city.qt_torres), pc_svg, print_svg_torre_range);
        quadtree_percorre_print(quadtree_root(city.qt_formas), pc_svg, print_svg_elemento);
        print_svg_point_stack(pc_svg, stk_pts);
        fprintf(pc_svg, "</svg>");

        fclose(pc_svg);
        free(str_pc);
        free_lista(pts);
        free(stk_pts);
        while (length_lista(towers) > 0) {
          remove_first(towers);
        }
        free(towers);

      } else if (buffer[0] == 'a' && buffer[1] == 'c' && buffer[2] == '?') {
        char str_x[100], str_y[100], str_width[100], str_height[100];
        double x, y, width, height;
        Lista *towers = create_lista();
        Lista *pts = create_lista();
        Pilha stk_pts = new_pilha();
        Node *n;
        str_x[0] = 0;
        str_y[0] = 0;
        str_width[0] = 0;
        str_height[0] = 0;

        sscanf(buffer, "ac? %s %s %s %s", str_x, str_y, str_width, str_height);

        if (strlen(str_x) > 0) {
          Rect *r;
          sscanf(str_x, "%lf", &x);
          sscanf(str_y, "%lf", &y);
          sscanf(str_width, "%lf", &width);
          sscanf(str_height, "%lf", &height);
          r = new_rect(width, height, x, y, "");
          quadtree_filter_to_list(quadtree_root(city.qt_torres), towers, torre_inside_rect, r);
          free(r);
        } else {
          quadtree_filter_to_list(quadtree_root(city.qt_torres), towers, cmp_true, NULL);
        }

        for (n = get_first(towers); n != NULL; n = get_next(towers, n)) {
          torre_range_pontos(get(towers, n), pts);
        }

        convex_hull(pts, stk_pts, get_x, get_y, cmp_ponto_y0, cmp_ponto_x0);



        file_txt = fopen(txt, "a+");
        fputs(buffer, file_txt);
        fprintf(file_txt, "%f metros\n", area_pilha_pontos(stk_pts));
        fclose(file_txt);

        free_lista(pts);
        free(stk_pts);
        while (length_lista(towers) > 0) {
          remove_first(towers);
        }
        free(towers);
      } else if (buffer[0] == 'm' && buffer[1] == 'v') {
        Celular origem, destino;
        char opdest, numero[100];
        Pessoa pessoa;
        sscanf(buffer, "mv %c %s", &opdest, numero);
        if (opdest == 's') {
          origem = hash_delete(city.uelmobile, numero);
          destino = hash_get(city.sercomtuel, numero);
        } else if (opdest == 'u') {
          origem = hash_delete(city.sercomtuel, numero);
          destino = hash_get(city.uelmobile, numero);
        }

        file_txt = fopen(txt, "a+");
        fputs(buffer, file_txt);
        if (origem == NULL || destino != NULL) {
          fputs("Erro, numero inexistente na operadora de origem ou existente na operadora destino\n", file_txt);
          fclose(file_txt);
          buffer[0] = 0;
          continue;
        }

        pessoa = hash_get(city.numcel_pessoa, pessoa);
        celular_set_operadora(origem, opdest);
        fprintf(file_txt, "Celular %s pertencente a %s, migrou de ", celular_get_numero(origem), pessoa_get_nome(pessoa));
        
        if (opdest == 's') {
          hash_insert(city.sercomtuel, numero, origem);
          fputs("Sercomtuel para UELMobile.\n", file_txt);
        } else if (opdest == 'u') {
          hash_insert(city.uelmobile, numero, origem);
          fputs("UELMobile para Sercomtuel.\n", file_txt);
        }

        /* TODO: reconectar se o celular estiver conectado */

        fclose(file_txt);
      } else if (buffer[0] == 'm' && buffer[1] == '?') {
        Lista moradores = create_lista();
        Node n;
        char cep[100];
        
        sscanf(buffer, "m? %s", cep);

        hash_filter(city.moradores, moradores, cmp_morador_cep, cep);

        file_txt = fopen(txt, "a+");
        fputs(buffer, file_txt);

        if (length_lista(moradores) == 0) {
          fputs("não existem moradores nesse bairro\n", file_txt);
        }

        for (n = get_first(moradores); n != NULL; n = get_next(moradores, n)) {
          Morador m = get(moradores, n);
          morador_imprime_dados(m, hash_get(city.pessoas, morador_get_cpf(m)), file_txt);
        }

        while (length_lista(moradores) > 0) {
          remove_first(moradores);
        }
        free(moradores);

        fclose(file_txt);

      } else if (buffer[0] == 'm' && buffer[1] == 'r' && buffer[2] == '?') {
        Lista quadras = create_lista();
        Node n;
        double x, y, width, height;
        Rect *r;

        sscanf(buffer, "mr? %lf %lf %lf %lf", &x, &y, &width, &height);
        r = new_rect(width, height, x, y, "");

        quadtree_filter_to_list(quadtree_root(city.qt_quadras), quadras, quadra_inside_rect, r);

        file_txt = fopen(txt, "a+");
        fputs(buffer, file_txt);
        
        if (length_lista(quadras) == 0) {
          fputs("não existem quadras nessa região\n", file_txt);
        }

        for (n = get_first(quadras); n != NULL; n = get_next(quadras, n)) {
          Lista moradores = create_lista();
          Node no;
          hash_filter(city.moradores, moradores, cmp_morador_cep, quadra_get_cep(get(quadras, n)));

          for (no = get_first(moradores); no != NULL; no = get_next(moradores, no)) {
            Morador m = get(moradores, no);
            morador_imprime_dados(m, hash_get(city.pessoas, morador_get_cpf(m)), file_txt);
          }

          while (length_lista(moradores) > 0) {
            remove_first(moradores);
          }
          free(moradores);
        }

        while (length_lista(quadras) > 0) {
          remove_first(quadras);
        }
        free(quadras);

        fclose(file_txt);

      } else if (buffer[0] == 'd' && buffer[1] == 'm' && buffer[2] == '?') {
        char cpf[100];
        Morador m;
        Ponto p;
        
        sscanf(buffer, "dm? %s", cpf);

        m = hash_get(city.moradores, cpf);

        file_txt = fopen(txt, "a+");
        fputs(buffer, file_txt);

        if (m == NULL) {
          fputs("não existe morador com esse cpf!\n", file_txt);
          buffer[0] = 0;
          fclose(file_txt);
          continue;
        }

        insert_last(city.printable_people, m);
        morador_imprime_dados(m, hash_get(city.pessoas, cpf), file_txt);
        p = cidade_get_ponto_address(city, morador_get_address(m));

        fprintf(file_txt, "%f %f\n", get_x(p), get_y(p));

        fclose(file_txt);
        free(p);
      } else if (buffer[0] == 'd' && buffer[1] == 'e' && buffer[2] == '?') {
        char cnpj[100];
        Comercio c;
        Ponto p;
        
        sscanf(buffer, "de? %s", cnpj);

        c = hash_get(city.estabelecimentos, cnpj);
        
        file_txt = fopen(txt, "a+");
        fputs(buffer, file_txt);

        if (c == NULL) {
          fputs("não existe estabelecimento com esse cnpj!\n", file_txt);
          buffer[0] = 0;
          fclose(file_txt);
          continue;
        }

        insert_last(city.printable_comercios, c);
        fprintf(file_txt, "%s - %s\n", comercio_get_nome(c), (char*) hash_get(city.tipo_comercio, comercio_get_codt(c)));
        p = cidade_get_ponto_address(city, comercio_get_address(c));

        fprintf(file_txt, "%f %f\n", get_x(p), get_y(p));
        
        fclose(file_txt);

      } else if (buffer[0] == 'c' && buffer[1] == 'o' && buffer[2] == 'n') {
      } else if (buffer[0] == 'm' && buffer[1] == 's' && buffer[2] == 'e') {
        Lista quadras = create_lista();
        Node n;
        char sexo, tipo[100];
        double x, y, width, height;
        Rect *r;

        sscanf(buffer, "mr? %c %s %lf %lf %lf %lf", &sexo, tipo, &x, &y, &width, &height);
        r = new_rect(width, height, x, y, "");

        quadtree_filter_to_list(quadtree_root(city.qt_quadras), quadras, quadra_inside_rect, r);


        file_txt = fopen(txt, "a+");
        fputs(buffer, file_txt);
        
        if (length_lista(quadras) == 0) {
          fputs("não existem quadras nessa região\n", file_txt);
        }

        for (n = get_first(quadras); n != NULL; n = get_next(quadras, n)) {
          Lista stabs = create_lista();
          Comercio q;
          hash_filter(city.estabelecimentos, stabs, cmp_comercio_codt, tipo);
          q = search_lista(stabs, cmp_comercio_cep, quadra_get_cep(get(quadras, n)));

          if (q != NULL) {
            Lista moradores = create_lista();
            Node no;
            hash_filter(city.moradores, moradores, cmp_morador_cep, quadra_get_cep(get(quadras, n)));

            for (no = get_first(moradores); no != NULL; no = get_next(moradores, no)) {
              Morador m = get(moradores, no);
              if (pessoa_get_sexo(hash_get(city.pessoas, morador_get_cpf(m))) == sexo) {
                morador_imprime_dados(m, hash_get(city.pessoas, morador_get_cpf(m)), file_txt);
              }
            }

            while (length_lista(moradores) > 0) {
              remove_first(moradores);
            }
            free(moradores);
          }

          while (length_lista(stabs) > 0) {
            remove_first(stabs);
          }
          free(stabs);
        }

        while (length_lista(quadras) > 0) {
          remove_first(quadras);
        }
        free(quadras);

        fclose(file_txt);

      } else if (buffer[0] == 'r' && buffer[1] == 'i' && buffer[2] == 'p') {
      } else if (buffer[0] == 'l' && buffer[1] == 'k' && buffer[2] == '?') {
      } else if (buffer[0] == 'r' && buffer[1] == 'b' && buffer[2] == '?') {
      } else if (buffer[0] == 'c' && buffer[1] == 'o' && buffer[2] == '?') {
      } else if (buffer[0] == 'l' && buffer[1] == 'n' && buffer[2] == 'r') {
      } else if (buffer[0] == 'e' && buffer[1] == 'c' && buffer[2] == 'q') {
      } else if (buffer[0] == 'e' && buffer[1] == 'c' && buffer[2] == 'r') {
      } else if (buffer[0] == 't' && buffer[1] == 'e' && buffer[2] == 'c' && buffer[3] == 'q') {
      } else if (buffer[0] == 't' && buffer[1] == 'e' && buffer[2] == 'c' && buffer[3] == 'r') {
      } else if (buffer[0] == 'd' && buffer[1] == 'c' && buffer[2] == '?') {
      } else if (buffer[0] == 'l' && buffer[1] == 'e' && buffer[2] == 'c') {
      } else if (buffer[0] == 'l' && buffer[1] == 'c' && buffer[2] == 'c') {
      } else if (buffer[0] == 'd' && buffer[1] == 'p' && buffer[2] == 'r') {
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
  free(ec);

  return 0;
}
