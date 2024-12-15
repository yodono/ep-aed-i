#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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

int conta_linhas (FILE * in) {
  char * _linha = (char *) malloc((TAMANHO + 1) * sizeof(char));
  int count = 0;
	char * quebra_de_linha;
  
  while(in && fgets(_linha, TAMANHO, in)) {
		if( (quebra_de_linha = strrchr(_linha, '\n')) ) *quebra_de_linha = 0;
    count++;
  }
  
  fclose(in);
  return count;
}

void null_fn() {}

