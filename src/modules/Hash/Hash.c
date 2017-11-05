#include "Hash.h"

const char global_key[] = "The quick brown fox jumps over the lazy dog";
const int  global_size  = 41; 

typedef struct hash {
  int size, used;
  int (*cmp)(void *a, void *key);
  Lista *arr;
}* StHash;

int hash_index(int size, char *key) {
  int i, soma, index;
  soma = 0;
  for (i = 0; i < strlen(key); i++) {
    soma += (key[i] * i) / (global_key[i % global_size]);
  }
  index = soma % size;
  /*printf("soma: %d index: %d\n", soma, index);*/
  return index;
}

Hash new_hash(int size, int (*compar)(void *a, void *key)) {
  int i;
  StHash hash = malloc(sizeof(struct hash));
  hash->size = size;
  hash->used = 0;
  hash->arr = malloc(sizeof(Lista) * size);
  hash->cmp = compar;
  for (i = 0; i < size; i++) {
    hash->arr[i] = create_lista();
  }
  return hash;
}

void hash_insert(Hash hash, char* key, void* data) {
  StHash h = (StHash) hash;
  int index = hash_index(h->size, key);
  insert_first(h->arr[index], data);
}

void *hash_get(Hash hash, char *key) {
  StHash h = (StHash) hash;
  int index = hash_index(h->size, key);
  return search_lista(h->arr[index], h->cmp, key);
}

void *hash_delete(Hash hash, char *key) {
  StHash h = (StHash) hash;
  int index = hash_index(h->size, key);
  return (seek_and_destroy_lista(h->arr[index], h->cmp, key));
}

void hash_free(Hash hash) {
  int i;
  StHash h = (StHash) hash;
  for (i = 0; i < h->size; i++) {
    free_lista(h->arr[i]);
  }
  free(h->arr);
  free(h);
}