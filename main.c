#include "main.h"

int main(int argc, char ** argv) {
	liste_t liste;

	char* NomFichierLecture;
	char* NomFichierEcriture;

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

	InitLCH(&liste);
	LectureFichier(NomFichierLecture, &liste);
	AfficherMessagesValides(&liste);
	SupprimerMessagesObsoletes(&liste);
	ParcoursLCH(&liste);
	ModifierDateDebut(&liste, 20190207, 66006600);
	MessagesContenantMotif(&liste, "Tp de");
	SauvegardeLCH(NomFichierEcriture, &liste);
	SupprimerLCH(&liste);

	return 0;
}
