#include "message.h"

void AfficherMessagesValides(liste_t * liste) {
	message_t * cour = liste->premier;
	int			date = RecupererDateSysteme();

	while(cour != NULL) {
		if(cour->DebutValidite < date && cour->FinValidite > date) {
			printf("%d %d - %s\n", cour->DebutValidite, cour->FinValidite, cour ->texte);
		}
		cour = cour->suivant;
	}
}

int RecupererDateSysteme() {
	char 		buffer[TAILLE_DATE];
	int 		date;
	time_t		t = time(NULL);
	struct tm * tm = localtime(&t);

	strftime(buffer, TAILLE_DATE, "%Y%m%d", tm);

	date = atoi(buffer);
	return date;
}

void SupprimerMessagesObsoletes(liste_t * liste) {
	message_t  * cour = liste->premier;
	message_t ** prec = &(liste->premier);
	int			 date = RecupererDateSysteme();

	while(cour != NULL) {
		if(cour->FinValidite < date) {
			cour = cour->suivant;
			SupprimerCellule(prec);
		}
		else {
			prec = &(cour->suivant);
			cour = cour->suivant;
		}
	}
}

void ModifierDateDebut(liste_t * liste, int DateInitiale, int NouvelleDate) {
	message_t * cour = liste->premier;

	while(cour != NULL) {
		if(cour->DebutValidite == DateInitiale) {
			cour->DebutValidite = NouvelleDate;
		}
		cour = cour->suivant;
	}
}

void MessagesContenantMotif(liste_t * liste, char * motif) {
	message_t * cour = liste->premier;

	while(cour != NULL) {
		if(ContientMotif(cour->texte, motif)) {
			printf("%d %d - %s\n", cour->DebutValidite, cour->FinValidite, cour ->texte);
		}
		cour = cour->suivant;
	}
}

int ContientMotif(char *s, char *motif) {
	size_t	TailleS = strlen(s);
	size_t	TailleMotif = strlen(motif);
	size_t	i = 0, j = 0;
	int		trouve = 0;

	while(i < TailleS - TailleMotif && !trouve) {
		j = 0;
		while(j < TailleMotif && motif[j] == s[i+j]) {
			j++;
		}
		trouve = (j == TailleMotif);
		i++;
	}

	return trouve;
}
