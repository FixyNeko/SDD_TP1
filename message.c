#include "message.h"

void AfficherMessagesValides(liste_t * liste) {
	message_t	*cour;
	int			date = RecupererDateSysteme();
	if(liste->premier != NULL) {
		cour = liste->premier;
		while(cour != NULL) {
			if(cour->DebutValidite < date && cour->FinValidite > date) {
				printf("%d %d - %s\n", cour->DebutValidite, cour->FinValidite, cour ->texte);
			}
			cour = cour->suivant;
		}
	}
}

int RecupererDateSysteme() {
	char 		buffer[TAILLE_DATE];
	int 		date;
	time_t		t = time(NULL);
	struct tm	*tm = localtime(&t);

	strftime(buffer, TAILLE_DATE, "%Y%m%d", tm);

	date = atoi(buffer);
	return date;
}

void SupprimerMessagesObsoletes(liste_t * liste) {
	message_t	*cour;
	message_t	**prec;
	int			date = RecupererDateSysteme();
	if(liste->premier != NULL) {
		prec = &(liste->premier);
		cour = liste->premier;
		while(cour != NULL) {
			if(cour->FinValidite < date) {
				SupprimerCellule(prec);
				cour = (*prec)->suivant;
			}
			prec = &(cour->suivant);
			cour = cour->suivant;
		}
	}
}

void ModifierDateDebut(liste_t * liste, int DateInitiale, int NouvelleDate) {
	message_t	*cour;
	if(liste->premier != NULL) {
		cour = liste->premier;
		while(cour != NULL) {
			if(cour->DebutValidite == DateInitiale) {
				cour->DebutValidite = NouvelleDate;
			}
			cour = cour->suivant;
		}
	}
}

void MessagesContenantMotif(liste_t * liste, char * motif) {
	message_t	*cour;
	if(liste->premier != NULL) {
		cour = liste->premier;
		while(cour != NULL) {
			if(ContientMotif(cour->texte, motif)) {
				printf("%d %d - %s\n", cour->DebutValidite, cour->FinValidite, cour ->texte);
			}
			cour = cour->suivant;
		}
	}
}

int ContientMotif(char *s, char *motif) {
	size_t	TailleS = strlen(s);
	size_t	TailleMotif = strlen(motif);
	int		trouve = 0, i = 0, j;

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
