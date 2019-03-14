#include "main.h"

int main(int argc, char ** argv) {
	liste_t liste;

	char* NomFichierLecture; /* Nom du fichier lu, passé en 1er paramètre du programme */
	char* NomFichierEcriture; /* Nom du fichier écrit, passé en 2eme paramètre du programme */

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

	InitLCH(&liste);
	LectureFichier(NomFichierLecture, &liste);
	ModifierDateDebut(&liste, 19851030, 20301030);
	SupprimerMessagesObsoletes(&liste);
	MessagesContenantMotif(&liste, "message");
	SauvegardeLCH(NomFichierEcriture, &liste);

	SupprimerLCH(&liste);

	/* Traitement */

	return 0;
}
