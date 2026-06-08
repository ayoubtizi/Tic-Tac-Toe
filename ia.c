#include "ia.h"
#include "logique.h"
#include <stdlib.h>

void mouvement_ordi_facile(Jeu *jeu) {
    int tentatives = 0;
    while (tentatives < 100) {
        int i = rand() % jeu->taille_grille;
        int j = rand() % jeu->taille_grille;
        if (jeu->plateau[i][j] == VIDE) {
            jeu->plateau[i][j] = JOUEUR_O;
            return;
        }
        tentatives++;
    }
}

void mouvement_ordi_intelligent(Jeu *jeu) {
    LigneVictoire temp = jeu->ligne_victoire;
    
    // Essayer de gagner
    for (int i = 0; i < jeu->taille_grille; i++) {
        for (int j = 0; j < jeu->taille_grille; j++) {
            if (jeu->plateau[i][j] == VIDE) {
                jeu->plateau[i][j] = JOUEUR_O;
                if (verifier_gagnant(jeu) == JOUEUR_O) {
                    jeu->ligne_victoire = temp;
                    return;
                }
                jeu->plateau[i][j] = VIDE;
                jeu->ligne_victoire = temp;
            }
        }
    }
    
    // Bloquer le joueur
    for (int i = 0; i < jeu->taille_grille; i++) {
        for (int j = 0; j < jeu->taille_grille; j++) {
            if (jeu->plateau[i][j] == VIDE) {
                jeu->plateau[i][j] = JOUEUR_X;
                if (verifier_gagnant(jeu) == JOUEUR_X) {
                    jeu->plateau[i][j] = JOUEUR_O;
                    jeu->ligne_victoire = temp;
                    return;
                }
                jeu->plateau[i][j] = VIDE;
                jeu->ligne_victoire = temp;
            }
        }
    }
    
    mouvement_ordi_facile(jeu);
}

int minimax(Jeu *jeu, int profondeur, bool maximiser, int alpha, int beta) {
    LigneVictoire temp = jeu->ligne_victoire;
    int gagnant = verifier_gagnant(jeu);
    jeu->ligne_victoire = temp;
    
    if (gagnant == JOUEUR_O) return 10 - profondeur;
    if (gagnant == JOUEUR_X) return profondeur - 10;
    if (plateau_plein(jeu)) return 0;
    if (profondeur > 4) return 0;
    
    if (maximiser) {
        int meilleur_score = -1000;
        for (int i = 0; i < jeu->taille_grille; i++) {
            for (int j = 0; j < jeu->taille_grille; j++) {
                if (jeu->plateau[i][j] == VIDE) {
                    jeu->plateau[i][j] = JOUEUR_O;
                    int score = minimax(jeu, profondeur + 1, false, alpha, beta);
                    jeu->plateau[i][j] = VIDE;
                    meilleur_score = (score > meilleur_score) ? score : meilleur_score;
                    alpha = (alpha > score) ? alpha : score;
                    if (beta <= alpha) return meilleur_score;
                }
            }
        }
        return meilleur_score;
    } else {
        int meilleur_score = 1000;
        for (int i = 0; i < jeu->taille_grille; i++) {
            for (int j = 0; j < jeu->taille_grille; j++) {
                if (jeu->plateau[i][j] == VIDE) {
                    jeu->plateau[i][j] = JOUEUR_X;
                    int score = minimax(jeu, profondeur + 1, true, alpha, beta);
                    jeu->plateau[i][j] = VIDE;
                    meilleur_score = (score < meilleur_score) ? score : meilleur_score;
                    beta = (beta < score) ? beta : score;
                    if (beta <= alpha) return meilleur_score;
                }
            }
        }
        return meilleur_score;
    }
}

void mouvement_ordi_difficile(Jeu *jeu) {
    if (jeu->taille_grille > 5) {
        mouvement_ordi_intelligent(jeu);
        return;
    }
    
    int meilleur_score = -1000;
    int meilleur_i = -1, meilleur_j = -1;
    
    for (int i = 0; i < jeu->taille_grille; i++) {
        for (int j = 0; j < jeu->taille_grille; j++) {
            if (jeu->plateau[i][j] == VIDE) {
                jeu->plateau[i][j] = JOUEUR_O;
                int score = minimax(jeu, 0, false, -1000, 1000);
                jeu->plateau[i][j] = VIDE;
                if (score > meilleur_score) {
                    meilleur_score = score;
                    meilleur_i = i;
                    meilleur_j = j;
                }
            }
        }
    }
    
    if (meilleur_i != -1 && meilleur_j != -1) {
        jeu->plateau[meilleur_i][meilleur_j] = JOUEUR_O;
    }
}