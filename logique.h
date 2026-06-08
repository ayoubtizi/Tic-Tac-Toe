#ifndef LOGIQUE_H
#define LOGIQUE_H

#include "types.h"

void creer_plateau(Jeu *jeu, int taille);
void nouvelle_partie(Jeu *jeu, int taille, int type);
int longueur_victoire(int taille);
int verifier_gagnant(Jeu *jeu);
bool plateau_plein(Jeu *jeu);

#endif // LOGIQUE_H