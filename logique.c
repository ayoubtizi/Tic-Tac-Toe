#include "logique.h"
#include <stdlib.h>

void creer_plateau(Jeu *jeu, int taille) {
    if (jeu->plateau) {
        for (int i = 0; i < jeu->taille_grille; i++) {
            free(jeu->plateau[i]);
        }
        free(jeu->plateau);
    }
    
    jeu->taille_grille = taille;
    jeu->taille_case = LARGEUR / taille;
    jeu->plateau = malloc(taille * sizeof(int*));
    
    for (int i = 0; i < taille; i++) {
        jeu->plateau[i] = malloc(taille * sizeof(int));
        for (int j = 0; j < taille; j++) {
            jeu->plateau[i][j] = VIDE;
        }
    }
}

void nouvelle_partie(Jeu *jeu, int taille, int type) {
    creer_plateau(jeu, taille);
    jeu->joueur_actuel = JOUEUR_X;
    jeu->jeu_termine = false;
    jeu->gagnant = VIDE;
    jeu->mode = EN_JEU;
    jeu->type_jeu = type;
    jeu->ligne_victoire.existe = false;
}

int longueur_victoire(int taille) {
    if (taille == 3) return 3;
    if (taille == 5) return 4;
    return 5;
}

int verifier_gagnant(Jeu *jeu) {
    int long_vic = longueur_victoire(jeu->taille_grille);
    
    // Verifier horizontal
    for (int i = 0; i < jeu->taille_grille; i++) {
        for (int j = 0; j <= jeu->taille_grille - long_vic; j++) {
            int premier = jeu->plateau[i][j];
            if (premier == VIDE) continue;
            
            bool victoire = true;
            for (int k = 1; k < long_vic; k++) {
                if (jeu->plateau[i][j+k] != premier) {
                    victoire = false;
                    break;
                }
            }
            
            if (victoire) {
                jeu->ligne_victoire.ligne_debut = i;
                jeu->ligne_victoire.col_debut = j;
                jeu->ligne_victoire.ligne_fin = i;
                jeu->ligne_victoire.col_fin = j + long_vic - 1;
                jeu->ligne_victoire.existe = true;
                return premier;
            }
        }
    }
    
    // Verifier vertical
    for (int j = 0; j < jeu->taille_grille; j++) {
        for (int i = 0; i <= jeu->taille_grille - long_vic; i++) {
            int premier = jeu->plateau[i][j];
            if (premier == VIDE) continue;
            
            bool victoire = true;
            for (int k = 1; k < long_vic; k++) {
                if (jeu->plateau[i+k][j] != premier) {
                    victoire = false;
                    break;
                }
            }
            
            if (victoire) {
                jeu->ligne_victoire.ligne_debut = i;
                jeu->ligne_victoire.col_debut = j;
                jeu->ligne_victoire.ligne_fin = i + long_vic - 1;
                jeu->ligne_victoire.col_fin = j;
                jeu->ligne_victoire.existe = true;
                return premier;
            }
        }
    }
    
    // Verifier diagonale
    for (int i = 0; i <= jeu->taille_grille - long_vic; i++) {
        for (int j = 0; j <= jeu->taille_grille - long_vic; j++) {
            int premier = jeu->plateau[i][j];
            if (premier == VIDE) continue;
            
            bool victoire = true;
            for (int k = 1; k < long_vic; k++) {
                if (jeu->plateau[i+k][j+k] != premier) {
                    victoire = false;
                    break;
                }
            }
            
            if (victoire) {
                jeu->ligne_victoire.ligne_debut = i;
                jeu->ligne_victoire.col_debut = j;
                jeu->ligne_victoire.ligne_fin = i + long_vic - 1;
                jeu->ligne_victoire.col_fin = j + long_vic - 1;
                jeu->ligne_victoire.existe = true;
                return premier;
            }
        }
    }
    
    // Verifier anti-diagonale
    for (int i = long_vic - 1; i < jeu->taille_grille; i++) {
        for (int j = 0; j <= jeu->taille_grille - long_vic; j++) {
            int premier = jeu->plateau[i][j];
            if (premier == VIDE) continue;
            
            bool victoire = true;
            for (int k = 1; k < long_vic; k++) {
                if (jeu->plateau[i-k][j+k] != premier) {
                    victoire = false;
                    break;
                }
            }
            
            if (victoire) {
                jeu->ligne_victoire.ligne_debut = i;
                jeu->ligne_victoire.col_debut = j;
                jeu->ligne_victoire.ligne_fin = i - long_vic + 1;
                jeu->ligne_victoire.col_fin = j + long_vic - 1;
                jeu->ligne_victoire.existe = true;
                return premier;
            }
        }
    }
    
    return VIDE;
}

bool plateau_plein(Jeu *jeu) {
    for (int i = 0; i < jeu->taille_grille; i++) {
        for (int j = 0; j < jeu->taille_grille; j++) {
            if (jeu->plateau[i][j] == VIDE) {
                return false;
            }
        }
    }
    return true;
}