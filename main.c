#include "main.h"

int main(int argc, char ** argv) {
	liste_t liste;

	char* NomFichierLecture; // Nom du fichier lu, passé en 1er paramètre du programme
	char* NomFichierEcriture; // Nom du fichier écrit, passé en 2eme paramètre du programme

	if(argc == 2) {
		NomFichierLecture = argv[1];
		NomFichierEcriture = argv[1];
	}
	else if(argc == 3) {
		NomFichierLecture = argv[1];
		NomFichierEcriture = argv[2];
	}
	else {
		exit(EXIT_FAILURE);
	}

	/* Traitement */

	printf("\nchaine vide\n\n");
	InitLCH(&liste);
	LectureFichier("Tests/FichierVide.txt", &liste);
	MessagesContenantMotif(&liste, "message depassé");

	SupprimerLCH(&liste);

	printf("\nmotif vide\n\n");
	InitLCH(&liste);
	LectureFichier("Tests/FichierNormal.txt", &liste);
	MessagesContenantMotif(&liste, "");

	SupprimerLCH(&liste);

	printf("\nmotif et chaine non vides\n\n");
	InitLCH(&liste);
	LectureFichier("Tests/FichierNormal.txt", &liste);
	MessagesContenantMotif(&liste, "message depassé");

	SupprimerLCH(&liste);

	/* Traitement */

	return 0;
}
