#include <ctype.h>
#include "utils.h"

void strlwr(char * s) {
  for(int i = 0; s[i]; i++){
    s[i] = tolower(s[i]);
  }
}

int max(int a, int b){
	return a > b ? a : b;
}

