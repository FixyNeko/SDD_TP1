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
	FILE	*fichier;
	char	texte[TAILLE_TEXTE+1] = {0};
	int		LongueurTexte;
	message_t * message;

	fichier = fopen(NomFichier, "r");

	if(fichier != NULL) {
		while(0 == feof(fichier)) {
			message = (message_t *) malloc(sizeof(message_t));

			fscanf(fichier, "%d %d ", &(message->DebutValidite), &(message->FinValidite));
			fgets(texte, TAILLE_TEXTE, fichier);
			suprRN(texte, TAILLE_TEXTE);
			texte[TAILLE_TEXTE] = '\0';

			LongueurTexte = strlen(texte);

			message->texte = (char *) malloc((LongueurTexte+1) * sizeof(char));
			strcpy(message->texte, texte);

			InsertionApres(message, RecherchePrec(liste, message->DebutValidite));
		}

		fclose(fichier);
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
	FILE		* fichier = fopen(NomFichier, "w");
	message_t	* cour = liste->premier;

	if(fichier != NULL) {
		while(cour != NULL) {
			fprintf(fichier, "%d %d %s", cour->DebutValidite, cour->FinValidite, cour->texte);

			if(cour->suivant != NULL) {
				fputc('\n', fichier);
			}

			cour = cour->suivant;
		}

		fclose(fichier);
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
	
	while(i < tailleMax && (s[i] != '\n' && s[i] != '\r')) {
		i++;
	}
	s[i] = '\0';
}
