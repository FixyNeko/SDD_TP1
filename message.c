#include "message.h"

/**************************************************************************************************/
/*																								  */
/* AfficherMessagesValides		affiche les messages valides sur la sortie standard				  */
/*																								  */
/*En entrée:	liste un pointeur sur une structure liste initialisée							  */
/*																								  */
/**************************************************************************************************/

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

/**************************************************************************************************/
/*																								  */
/* RecupererDateSysteme		retourne la date au moment où la fonction est appelée				  */
/*																								  */
/*En sortie:	La valeur retournée est un entier sous la forme aaaammjj						  */
/*																								  */
/**************************************************************************************************/

int RecupererDateSysteme() {
	char 		buffer[TAILLE_DATE];
	int 		date;
	time_t		t = time(NULL);
	struct tm * tm = localtime(&t);

	strftime(buffer, TAILLE_DATE, "%Y%m%d", tm);

	date = atoi(buffer);
	return date;
}

/**************************************************************************************************/
/*																								  */
/* SupprimerMessagesObsoletes		supprime les messages dont la date de fin est dépassée de	  */
/*									la liste chainée											  */
/*																								  */
/*En entrée:	liste un pointeur sur une structure liste initialisée							  */
/*																								  */
/**************************************************************************************************/

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

/**************************************************************************************************/
/*																								  */
/* ModifierDateDebut		modifie la date de début de tous les messages ayant					  */
/*							une date de début donnée											  */
/*																								  */
/*En entrée:	liste un pointeur sur une structure liste initialisée							  */
/*				DateInitiale la date de début à remplacer										  */
/*				NouvelleDate la nouvelle date remplaçant DateInitiale							  */
/*																								  */
/**************************************************************************************************/

void ModifierDateDebut(liste_t * liste, int DateInitiale, int NouvelleDate) {
	message_t * cour = liste->premier;

	while(cour != NULL) {
		if(cour->DebutValidite == DateInitiale) {
			cour->DebutValidite = NouvelleDate;
		}
		cour = cour->suivant;
	}
}

/**************************************************************************************************/
/*																								  */
/* MessagesContenantMotif	affiche les messages contenant un motif (chaine de caractères) donné  */
/*							quelque soit la date												  */
/*																								  */
/*En entrée:	liste un pointeur sur une structure liste initialisée							  */
/*				motif une chaine de caracteres													  */
/*																								  */
/**************************************************************************************************/

void MessagesContenantMotif(liste_t * liste, char * motif) {
	message_t * cour = liste->premier;

	while(cour != NULL) {
		if(ContientMotif(cour->texte, motif)) {
			printf("%d %d - %s\n", cour->DebutValidite, cour->FinValidite, cour ->texte);
		}
		cour = cour->suivant;
	}
}

/**************************************************************************************************/
/*																								  */
/* ContientMotif	fonction qui teste si une chaine de caracteres contient un motif donné		  */
/*							quelque soit la date												  */
/*																								  */
/*	En entrée:	s, motif des chaines de caracteres												  */
/*																								  */
/*	En sortie:	1 si s contient le motif, 0 sinon												  */
/*																								  */
/**************************************************************************************************/

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
		/* le motif est trouvé si on sort de la boucle car plus de caracteres à tester */
		trouve = (j == TailleMotif);
		i++;
	}

	return trouve;
}
