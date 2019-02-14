#ifndef DEF_FICHIER
#define DEF_FICHIER

#include <stdlib.h>
#include <string.h>
#include "listeChainee.h"

void LectureFichier(char * NomFichier, liste_t * liste);
void suprRN(char* s, int tailleMax);
void SauvegardeLCH(char * NomFichier, liste_t * liste);

#endif
