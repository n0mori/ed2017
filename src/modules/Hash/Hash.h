#ifndef HASH__H
#define HASH__H

/* 
Este é o módulo que implementará a tabela de espalhamento (Hash). Uma tabela de espalhamento
é uma maneira eficaz de fazer buscas em um conjunto de dados.
*/

#include "../Lista/Lista.h"
#include <string.h>
#include <stdio.h>

typedef void* Hash;

Hash new_hash(int size);
void hash_insert(Hash hash, char* key, void* data);
int hash_index(int size, char *key); /*TEMPORARIAMENTE NO .h, RETIRAR*/
void *hash_get(Hash hash, char *key);
void *hash_delete(Hash hash, char *key);
void hash_free(Hash hash, void (*destroy)(void *a));

#endif
