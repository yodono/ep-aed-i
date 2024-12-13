compile:
	clear && gcc -o ep ep.c comparador.c lista_ligada.c lista_sequencial_ordenada.c lista_occ.c AVL.c strategy.c utils.c -lm
