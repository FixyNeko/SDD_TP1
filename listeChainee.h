#ifndef DEF_LISTECHAINEE
#define DEF_LISTECHAINEE

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>

#define TAILLE_TEXTE 100
#define TAILLE_DATE 9

typedef struct message {
	int DebutValidite;
	int FinValidite;
	char * texte;
	struct message * suivant;
} message_t;

typedef struct liste {
	struct message * premier;
} liste_t;


void InitLCH(liste_t * liste);
message_t * CreerCellule(int DebutValidite, int FinValidite, char * texte);
void InsertionApres(message_t * message, message_t ** prec);
message_t ** RecherchePrec(liste_t * liste, int valeur);
void SupprimerCellule(message_t ** prec);
void ParcoursLCH(liste_t * liste);
void AfficherMessagesValides(liste_t * liste);
int RecupererDateSysteme();
void SupprimerMessagesObsoletes(liste_t * liste);
void ModifierDateDebut(liste_t * liste, int DateInitiale, int NouvelleDate);
void MessagesContenantMotif(liste_t * liste, char * motif);
int ContientMotif(char * s, char * motif);

#endif
