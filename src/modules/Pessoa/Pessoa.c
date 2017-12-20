#include "Pessoa.h"

typedef struct stPessoa {
  char cpf[100];
  char nome[100];
  char sobrenome[100];
  char sexo;
  char nasc[100]; 
  int vivo;
  Celular celular;
}* Person;

Pessoa new_pessoa(char *cpf, char *nome, char *sobrenome, char sexo, char *nasc) {
  Pessoa pessoa = malloc(sizeof(struct stPessoa));
  Person p = (Person) pessoa;
  strcpy(p->cpf, cpf);
  strcpy(p->nome, nome);
  strcpy(p->sobrenome, sobrenome);
  p->sexo = sexo;
  strcpy(p->nasc, nasc);
  p->vivo = 1;
  p->celular = NULL;
  return pessoa;
}

char *pessoa_get_cpf(Pessoa p) {
  Person person = (Person) p;
  return person->cpf;
}

char *pessoa_get_nome(Pessoa p) {
  Person person = (Person) p;
  return person->nome;
}

char *pessoa_get_sobrenome(Pessoa p) {
  Person person = (Person) p;
  return person->sobrenome;
}

char pessoa_get_sexo(Pessoa p) {
  Person person = (Person) p;
  return person->sexo;
}

char *pessoa_get_nasc(Pessoa p) {
  Person person = (Person) p;
  return person->nasc;
}

Celular pessoa_get_celular(Pessoa p) {
  Person person = (Person) p;
  return person->celular;
}

int cmp_pessoa_cpf(Pessoa p, void *cpf) {
  return strcmp(pessoa_get_cpf(p), cpf) == 0;
}

int cmp_pessoa_operadora(Pessoa p, void *op) {
  Celular c = pessoa_get_celular(p);
  char cop;
  if (c == NULL) {
    return 0;
  }
  cop = celular_get_operadora(c);
  if (cop == 'u') {
    return strcmp("um", op) == 0;
  } else if (cop == 's') {
    return strcmp("su", op) == 0;
  } else {
    return 0;
  }
}

int cmp_pessoa_pessoa(Pessoa p, Pessoa r) {
  return strcmp(pessoa_get_nome(p), pessoa_get_nome(r));
}

void pessoa_set_celular(Pessoa p, Celular celular) {
  Person person = (Person) p;
  person->celular = celular;
}

int pessoa_viva(Pessoa p) {
  Person person = (Person) p;
  return person->vivo;
}

void kill_pessoa(Pessoa p) {
  Person person = (Person) p;
  person->vivo = 0;
}

void pessoa_imprime_dados(Pessoa p, FILE *out) {
  fprintf(out, "%s %s %s %s\n",
          pessoa_get_nome(p),
          pessoa_get_sobrenome(p),
          pessoa_get_cpf(p),
          pessoa_get_nasc(p));
}