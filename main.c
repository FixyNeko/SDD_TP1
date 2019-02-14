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

	InitLCH(&liste);
	LectureFichier(NomFichierLecture, &liste);
	//AfficherMessagesValides(&liste);
	SupprimerMessagesObsoletes(&liste);
	ModifierDateDebut(&liste, 20190207, 66006600);
	MessagesContenantMotif(&liste, " le Tp de S");
	SauvegardeLCH(NomFichierEcriture, &liste);

	return 0;
}
