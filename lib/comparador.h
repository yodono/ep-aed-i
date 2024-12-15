#ifndef COMPARADOR_H
#define COMPARADOR_H

#include "types.h"

Boolean eq(Elemento * a, Elemento * b);
Boolean eq_char(char * a, char * b);
Boolean neq(Elemento * a, Elemento * b);
Boolean lt(Elemento * a, Elemento * b);
Boolean gt(Elemento * a, Elemento * b);
Boolean nornull(Elemento * a, Elemento * b);
Boolean is_null(Elemento * e);

#endif

