#include <stdio.h>
#include <stdlib.h>
#include "modules/Cidade/Cidade.h"
#include "modules/svg/svg.h"
#include "modules/Nick_string/Nick_string.h"
#include "modules/Elemento/Elemento.h"

int main(int argc, char *argv[]) {
  int i, acc0, acc, ins, cpi, del, cpd;
  char *bsd = alloc_inicial();
  char *bed = alloc_inicial();
  char *geo_name, *full_name, buffer[MAX_BUFFER], *txt, *svg;
  char cfq[100], csq[100], cfh[100], csh[100], cfs[100], css[100], cft[100], cst[100];
  char *geo = alloc_inicial();
  char *qry = alloc_inicial();
  FILE *in, *file_txt, *file_qry, *file_svg;
  Cidade city = new_cidade();
  Node *no;

  acc0 = 0;
  acc = 0;
  ins = 0;
  cpi = 0;
  del = 0;
  cpd = 0;
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
    } else if (!strcmp("-o", argv[i])) {
      bsd = concatena(bsd, argv[++i]);
    } else if (!strcmp("-e", argv[i])) {
      bed = concatena(bed, argv[++i]);
    } else if (!strcmp("-acc0", argv[i])) {
      acc0 = 0;
    } else if (!strcmp("-acc", argv[i])) {
      acc = 0;
    } else if (!strcmp("-q", argv[i])) {
      qry = concatena(qry, argv[++i]);
    }
  }

  if (strlen(geo_name) == 0) {
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

  /*
  O próximo loop irá interpretar todos os comandos do arquivo geo, salvando os
  elementos na lista e já escrevendo os resultados de operações requisitadas no
  arquivo de saída .txt
  */

  full_name = monta_arquivo(bed, geo, "geo");
  txt = monta_arquivo(bsd, geo, "txt");
  in = fopen(full_name, "r");
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

    } else if (buffer[0] == 'i') {

    } else if (buffer[0] == 'd') {

    } else if (buffer[0] == 'a') {

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

  svg = monta_arquivo(bsd, geo, "svg");
  print_svg_cidade(svg, city);

  free_lista(city.quadras);
  free_lista(city.hidrantes);
  free_lista(city.semaforos);
  free_lista(city.torres);
  free_lista(city.formas);

  free(txt);
  free(svg);
  free(full_name);
  free(qry);
  free(geo);
  free(bsd);
  free(bed);

  return 0;
}
