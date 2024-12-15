compile:
	clear && gcc -o ep ep.c lib/comparador.c lib/lista_ligada.c lib/lista_sequencial_ordenada.c lib/lista_occ.c lib/AVL.c lib/indexador.c lib/utils.c -lm

arvore:
	make compile && clear && ./ep texto.txt arvore

lista:
	make compile && clear && ./ep texto.txt lista
