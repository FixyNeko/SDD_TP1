#include "listeChainee.h"

/**************************************************************************************************/
/*																								  */
/* InitLCH	initialise une liste chainée														  */
/*																								  */
/*	En entrée:	liste un pointeur sur une structure liste										  */
/*																								  */
/**************************************************************************************************/

void InitLCH(liste_t * liste) {
	if(liste == NULL) {
		exit(EXIT_FAILURE);
	}
	liste->premier = NULL;
}

/**************************************************************************************************/
/*																								  */
/* CreerCellule	crée une cellule de liste chainée à partir des donéées à stocker				  */
/*																								  */
/*	En entrée:	DebutValidite, FinValidite, texte les données à stocker dans la cellule			  */
/*																								  */
/*	En sortie:	retourne l'adresse de la cellule crée											  */
/*																								  */
/**************************************************************************************************/

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

/**************************************************************************************************/
/*																								  */
/* InsertionApres	insere une cellule dans la liste chainée apres une cellule de la liste donnée */
/*																								  */
/*	En entrée:	message un pointeur vers la cellule à ajouter à la liste						  */
/*				prec un pointeur sur l'attribut suivant d'une cellule de la liste				  */
/*																								  */
/**************************************************************************************************/

void InsertionApres(message_t * message, message_t ** prec) {
	message->suivant = *prec;
	*prec = message;
}

/**************************************************************************************************/
/*																								  */
/* RecherchePrec	recherche le precedent d'une valeur dans une liste chainée					  */
/*					selon la date de debut des messages											  */
/*																								  */
/*	En entrée:	liste un pointeur sur une structure liste initialisée							  */
/*				valeur la date pour laquelle on cherche le precedant							  */
/*																								  */
/*	En sortie:	retourne le précédant de la valeur												  */
/*																								  */
/**************************************************************************************************/

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

/**************************************************************************************************/
/*																								  */
/* SupprimerCellule	supprime une  cellule de la liste chainée et libère la mémoire				  */
/*																								  */
/*	En entrée:	prec le precedant de la cellule à supprimer										  */
/*																								  */
/**************************************************************************************************/

void SupprimerCellule(message_t ** prec) {
	message_t * cour = *prec;

	if(cour != NULL) {
		*prec = (*prec)->suivant;
		free(cour->texte);
		free(cour);
	}
}

/**************************************************************************************************/
/*																								  */
/* ParcoursLCH	afficher tout le contenu de la list chainée										  */
/*																								  */
/*	En entrée:	liste un pointeur sur une structure liste initialisée							  */
/*																								  */
/**************************************************************************************************/

void ParcoursLCH(liste_t * liste) {
	message_t * cour = liste->premier;

	while(cour != NULL) {
		printf("%d %d %s\n", cour->DebutValidite, cour->FinValidite, cour ->texte);
		cour = cour->suivant;
	}
}

/**************************************************************************************************/
/*																								  */
/* SupprimerLCH	supprime tous les éléments de la liste chainée 									  */
/*																								  */
/*	En entrée:	liste un pointeur sur une structure liste initialisée							  */
/*																								  */
/**************************************************************************************************/

void SupprimerLCH(liste_t * liste) {
	while(liste->premier != NULL) {
		SupprimerCellule(&(liste->premier));
	}
}
