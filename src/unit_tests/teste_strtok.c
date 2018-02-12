#include <string.h>
#include <stdio.h>

int main() {
  char buffer[10000], *sufixo, *r1, *r2, *cor, *token;
  int opt_pic, opt_dist;

  fgets(buffer, 10000, stdin);

  token = strtok(buffer, " ");
  puts(token);
  
  token = strtok(NULL, " ");
  puts(token);

  if (token[0] == 'p') {
    opt_pic = 1;
    sufixo = strtok(NULL, " ");
    puts(sufixo);
  } else {
    opt_pic = 0;
  }

  token = strtok(NULL, " ");
  if (token[0] == 'D') {
    opt_dist = 1;
  } else {
    opt_dist = 2;
  }

  r1 = strtok(NULL, " ");
  r2 = strtok(NULL, " ");

  if (opt_pic) {
    cor = strtok(NULL, " ");
  }
  
  puts(r1);
  puts(r2);
  puts(cor);

  return 0;

}