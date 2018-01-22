#include "Register.h"

typedef struct reg {
  char type;
  void *data;
}* StReg;

Register new_register(char type, void *data) {
  StReg r = malloc(sizeof(struct reg));
  r->type = type;
  r->data = data;
  return r;
}

char register_get_type(Register r){
  StReg reg = (StReg) r;
  return reg->type;
}

void* register_get_data(Register r) {
  StReg reg = (StReg) r;
  return reg->data;
}

void regiser_set_type(Register r, char type) {
  StReg reg = (StReg) r;
  reg->type = type;
}

void regiser_set_data(Register r, void *data) {
  StReg reg = (StReg) r;
  reg->data = data;
}