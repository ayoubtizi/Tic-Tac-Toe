#include <SDL3/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "types.h"
#include "graphique.h"
#include "interface.h"
#include "logique.h"
#include "ia.h"

void gerer_clic_menu(Jeu *jeu, int x, int y) {
    for (int i = 0; i < nombre_boutons; i++) {
        if (x >= boutons[i].x && x <= boutons[i].x + boutons[i].largeur &&
            y >= boutons[i].y && y <= boutons[i].y + boutons[i].hauteur) {
            
            jouer_son(jeu, 800, 100);
            
            if (jeu->mode == MENU_DEMARRAGE) {
                boutons_grille();
                jeu->mode = MENU_GRILLE;
            } else if (jeu->mode == MENU_GRILLE) {
                jeu->taille_grille = boutons[i].valeur;
                boutons_mode();
                jeu->mode = MENU_MODE;
            } else if (jeu->mode == MENU_MODE) {
                jeu->type_jeu = boutons[i].valeur;
                if (jeu->type_jeu == CONTRE_ORDI) {
                    boutons_difficulte();
                    jeu->mode = MENU_DIFFICULTE;
                } else {
                    nouvelle_partie(jeu, jeu->taille_grille, jeu->type_jeu);
                }
            } else if (jeu->mode == MENU_DIFFICULTE) {
                jeu->difficulte = boutons[i].valeur;
                nouvelle_partie(jeu, jeu->taille_grille, jeu->type_jeu);
            }
            return;
        }
    }
}

void gerer_clic_jeu(Jeu *jeu, int x, int y) {
    // Clic sur bouton menu
    if (y < ZONE_MENU && x >= LARGEUR - 110 && x <= LARGEUR - 10 &&
        y >= 10 && y <= 50) {
        jouer_son(jeu, 800, 100);
        boutons_menu_principal();
        jeu->mode = MENU_DEMARRAGE;
        return;
    }
    
    // Rejouer si jeu termine
    if (jeu->jeu_termine) {
        jouer_son(jeu, 800, 100);
        nouvelle_partie(jeu, jeu->taille_grille, jeu->type_jeu);
        return;
    }
    
    if (y < ZONE_MENU) return;
    
    int col = x / jeu->taille_case;
    int ligne = (y - ZONE_MENU) / jeu->taille_case;
    
    if (ligne >= 0 && ligne < jeu->taille_grille && col >= 0 && col < jeu->taille_grille) {
        if (jeu->plateau[ligne][col] == VIDE) {
            jouer_son(jeu, 600, 80);
            jeu->plateau[ligne][col] = jeu->joueur_actuel;
            
            int gagnant = verifier_gagnant(jeu);
            if (gagnant != VIDE) {
                jeu->jeu_termine = true;
                jeu->gagnant = gagnant;
                jouer_son(jeu, 1200, 300);
            } else if (plateau_plein(jeu)) {
                jeu->jeu_termine = true;
            } else {
                jeu->joueur_actuel = (jeu->joueur_actuel == JOUEUR_X) ? JOUEUR_O : JOUEUR_X;
                
                // Tour de l'ordinateur
                if (jeu->type_jeu == CONTRE_ORDI && jeu->joueur_actuel == JOUEUR_O && !jeu->jeu_termine) {
                    SDL_Delay(300);
                    
                    if (jeu->difficulte == FACILE) {
                        mouvement_ordi_facile(jeu);
                    } else if (jeu->difficulte == MOYEN) {
                        mouvement_ordi_intelligent(jeu);
                    } else {
                        mouvement_ordi_difficile(jeu);
                    }
                    
                    jouer_son(jeu, 600, 80);
                    
                    gagnant = verifier_gagnant(jeu);
                    if (gagnant != VIDE) {
                        jeu->jeu_termine = true;
                        jeu->gagnant = gagnant;
                        jouer_son(jeu, 1200, 300);
                    } else if (plateau_plein(jeu)) {
                        jeu->jeu_termine = true;
                    } else {
                        jeu->joueur_actuel = JOUEUR_X;
                    }
                }
            }
        }
    }
}

int main(int argc, char *argv[]) {
    srand(time(NULL));
    
    if (!SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO)) {
        printf("Erreur SDL_Init: %s\n", SDL_GetError());
        return 1;
    }
    
    Jeu jeu = {0};
    
    jeu.fenetre = SDL_CreateWindow("JEU MORPION", LARGEUR, HAUTEUR, 0);
    if (!jeu.fenetre) {
        printf("Erreur fenetre: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }
    
    jeu.rendu = SDL_CreateRenderer(jeu.fenetre, NULL);
    if (!jeu.rendu) {
        printf("Erreur rendu: %s\n", SDL_GetError());
        SDL_DestroyWindow(jeu.fenetre);
        SDL_Quit();
        return 1;
    }
    
    // Initialiser l'audio
    SDL_AudioSpec spec;
    spec.freq = 22050;
    spec.format = SDL_AUDIO_S16;
    spec.channels = 1;
    jeu.audio = SDL_OpenAudioDeviceStream(SDL_AUDIO_DEVICE_DEFAULT_PLAYBACK, &spec, NULL, NULL);
    if (jeu.audio) {
        SDL_ResumeAudioStreamDevice(jeu.audio);
        jouer_melodie(&jeu);
    }
    
    boutons_menu_principal();
    jeu.mode = MENU_DEMARRAGE;
    jeu.type_jeu = DEUX_JOUEURS;
    jeu.difficulte = MOYEN;
    jeu.taille_grille = 3;
    
    bool en_cours = true;
    SDL_Event evenement;
    
    while (en_cours) {
        while (SDL_PollEvent(&evenement)) {
            if (evenement.type == SDL_EVENT_QUIT) {
                en_cours = false;
            } else if (evenement.type == SDL_EVENT_MOUSE_MOTION) {
                jeu.souris_x = evenement.motion.x;
                jeu.souris_y = evenement.motion.y;
            } else if (evenement.type == SDL_EVENT_MOUSE_BUTTON_DOWN) {
                if (evenement.button.button == SDL_BUTTON_LEFT) {
                    if (jeu.mode == EN_JEU) {
                        gerer_clic_jeu(&jeu, evenement.button.x, evenement.button.y);
                    } else {
                        gerer_clic_menu(&jeu, evenement.button.x, evenement.button.y);
                    }
                }
            }
        }
        
        if (jeu.mode == EN_JEU) {
            dessiner_plateau(&jeu);
        } else if (jeu.mode == MENU_DEMARRAGE) {
            dessiner_ecran_demarrage(&jeu);
        } else if (jeu.mode == MENU_GRILLE) {
            dessiner_menu(&jeu, "CHOISIR LA GRILLE");
        } else if (jeu.mode == MENU_MODE) {
            dessiner_menu(&jeu, "MODE DE JEU");
        } else if (jeu.mode == MENU_DIFFICULTE) {
            dessiner_menu(&jeu, "DIFFICULTE");
        }
        
        SDL_Delay(16);
    }
    
    // Nettoyage
    if (jeu.plateau) {
        for (int i = 0; i < jeu.taille_grille; i++) {
            free(jeu.plateau[i]);
        }
        free(jeu.plateau);
    }
    
    if (jeu.audio) {
        SDL_DestroyAudioStream(jeu.audio);
    }
    
    SDL_DestroyRenderer(jeu.rendu);
    SDL_DestroyWindow(jeu.fenetre);
    SDL_Quit();
    
    return 0;
}