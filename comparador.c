#include <string.h>
#include "ep.h"

Boolean eq(Elemento a, Elemento b) {
  return strcmp(a, b) == 0;
}

Boolean lt(Elemento a, Elemento b) {
  return strcmp(a, b) < 0;
}

Boolean gt(Elemento a, Elemento b) {
  return strcmp(a, b) > 0;
}

