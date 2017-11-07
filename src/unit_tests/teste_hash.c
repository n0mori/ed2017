#include <stdio.h>
#include "../modules/Hash/Hash.h"
#include "../modules/Pessoa/Pessoa.h"
#include "../modules/Comercio/Comercio.h"

int main() {
  int j;
  Hash hash, comercios;
  Pessoa nick, f;
  Comercio i, p;
  printf("Testando indice...\n");
  for (j = 1; j < 10; j++) {
    hash_index(j, "Senhas longas protegem a felicidade");
  }

  printf("Criando uma hash\n");
  hash = new_hash(31);
  comercios = new_hash(31);

  printf("Inserindo algumas coisas...\n");
  nick = new_pessoa("101.247.789-41", "Nicolas", "Omori", 'M', "26/12/1997");
  hash_insert(hash, "101.247.789-41", nick);

  i = new_comercio("1", "12321-123", 'N', 666, "123.123.123-23", "Infobiz");
  p = new_comercio("1", "12321-123", 'N', 666, "321.321.321-32", "Pichau");
  hash_insert(comercios, comercio_get_cnpj(i), i);
  hash_insert(comercios, comercio_get_cnpj(p), p);

  printf("Printando o nome de algo que inseri...\n");
  f = hash_get(hash, "101.247.789-41");
  printf("%s\n", pessoa_get_nome(f));
  printf("%s\n", comercio_get_nome(hash_get(comercios, comercio_get_cnpj(i))));
  printf("%s\n", comercio_get_nome(hash_get(comercios, comercio_get_cnpj(p))));

  printf("Vou deletar o nick\n");
  f = hash_delete(hash, "101.247.789-41");
  free(f);

  hash_free(hash, free);
  hash_free(comercios, free);

  return 0;
}