#include "Pessoa.h"

typedef struct stPessoa {
  char cpf[100];
  char nome[100];
  char sobrenome[100];
  char sexo;
  char nasc[100]; 
}* Person;

Pessoa new_pessoa(char *cpf, char *nome, char *sobrenome, char sexo, char *nasc) {
  Pessoa pessoa = malloc(sizeof(struct stPessoa));
  Person p = (Person) pessoa;
  strcpy(cpf, p->cpf);
  strcpy(nome, p->nome);
  strcpy(sobrenome, p->sobrenome);
  p->sexo = sexo;
  strcpy(nasc, p->nasc);
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
