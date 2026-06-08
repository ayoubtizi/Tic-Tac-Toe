#ifndef IA_H
#define IA_H

#include "types.h"

void mouvement_ordi_facile(Jeu *jeu);
void mouvement_ordi_intelligent(Jeu *jeu);
void mouvement_ordi_difficile(Jeu *jeu);
int minimax(Jeu *jeu, int profondeur, bool maximiser, int alpha, int beta);

#endif // IA_H