#include <stdio.h>

int main() {
  char cpf[100], nome[100], sobrenome[100], sexo, nasc[100];
  char buffer[] = "p 10124778941 nicolas omori M 26/12/1997\n";
  sscanf(buffer, "p %[^ ] %[^ ] %[^ ] %c %[^\r\n]", cpf, nome, sobrenome, &sexo, nasc);

  puts(cpf);
  puts(nome);
  puts(sobrenome);
  printf("%c\n", sexo);
  puts(nasc);

  return 0;
}
