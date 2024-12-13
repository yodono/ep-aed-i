#include <string.h>
#include "utils.h"

Boolean eq_char(char * a, char * b) {
  return strcmp(a, b) == 0;
}

Boolean eq(Elemento * a, Elemento * b) {
  return nornull(a, b) && strcmp(a->valor, b->valor) == 0;
}

Boolean neq(Elemento * a, Elemento * b) {
  return !eq(a, b);
}

Boolean lt(Elemento * a, Elemento * b) {
  return nornull(a, b) && strcmp(a->valor, b->valor) < 0;
}

Boolean gt(Elemento * a, Elemento * b) {
  return nornull(a, b) && strcmp(a->valor, b->valor) > 0;
}

Boolean is_null(Elemento * e) {
  return !e || !e->valor;
}

Boolean nornull(Elemento * a, Elemento * b) {
  return !(is_null(a) || is_null(b));
}

