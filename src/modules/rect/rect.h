#ifndef RECT__H
#define RECT__H

/*
Esse arquivo define os metodos e atributos de um retangulo (abbr: rect).
Um retangulo eh uma forma geometrica bidimensional que possui uma coordenada que
define sua posicao, altura (height) e largura (width). Tambem possui uma cor em
formato reconhecido por SVG, guardada em uma string.
*/

#include <stdlib.h>
#include <string.h>

typedef struct r {
  int id;
  double x, y, width, height;
  char cor[100];
} rect;

rect *new_rect(int id, double width, double height, double x, double y, char *cor);
int rect_interno(rect r, double x, double y);

#endif
