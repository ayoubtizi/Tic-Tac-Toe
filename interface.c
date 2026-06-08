#include "interface.h"
#include <stdlib.h>
#include <string.h>
#include <math.h>

Bouton boutons[10];
int nombre_boutons = 0;

void jouer_son(Jeu *jeu, int frequence, int duree) {
    if (!jeu->audio) return;
    
    int echantillons = (22050 * duree) / 1000;
    Sint16 *buffer = malloc(echantillons * sizeof(Sint16));
    
    for (int i = 0; i < echantillons; i++) {
        double t = (double)i / 22050;
        buffer[i] = (Sint16)(32767.0 * 0.3 * sin(2.0 * M_PI * frequence * t));
    }
    
    SDL_PutAudioStreamData(jeu->audio, buffer, echantillons * sizeof(Sint16));
    free(buffer);
}

void jouer_melodie(Jeu *jeu) {
    if (jeu->musique_jouee) return;
    
    int notes[] = {523, 587, 659, 784, 880, 784, 659, 587, 523};
    int durees[] = {150, 150, 150, 150, 300, 150, 150, 150, 300};
    
    for (int i = 0; i < 9; i++) {
        jouer_son(jeu, notes[i], durees[i]);
        if (i < 8) SDL_Delay(50);
    }
    
    jeu->musique_jouee = true;
}

void boutons_menu_principal() {
    nombre_boutons = 1;
    strcpy(boutons[0].texte, "JOUER");
    boutons[0].x = 200;
    boutons[0].y = 400;
    boutons[0].largeur = 200;
    boutons[0].hauteur = 60;
}

void boutons_grille() {
    nombre_boutons = 3;
    
    strcpy(boutons[0].texte, "GRILLE 3X3");
    boutons[0].x = 200;
    boutons[0].y = 250;
    boutons[0].largeur = 200;
    boutons[0].hauteur = 60;
    boutons[0].valeur = 3;
    
    strcpy(boutons[1].texte, "GRILLE 5X5");
    boutons[1].x = 200;
    boutons[1].y = 330;
    boutons[1].largeur = 200;
    boutons[1].hauteur = 60;
    boutons[1].valeur = 5;
    
    strcpy(boutons[2].texte, "GRILLE 7X7");
    boutons[2].x = 200;
    boutons[2].y = 410;
    boutons[2].largeur = 200;
    boutons[2].hauteur = 60;
    boutons[2].valeur = 7;
}

void boutons_mode() {
    nombre_boutons = 2;
    
    strcpy(boutons[0].texte, "2 JOUEURS");
    boutons[0].x = 150;
    boutons[0].y = 280;
    boutons[0].largeur = 300;
    boutons[0].hauteur = 60;
    boutons[0].valeur = DEUX_JOUEURS;
    
    strcpy(boutons[1].texte, "VS ORDINATEUR");
    boutons[1].x = 150;
    boutons[1].y = 360;
    boutons[1].largeur = 300;
    boutons[1].hauteur = 60;
    boutons[1].valeur = CONTRE_ORDI;
}

void boutons_difficulte() {
    nombre_boutons = 3;
    
    strcpy(boutons[0].texte, "FACILE");
    boutons[0].x = 200;
    boutons[0].y = 250;
    boutons[0].largeur = 200;
    boutons[0].hauteur = 60;
    boutons[0].valeur = FACILE;
    
    strcpy(boutons[1].texte, "MOYEN");
    boutons[1].x = 200;
    boutons[1].y = 330;
    boutons[1].largeur = 200;
    boutons[1].hauteur = 60;
    boutons[1].valeur = MOYEN;
    
    strcpy(boutons[2].texte, "DIFFICILE");
    boutons[2].x = 200;
    boutons[2].y = 410;
    boutons[2].largeur = 200;
    boutons[2].hauteur = 60;
    boutons[2].valeur = DIFFICILE;
}