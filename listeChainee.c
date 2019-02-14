#include "listeChainee.h"

void InitLCH(liste_t * liste) {
	if(liste == NULL) {
		exit(EXIT_FAILURE);
	}
	liste->premier = (message_t *) malloc(sizeof(message_t));
	liste->premier = NULL;
}

message_t *CreerCellule(int DebutValidite, int FinValidite, char * texte) {
	message_t *cellule = (message_t *) malloc(sizeof(message_t));
	if(cellule == NULL) {
		exit(EXIT_FAILURE);
	}
	cellule->DebutValidite = DebutValidite;
	cellule->FinValidite = FinValidite;
	cellule->texte = texte;
	cellule->suivant = NULL;
	return cellule;
}

void InsertionApres(message_t * message, message_t ** prec) {
	message->suivant = *prec;
	*prec = message;
}

message_t **RecherchePrec(liste_t * liste, int valeur) {
	message_t **prec = &(liste->premier);
	message_t *cour = liste->premier;
	while(cour != NULL &&
			cour->DebutValidite < valeur) {
		prec = &(cour->suivant);
		cour = cour->suivant;
	}
	
	return prec;
}

void SupprimerCellule(message_t ** prec) {
	message_t *cour = *prec;
	if(cour != NULL) {
		*prec = cour->suivant;
		free(cour->texte);
		free(cour);
	}
}

void ParcoursLCH(liste_t * liste) {
	message_t *cour;
	if(liste->premier != NULL) {
		cour = liste->premier;
		while(cour != NULL) {
			printf("%d %d - %s\n", cour->DebutValidite, cour->FinValidite, cour ->texte);
			cour = cour->suivant;
		}
	}
}

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
