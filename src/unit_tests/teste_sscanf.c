#include <stdio.h>

int main() {
  char sufixo[100], str_x[100], str_y[100], str_width[100], str_height[100];
  sufixo[0] = 0;
  str_x[0] = 0;
  str_y[0] = 0;
  str_width[0] = 0;
  str_height[0] = 0;
  char buffer[] = "pc? meu_pau 10.00 20.000\n";
  sscanf(buffer, "pc? %s %s %s %s %s", sufixo, str_x, str_y, str_width, str_height);

  puts(sufixo);
  puts(str_x);
  puts(str_y);
  puts(str_width);
  puts(str_height);

  return 0;
}
