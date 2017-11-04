#ifndef PESSOA__H
#define PESSOA__H

/*
Esse é o módulo que se encarrega de representar as pessoas da cidade e os
seus dados. As pessoas possuem vários dados, como cpf, nome, sobrenome,
entre outros.
*/

typedef void* Pessoa;

Pessoa new_pessoa(char *cpf, char *nome, char *sobrenome, char sexo, char *nasc);
char *pessoa_get_cpf(Pessoa p);
char *pessoa_get_nome(Pessoa p);
char *pessoa_get_sobrenome(Pessoa p);
char pessoa_get_sexo(Pessoa p);
char *pessoa_get_nasc(Pessoa p);

#endif