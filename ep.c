#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "lista_ligada.h"

#define TAMANHO 10000

int main(int argc, char ** argv){

	FILE * in;
	char * linha;
	char * copia_ponteiro_linha;
	char * quebra_de_linha;
	char * palavra;	
	int contador_linha;

  ListaLigada * lista_ligada = cria_lista();

	if(argc == 2) {

		in = fopen(argv[1], "r");

		printf(">>>>> Carregando arquivo...\n");

		contador_linha = 0;
 		linha = (char *) malloc((TAMANHO + 1) * sizeof(char));

		while(in && fgets(linha, TAMANHO, in)){
			
			if( (quebra_de_linha = strrchr(linha, '\n')) ) *quebra_de_linha = 0;

			printf("linha %03d: '%s'\n", contador_linha + 1, linha);

			// fazemos uma copia do endereço que corresponde ao array de chars 
			// usado para armazenar cada linha lida do arquivo pois a função 'strsep' 
			// modifica o endereço do ponteiro a cada chamada feita a esta função (e 
			// não queremos que 'linha' deixe de apontar para o inicio do array).

			copia_ponteiro_linha = linha;

      char * delim = " -";
			while( (palavra = strsep(&copia_ponteiro_linha, delim)) ){
				// antes de guardar a palavra em algum tipo de estrutura usada
				// para implementar o índice, será necessário fazer uma copia
				// da mesma, uma vez que o ponteiro 'palavra' aponta para uma 
				// substring dentro da string 'linha', e a cada nova linha lida
				// o conteúdo da linha anterior é sobreescrito.
        Indice * indice;

        // TODO: salvar em minusculo
        strcpy(indice->valor, palavra);
        
        if (insere_distinto(lista_ligada, indice->valor)) {
          // TODO: atualiza quantidade
          // TODO: atualiza ocorrencia
        }

				printf("\t\t'%s'\n", palavra);
			}

			contador_linha++;
		}

		printf(">>>>> Arquivo carregado!\n");

    // TODO: copiar lista ligada p lista sequencial

    // TODO: while para menu de opcoes para usuario
    
    // TODO: funcao de busca de palavra -> busca binaria na lista sequencial

		return 0;
	}

	return 1;
}
