#include "message.h"

/**************************************************************************************************/
/*																								  */
/* RecupererDateSysteme		retourne la date au moment où la fonction est appelée				  */
/*																								  */
/*En sortie:	La valeur retournée est un entier sous la forme aaaammjj						  */
/*																								  */
/**************************************************************************************************/

int RecupererDateSysteme() {
	char 		buffer[TAILLE_DATE]; /* stocke la date sous forme de texte */
	int 		date; /* variable resultat */
	time_t		t = time(NULL);
	struct tm * tm = localtime(&t); /* on recupere la date avec une librairie C */

	/* on veut la date sous le format aaammjj: la documentation de la librairie
	nous indique d'utiliser ce formatage */
	strftime(buffer, TAILLE_DATE, "%Y%m%d", tm);

	/* la date retournée par la librairie est une chaine de caracteres; on la convertit en entier */
	date = atoi(buffer);
	return date;
}

/**************************************************************************************************/
/*																								  */
/* AfficherMessagesValides		affiche les messages valides sur la sortie standard				  */
/*																								  */
/*En entrée:	liste un pointeur sur une structure liste initialisée							  */
/*																								  */
/**************************************************************************************************/

void AfficherMessagesValides(liste_t * liste) {
	message_t * cour = liste->premier; /* pointeur sur le message traité */
	int			date = RecupererDateSysteme(); /* la date au moment où la fonction est appelée */

	while(cour != NULL) { /* tant qu'il reste des messages à traiter */
		/* si le message est valide */
		if(cour->DebutValidite < date && cour->FinValidite > date) {
			/* on l'affiche avec ses dates de debut et fin */
			printf("%d %d - %s\n", cour->DebutValidite, cour->FinValidite, cour ->texte);
		}
		/* on passe au message suivant */
		cour = cour->suivant;
	}
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
	message_t  * cour = liste->premier; /* pointeur sur le message traité */
	message_t ** prec = &(liste->premier); /* pointeur sur son precedent */
	int			 date = RecupererDateSysteme(); /* la date au moment où la fonction est appelée */

	while(cour != NULL) { /* tant qu'il reste des messages à traiter */
		if(cour->FinValidite < date) { /* si le message n'est plus valide */
			cour = cour->suivant; /* le message courant est le suivant, mais le precedant ne change pas */
			SupprimerCellule(prec); /* on supprime le message invalide de la liste chainée */
		}
		else { /* si il est valide */
			prec = &(cour->suivant); /* on passe au message suivant */
			cour = cour->suivant;
		}
	}
}

/**************************************************************************************************/
/*																								  */
/*	ModifierDateDebut		modifie la date de début de tous les messages ayant					  */
/*							une date de début donnée											  */
/*																								  */
/*	En entrée:	liste un pointeur sur une structure liste initialisée							  */
/*				DateInitiale la date de début à remplacer										  */
/*				NouvelleDate la nouvelle date remplaçant DateInitiale							  */
/*																								  */
/*	Principe: La liste chainée étant triée, on cherche le premier message dont la date est		  */
/*		à changer. Si on l'a trouvé, on change toutes les dates des messages à changer et on	  */
/*		enregistre l'adresse du dernier message qui a changé. On cherche ensuite où on doit		  */
/*		placer la nouvelle date dans la liste chainée, et on fait les changements de pointeurs	  */
/*		nécessaires pour garder l'ordre chronologique de début de message						  */
/*																								  */
/**************************************************************************************************/

void ModifierDateDebut(liste_t * liste, int DateInitiale, int NouvelleDate) {
	message_t ** prec = NULL;
	message_t ** prec1 = &(liste->premier);
	message_t  * cour = liste->premier; /* pointeur sur le message traité */
	message_t  * DebutChangement = NULL;
	message_t  * FinChangement = NULL;

	while(cour != NULL && cour->DebutValidite < DateInitiale) {
		prec1 = &(cour->suivant);
		cour = cour->suivant;
	}

	if(cour != NULL) {
		DebutChangement = cour; /* debut des dates à changer */
		FinChangement = cour;

		while(cour != NULL && cour->DebutValidite == DateInitiale) {
			cour->DebutValidite = NouvelleDate;
			FinChangement = cour; /* fin des dates à changer */
			cour = cour->suivant;
		}

		prec = RecherchePrec(liste, NouvelleDate);

		*prec1 = FinChangement->suivant;
		FinChangement->suivant = *prec;
		*prec = DebutChangement;
	}
}

/**************************************************************************************************/
/*																								  */
/*	MessagesContenantMotif	affiche les messages contenant un motif (chaine de caractères) donné  */
/*							quelque soit la date												  */
/*																								  */
/*	En entrée:	liste un pointeur sur une structure liste initialisée							  */
/*				motif une chaine de caracteres													  */
/*																								  */
/*	Principe:	on regarde chaque message, et on teste si le message contient le motif. Si oui,	  */
/*				on affiche le message															  */
/*																								  */
/**************************************************************************************************/

void MessagesContenantMotif(liste_t * liste, char * motif) {
	message_t * cour = liste->premier; /* pointeur sur le message traité */

	while(cour != NULL) { /* tant qu'il reste des messages à traiter */
		if(ContientMotif(cour->texte, motif)) { /* si le texte du message contient le motif recherché */
			/* on affiche le message avec ses dates de but et fin */
			printf("%08d %08d - %s\n", cour->DebutValidite, cour->FinValidite, cour->texte);
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
	size_t	TailleS = strlen(s); /* taille de la chaine de caracteres dans laquelle on cherche le motif */
	size_t	TailleMotif = strlen(motif); /* taille de la chaine de caracteres du motif */
	size_t	i = 0, j = 0; /* variables d'avancement dans les chaines de caracteres */
	int		trouve = 0; /* variable retour */

	/* on teste si le motif se superpose depuis chaque caractere de s */
	while(i < TailleS - TailleMotif && !trouve) {
		j = 0;
		
		/* pour chaque lettre du motif, on verifie si elle se superpose à s */
		while(j < TailleMotif && motif[j] == s[i+j]) {
			j++;
		}
		/* le motif est trouvé si on sort de la boucle car on est arrivé à la fin du motif */
		trouve = (j == TailleMotif);
		i++;
	}

	return trouve;
}
