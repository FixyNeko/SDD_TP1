#include "listeChainee.h"

void InitLCH(liste_t * liste) {
	if(liste == NULL) {
		exit(EXIT_FAILURE);
	}
	liste->premier = NULL;
}

message_t *CreerCellule(int DebutValidite, int FinValidite, char * texte) {
	message_t * cellule = (message_t *) malloc(sizeof(message_t));
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
	message_t ** prec = &(liste->premier);
	message_t  * cour = liste->premier;
	while(cour != NULL &&
			cour->DebutValidite < valeur) {
		prec = &(cour->suivant);
		cour = cour->suivant;
	}
	
	return prec;
}

void SupprimerCellule(message_t ** prec) {
	message_t * cour = *prec;
	if(cour != NULL) {
		*prec = (*prec)->suivant;
		free(cour->texte);
		free(cour);
	}
}

void ParcoursLCH(liste_t * liste) {
	message_t * cour = liste->premier;
	while(cour != NULL) {
		printf("%d %d %s\n", cour->DebutValidite, cour->FinValidite, cour ->texte);
		cour = cour->suivant;
	}
}

void SupprimerLCH(liste_t * liste) {
	while(liste->premier != NULL) {
		SupprimerCellule(&(liste->premier));
	}

	free(liste->premier);
}
