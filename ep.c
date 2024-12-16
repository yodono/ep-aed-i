#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h> 

#include "lib/indexador.h"

int main(int argc, char ** argv){

	FILE * in;
  char * nome_arquivo;
	char * linha;
	char * copia_ponteiro_linha;
	char * quebra_de_linha;
	char * palavra;	
	int contador_linha;
  int total_linhas;
  int total_palavras_indexadas = 0;

  double tempo_construcao, tempo_diff;

	if(argc == 3) {

    tempo_construcao = clock();

    nome_arquivo = argv[1];

    // lendo total de linhas
		in = fopen(nome_arquivo, "r");
    total_linhas = conta_linhas(in);
		char * lista_linhas[total_linhas];

    // carregando arquivo
		in = fopen(nome_arquivo, "r");
    Indexador * indexador = cria_estrategia(argv[2]);

		// printf(">>>>> Carregando arquivo...\n");

    contador_linha = 0;
 		linha = (char *) malloc((TAMANHO + 1) * sizeof(char));

		while(in && fgets(linha, TAMANHO, in)){
			
			if( (quebra_de_linha = strrchr(linha, '\n')) ) *quebra_de_linha = 0;

			// printf("linha %03d: '%s'\n", contador_linha + 1, linha);

			// fazemos uma copia do endereço que corresponde ao array de chars 
			// usado para armazenar cada linha lida do arquivo pois a função 'strsep' 
			// modifica o endereço do ponteiro a cada chamada feita a esta função (e 
			// não queremos que 'linha' deixe de apontar para o inicio do array).

			copia_ponteiro_linha = linha;
      lista_linhas[contador_linha] = (char ) malloc((strlen(linha) + 1) sizeof(char));
      strcpy(lista_linhas[contador_linha], linha);
      
      char * delim = " -,.;!':?";
			while( (palavra = strsep(&copia_ponteiro_linha, delim)) ){
				// antes de guardar a palavra em algum tipo de estrutura usada
				// para implementar o índice, será necessário fazer uma copia
				// da mesma, uma vez que o ponteiro 'palavra' aponta para uma 
				// substring dentro da string 'linha', e a cada nova linha lida
				// o conteúdo da linha anterior é sobreescrito.
        
	      Elemento * novo_elemento = (Elemento *) malloc (sizeof(Elemento));
        novo_elemento->valor = (char *) malloc(strlen(palavra) + 1);
        novo_elemento->quantidade = 0;

        strcpy(novo_elemento->valor, palavra);
        strlwr(novo_elemento->valor);

        // indexador->insere retorna TRUE caso o elemento seja novo, FALSE do contrario
        // indexador->insere atualiza o ponteiro do novo_elemento para o elemento existente caso haja
        if(indexador->insere(indexador->estrutura, &novo_elemento)) {
          novo_elemento->ocorrencias = cria_lista_occ();
        }
        
        insere_occ(novo_elemento->ocorrencias, contador_linha);
        novo_elemento->quantidade++;
        
        total_palavras_indexadas++;
				
        // printf("\t\t'%s'\n", palavra);
			}

			contador_linha++;
		}

		// printf(">>>>> Arquivo carregado!\n\n\n");
    
    indexador->otimizar(indexador);
    setListaLinhas(indexador, lista_linhas);
    
    tempo_diff = clock() - tempo_construcao;

    printf("Arquivo: '%s'\n", nome_arquivo);
    printf("Tipo de indice: '%s'\n", indexador->estrategia);
    printf("Numero de linhas no arquivo: '%d'\n", total_linhas);
    printf("Total de palavras indexadas: '%d'\n", total_palavras_indexadas);
    indexador->imprimir_detalhes(indexador);
    printf("Tempo de carga do arquivo e construcao do indice: %.3lf ms\n", tempo_diff);
    
    menu_busca(indexador);
    
		// printf("\n\n\n>>>>>Fim teste!\n\n\n");
		fclose(in);
    exit(0);
	}

	exit(1);
}

