#ifndef CELULAR__H
#define CELULAR__H

/* Um celular é um aparelho móvel utilizado para efetuar chamadas de voz.
Um celular é identificado por um número de 8 ou 9 digitos, tem um dono (cpf)
e se conecta a uma torre de celular de operadora igual
*/

typedef void* Celular;

Celular new_celular(char *numero, char *cpf);
char *celular_get_numero(Celular c);
char *celular_get_cpf(Celular c);
int cmp_celular_numero(Celular c, void *numero);

#endif