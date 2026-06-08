#ifndef INTERFACE_H
#define INTERFACE_H

#include "types.h"

// Fonctions audio
void jouer_son(Jeu *jeu, int frequence, int duree);
void jouer_melodie(Jeu *jeu);

// Fonctions boutons/menus
void boutons_menu_principal(void);
void boutons_grille(void);
void boutons_mode(void);
void boutons_difficulte(void);

#endif // INTERFACE_H