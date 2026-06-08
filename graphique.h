#ifndef GRAPHIQUE_H
#define GRAPHIQUE_H

#include "types.h"

extern unsigned char police[95][7];

void dessiner_texte(SDL_Renderer *rendu, char *texte, int x, int y, int taille);
void dessiner_grille(Jeu *jeu);
void dessiner_x(Jeu *jeu, int ligne, int col);
void dessiner_o(Jeu *jeu, int ligne, int col);
void dessiner_ligne_victoire(Jeu *jeu);
void dessiner_bouton(Jeu *jeu, Bouton *btn, bool survol);
void dessiner_ecran_demarrage(Jeu *jeu);
void dessiner_menu(Jeu *jeu, char *titre);
void dessiner_plateau(Jeu *jeu);

#endif // GRAPHIQUE_H