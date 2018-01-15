#include "Rua.h"

typedef struct rua {
  char from[100];
  char to[100];
  char ldir[100];
  char lesq[100];
  char nome[100];
  double comprimento;
  double velocidade;
}* StRua;

Rua new_rua(char *from, char *to, char *ldir, char *lesq, double comprimento, double velocidade, char *nome) {
  StRua rua = malloc(sizeof (struct rua));
  strcpy(rua->from, from);
  strcpy(rua->to, to);
  strcpy(rua->ldir, ldir);
  strcpy(rua->lesq, lesq);
  strcpy(rua->nome, nome);
  rua->comprimento = comprimento;
  rua->velocidade = velocidade;
  return rua;
}

char* rua_get_from(Rua r) {
}

char* rua_get_to(Rua r);
char* rua_get_ldir(Rua r);
char* rua_get_lesq(Rua r);
char* rua_get_nome(Rua r);
double rua_get_comprimento(Rua r);
double rua_get_velocidade(Rua r);