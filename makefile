all: main.c listeChainee.c fichier.c message.c
	gcc -g -Wall -Wextra -Wpedantic -ansi -Wno-endif-labels -o main main.c listeChainee.c fichier.c message.c

clean: rm main