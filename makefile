all: main.c listeChainee.c fichier.c
	gcc -o main main.c listeChainee.c fichier.c -g

clean: rm main