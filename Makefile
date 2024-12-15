compile:
	clear && gcc -o ep ep.c comparador.c lista_ligada.c lista_sequencial_ordenada.c lista_occ.c AVL.c indexador.c utils.c -lm

arvore:
	make compile && clear && ./ep texto.txt arvore

lista:
	make compile && clear && ./ep texto.txt lista
