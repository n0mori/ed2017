#include "svg.h"

void print_svg_circ(FILE *fsvg, circ *c) {
  fprintf(fsvg, "<circle cx=\"%lf\" cy=\"%lf\" r=\"%lf\" fill=\"%s\"/>\n", c->x, c->y, c->raio, c->cor);
}

void print_svg_rect(FILE *fsvg, rect *r) {
  fprintf(fsvg, "<rect x=\"%lf\" y=\"%lf\" width=\"%lf\" height=\"%lf\" fill=\"%s\"/>\n", r->x, r->y, r->width, r->height, r->cor);
}

void print_sobreposto(FILE *fsvg, double *extremidades) {
  fprintf(fsvg, "<rect x=\"%lf\" y=\"%lf\" width=\"%lf\" height=\"%lf\" fill=\"none\" style=\"stroke:pink;stroke-width:3;stroke-dasharray:5,5;z-index:1000\"/>\n", extremidades[1], extremidades[0], extremidades[3] - extremidades[1], extremidades[2] - extremidades[0]);
  fprintf(fsvg, "<text x=\"%lf\" y=\"%lf\" fill=\"red\" font-size=\"16\" style=\"z-index:100\">sobrepoe</text>\n", extremidades[1], extremidades[0] + 16);
}

void print_circ_points(FILE *fsvg, circ *c, char *cor) {
  fprintf(fsvg, "<circle cx=\"%lf\" cy=\"%lf\" r=\"5\" fill=\"%s\"/>\n", c->x, c->y, cor);
}

void print_rect_points(FILE *fsvg, rect *r, char *cor) {
  fprintf(fsvg, "<circle cx=\"%lf\" cy=\"%lf\" r=\"5\" fill=\"%s\"/>\n", r->x, r->y, cor);
  fprintf(fsvg, "<circle cx=\"%lf\" cy=\"%lf\" r=\"5\" fill=\"%s\"/>\n", r->x + r->width, r->y, cor);
  fprintf(fsvg, "<circle cx=\"%lf\" cy=\"%lf\" r=\"5\" fill=\"%s\"/>\n", r->x, r->y + r->height, cor);
  fprintf(fsvg, "<circle cx=\"%lf\" cy=\"%lf\" r=\"5\" fill=\"%s\"/>\n", r->x + r->width, r->y + r->height, cor);
}
