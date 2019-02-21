#include "fichier.h"

void LectureFichier(char * NomFichier, liste_t * liste) {
	FILE	*fichier;
	char	texte[TAILLE_TEXTE];
	int		LongueurTexte;

	fichier = fopen(NomFichier, "r");

	if(fichier != NULL) {

		while(0 == feof(fichier)) {
			message_t * message = (message_t *) malloc(sizeof(message_t));
			fscanf(fichier, "%d %d ", &(message->DebutValidite), &(message->FinValidite));
			fgets(texte, TAILLE_TEXTE, fichier);
			suprRN(texte, TAILLE_TEXTE);
			LongueurTexte = strlen(texte);
			message->texte = (char*) malloc(LongueurTexte * sizeof(char));
			strcpy(message->texte, texte);
			InsertionApres(message, RecherchePrec(liste, message->DebutValidite));
		}
		fclose(fichier);
	}
}

void SauvegardeLCH(char * NomFichier, liste_t * liste) {
	FILE * fichier = fopen(NomFichier, "w");
	if(fichier != NULL) {
		if(liste->premier != NULL) {
			message_t * cour = liste->premier;
			while(cour != NULL) {
				fprintf(fichier, "%d %d %s", cour->DebutValidite, cour->FinValidite, cour ->texte);
				if(cour->suivant != NULL) {
					fputc('\n', fichier);
				}
				cour = cour->suivant;
			}
		}
		fclose(fichier);
	}
}

void suprRN(char* s, int tailleMax) {
	int i = 0;
	while(i < tailleMax && (s[i] != '\n' && s[i] != '\r'))
		i++;
	s[i] = '\0';
}
