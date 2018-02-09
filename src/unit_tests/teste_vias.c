#include <stdio.h>
#include <float.h>
#include "../modules/Vias/Vias.h"

int main() {
  Vias v = new_vias();

  vias_insert_esquina(v, "1", 0, 0);
  vias_insert_esquina(v, "2", 50, 0);
  vias_insert_esquina(v, "3", 90, 0);
  vias_insert_esquina(v, "4", 0, 60);
  vias_insert_esquina(v, "5", 50, 60);
  vias_insert_esquina(v, "6", 90, 60);
  vias_insert_esquina(v, "7", 0, 100);
  vias_insert_esquina(v, "8", 50, 100);
  vias_insert_esquina(v, "9", 90, 100);

  vias_insert_rua(v, "1", "2", "-", "-", 50, 30, "BH");
  vias_insert_rua(v, "2", "3", "-", "-", 40, 30, "BH");
  vias_insert_rua(v, "1", "6", "-", "-", 60, 30, "Para");
  vias_insert_rua(v, "3", "4", "-", "-", 60, 30, "ES");
  vias_insert_rua(v, "5", "2", "-", "-", 60, 30, "Goias");
  vias_insert_rua(v, "4", "5", "-", "-", 40, 30, "Santos");
  vias_insert_rua(v, "5", "6", "-", "-", 50, 30, "Santos");
  vias_insert_rua(v, "6", "7", "-", "-", 40, 30, "Para");
  vias_insert_rua(v, "4", "9", "-", "-", 40, 30, "ES");
  vias_insert_rua(v, "8", "5", "-", "-", 40, 30, "Goias");
  vias_insert_rua(v, "7", "8", "-", "-", 50, 30, "Paranagua");
  vias_insert_rua(v, "8", "9", "-", "-", 40, 30, "Paranagua");

  vias_calcular_rota(v, new_ponto(1, 1), new_ponto(90, 100), 1);


  return 0;
}