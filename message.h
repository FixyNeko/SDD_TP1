#ifndef MESSAGE_H
#define MESSAGE_H

#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "listeChainee.h"

void AfficherMessagesValides(liste_t * liste);
int RecupererDateSysteme();
void SupprimerMessagesObsoletes(liste_t * liste);
void ModifierDateDebut(liste_t * liste, int DateInitiale, int NouvelleDate);
void MessagesContenantMotif(liste_t * liste, char * motif);
int ContientMotif(char * s, char * motif);

#endif // MESSAGE_H
