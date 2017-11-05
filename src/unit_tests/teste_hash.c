#include <stdio.h>
#include "../modules/Hash/Hash.h"
#include "../modules/Pessoa/Pessoa.h"

int main() {
  int i;
  Hash hash;
  Pessoa nick, f;
  printf("Testando indice...\n");
  for (i = 1; i < 10; i++) {
    hash_index(i, "Senhas longas protegem a felicidade");
  }

  printf("Criando uma hash\n");
  hash = new_hash(31, cmp_pessoa_cpf);

  printf("Inserindo algumas coisas...\n");
  nick = new_pessoa("101.247.789-41", "Nicolas", "Omori", 'M', "26/12/1997");
  hash_insert(hash, "101.247.789-41", nick);

  printf("Printando o nome de algo que inseri...\n");
  f = hash_get(hash, "101.247.789-41");
  printf("%s\n", pessoa_get_nome(f));

  printf("Vou deletar o nick\n");
  f = hash_delete(hash, "101.247.789-41");
  free(f);

  hash_free(hash);

  return 0;
}