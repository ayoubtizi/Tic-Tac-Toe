#ifndef TYPES_H
#define TYPES_H

#include <SDL3/SDL.h>
#include <stdbool.h>

// Dimensions
#define LARGEUR 600
#define HAUTEUR 700
#define ZONE_MENU 100

// Couleurs theme neon
#define FOND_R 26
#define FOND_G 29
#define FOND_B 41

#define MENU_R 37
#define MENU_G 40
#define MENU_B 54

#define GRILLE_R 107
#define GRILLE_G 114
#define GRILLE_B 128

#define X_R 99
#define X_G 242
#define X_B 193

#define O_R 255
#define O_G 107
#define O_B 157

#define VICTOIRE_R 255
#define VICTOIRE_G 217
#define VICTOIRE_B 61

#define BOUTON_R 61
#define BOUTON_G 64
#define BOUTON_B 81

#define BOUTON_SURVOL_R 74
#define BOUTON_SURVOL_G 80
#define BOUTON_SURVOL_B 96

#define BORDURE_R 99
#define BORDURE_G 242
#define BORDURE_B 193

#define TITRE_R 99
#define TITRE_G 242
#define TITRE_B 193

#define TEXTE_R 229
#define TEXTE_G 231
#define TEXTE_B 235

// Etats
#define VIDE 0
#define JOUEUR_X 1
#define JOUEUR_O 2

// Modes
#define MENU_DEMARRAGE 0
#define MENU_GRILLE 1
#define MENU_MODE 2
#define MENU_DIFFICULTE 3
#define EN_JEU 4

// Types de jeu
#define DEUX_JOUEURS 0
#define CONTRE_ORDI 1

// Difficultes
#define FACILE 0
#define MOYEN 1
#define DIFFICILE 2

// Structure pour stocker la ligne de victoire
typedef struct {
    int ligne_debut, col_debut;
    int ligne_fin, col_fin;
    bool existe;
} LigneVictoire;

// Structure principale du jeu
typedef struct {
    SDL_Window *fenetre;
    SDL_Renderer *rendu;
    SDL_AudioStream *audio;
    int **plateau;
    int taille_grille;
    int taille_case;
    int joueur_actuel;
    bool jeu_termine;
    int gagnant;
    int mode;
    int type_jeu;
    int difficulte;
    LigneVictoire ligne_victoire;
    int souris_x;
    int souris_y;
    bool musique_jouee;
} Jeu;

// Structure pour les boutons
typedef struct {
    int x, y, largeur, hauteur;
    char texte[50];
    int valeur;
} Bouton;

// Variables globales
extern Bouton boutons[10];
extern int nombre_boutons;

#endif // TYPES_H