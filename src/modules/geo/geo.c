#include "geo.h"

int intersec_cc(circ a, circ b) {
  if (dist_cc(a.ancora, b.ancora) <= a.raio + b.raio) {
    return 1;
  }
  return 0;
}

void extremidades_cc(circ a, circ b, double *extremidades) {
  if (circ_upmost(a) <= circ_upmost(b)) {
    extremidades[0] = circ_upmost(a);
  } else {
    extremidades[0] = circ_upmost(b);
  }
  if (circ_leftmost(a) <= circ_leftmost(b)) {
    extremidades[1] = circ_leftmost(a);
  } else {
    extremidades[1] = circ_leftmost(b);
  }
  if (circ_botmost(a) >= circ_botmost(b)) {
    extremidades[2] = circ_botmost(a);
  } else {
    extremidades[2] = circ_botmost(b);
  }
  if (circ_rightmost(a) >= circ_rightmost(b)) {
    extremidades[3] = circ_rightmost(a);
  } else {
    extremidades[3] = circ_rightmost(b);
  }
}
