#include "Connection.h"

typedef struct connection {
  Ponto a;
  Ponto b;
}* StConnection;

Connection new_connection(Ponto a, Ponto b) {
  StConnection c = malloc(sizeof(struct connection));
  c->a = a;
  c->b = b;
  return c;
}

double connection_get_xa(Connection c) {
  StConnection con = (StConnection) c;
  return get_x(con->a);
}

double connection_get_xb(Connection c) {
  StConnection con = (StConnection) c;
  return get_x(con->b);
}

double connection_get_ya(Connection c) {
  StConnection con = (StConnection) c;
  return get_y(con->a);
}

double connection_get_yb(Connection c) {
  StConnection con = (StConnection) c;
  return get_y(con->b);
}

void free_connection(Connection c) {
  StConnection con = (StConnection) c;
  free(con->a);
  free(con->b);
  free(con);
}