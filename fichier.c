#include "fichier.h"

/**************************************************************************************************/
/*																								  */
/* LectureFichier		construit une liste chainee de messages depuis un fichier de messages	  */
/*																								  */
/* En entrée:	NomFichier le nom du fichier à lire depuis le repertoire de l'éxécutable		  */
/*				liste un pointeur sur une structure liste initialisée							  */
/*																								  */
/* En sortie:	liste est une liste chainée des messages du fichier d'entrée					  */
/*																								  */
/**************************************************************************************************/

void LectureFichier(char * NomFichier, liste_t * liste) {
	FILE	*fichier; /* descripteur de fichier de lecture */
	char	texte[TAILLE_TEXTE+1] = {0}; /* variable temporaire qui stocke des textes avant traitement */
	int		LongueurTexte; /* variable temporaire contenant la taille du texte */
	message_t * message; /* pointeur temporaire de message en construction */

	fichier = fopen(NomFichier, "r"); /* on ouvre le fichier en lecture seule */

	if(fichier != NULL) { /* si le fichier est valide */
		while(0 == feof(fichier)) { /* tant qu'ona pas atteint la fin du fichier */
			message = (message_t *) malloc(sizeof(message_t)); /* un nouveau message peut etre lu */

			/* on lit les dates de debut et fin */
			fscanf(fichier, "%d %d ", &(message->DebutValidite), &(message->FinValidite));
			/* on lit le reste de la ligne jusqu'à atteindre un retour à la ligne */
			fgets(texte, TAILLE_TEXTE, fichier);
			/* on supprime le retour à la ligne du message */
			suprRN(texte, TAILLE_TEXTE+1);

			LongueurTexte = strlen(texte);

			/* on alloue juste la place necessaire pour stocker le texte en mémoire */
			message->texte = (char *) malloc((LongueurTexte+1) * sizeof(char));
			strcpy(message->texte, texte);

			/* on peut ajouter le message au bon endroit dans la liste */
			InsertionApres(message, RecherchePrec(liste, message->DebutValidite));
		}

		fclose(fichier); /* on pense à fermer le fichier puisqu'on a fini de l'utiliser */
	}
}

/**************************************************************************************************/
/*																								  */
/* SauvegardeLCH		construit un fichier de messages depuis une liste chainee de messages	  */
/*																								  */
/* En entrée:	NomFichier le nom du fichier où écrire depuis le repertoire de l'éxécutable		  */
/*				liste un pointeur sur une structure liste										  */
/*																								  */
/* En sortie:	un fichier representant la liste chainée est crée								  */
/*																								  */
/**************************************************************************************************/

void SauvegardeLCH(char * NomFichier, liste_t * liste) {
	FILE		* fichier; /* descripteur de fichier en écriture */
	message_t	* cour; /* pointeur sur le message traité */

	fichier = fopen(NomFichier, "w"); /* on ouvre un nouveau fichier en écriture */
	cour = liste->premier; /* le premier element à traiter est l'element pointé par la tete de liste */

	if(fichier != NULL) { /* si le fichier est valide */
		while(cour != NULL) { /* tant que l'element à traiter est un message */
			/* on imprime dans le fichier dans le bon format les informations du message */
			fprintf(fichier, "%d %d %s", cour->DebutValidite, cour->FinValidite, cour->texte);
			/* si le message a un suivant, on ajoute une ligne au fichier */
			if(cour->suivant != NULL) {
				fputc('\n', fichier);
			}
			/* on passe à l'élément suivant */
			cour = cour->suivant;
		}

		fclose(fichier); /* on pense à fermer le fichier */
	}
}

/**************************************************************************************************/
/*																								  */
/* suprRN		supprime les caractères de retour à la ligne en fin de chaine de caracteres		  */
/*																								  */
/* En entrée:	s une chaine de caracteres														  */
/*				taillemax la taille maximum de s (sans compter la fin de chaine '\0')			  */
/*																								  */
/* En sortie:	s sans '\r' ou '\n'																  */
/*																								  */
/**************************************************************************************************/

void suprRN(char* s, int tailleMax) {
	int i = 0;
	/* on cherche le premier caractere de retour à la ligne de la chaine de caracteres */
	while(i < tailleMax && (s[i] != '\n' && s[i] != '\r' && s[i] != '\0')) {
		i++;
	}
	/* on le remplace par un caractere de fin de chaine */
	s[i] = '\0';
}
