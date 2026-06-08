#include "graphique.h"
#include <string.h>
#include <math.h>

// Police bitmap simple
unsigned char police[95][7] = {
    {0x00,0x00,0x00,0x00,0x00,0x00,0x00}, {0x04,0x04,0x04,0x04,0x00,0x04,0x00},
    {0x0A,0x0A,0x0A,0x00,0x00,0x00,0x00}, {0x0A,0x1F,0x0A,0x1F,0x0A,0x00,0x00},
    {0x04,0x0F,0x14,0x0E,0x05,0x1E,0x04}, {0x18,0x19,0x02,0x04,0x08,0x13,0x03},
    {0x0C,0x12,0x14,0x08,0x15,0x12,0x0D}, {0x0C,0x04,0x08,0x00,0x00,0x00,0x00},
    {0x02,0x04,0x08,0x08,0x08,0x04,0x02}, {0x08,0x04,0x02,0x02,0x02,0x04,0x08},
    {0x00,0x04,0x15,0x0E,0x15,0x04,0x00}, {0x00,0x04,0x04,0x1F,0x04,0x04,0x00},
    {0x00,0x00,0x00,0x00,0x0C,0x04,0x08}, {0x00,0x00,0x00,0x1F,0x00,0x00,0x00},
    {0x00,0x00,0x00,0x00,0x00,0x0C,0x0C}, {0x00,0x01,0x02,0x04,0x08,0x10,0x00},
    {0x0E,0x11,0x13,0x15,0x19,0x11,0x0E}, {0x04,0x0C,0x04,0x04,0x04,0x04,0x0E},
    {0x0E,0x11,0x01,0x02,0x04,0x08,0x1F}, {0x1F,0x02,0x04,0x02,0x01,0x11,0x0E},
    {0x02,0x06,0x0A,0x12,0x1F,0x02,0x02}, {0x1F,0x10,0x1E,0x01,0x01,0x11,0x0E},
    {0x06,0x08,0x10,0x1E,0x11,0x11,0x0E}, {0x1F,0x01,0x02,0x04,0x08,0x08,0x08},
    {0x0E,0x11,0x11,0x0E,0x11,0x11,0x0E}, {0x0E,0x11,0x11,0x0F,0x01,0x02,0x0C},
    {0x00,0x0C,0x0C,0x00,0x0C,0x0C,0x00}, {0x00,0x0C,0x0C,0x00,0x0C,0x04,0x08},
    {0x02,0x04,0x08,0x10,0x08,0x04,0x02}, {0x00,0x00,0x1F,0x00,0x1F,0x00,0x00},
    {0x08,0x04,0x02,0x01,0x02,0x04,0x08}, {0x0E,0x11,0x01,0x02,0x04,0x00,0x04},
    {0x0E,0x11,0x01,0x0D,0x15,0x15,0x0E}, {0x0E,0x11,0x11,0x11,0x1F,0x11,0x11},
    {0x1E,0x11,0x11,0x1E,0x11,0x11,0x1E}, {0x0E,0x11,0x10,0x10,0x10,0x11,0x0E},
    {0x1C,0x12,0x11,0x11,0x11,0x12,0x1C}, {0x1F,0x10,0x10,0x1E,0x10,0x10,0x1F},
    {0x1F,0x10,0x10,0x1E,0x10,0x10,0x10}, {0x0E,0x11,0x10,0x17,0x11,0x11,0x0F},
    {0x11,0x11,0x11,0x1F,0x11,0x11,0x11}, {0x0E,0x04,0x04,0x04,0x04,0x04,0x0E},
    {0x07,0x02,0x02,0x02,0x02,0x12,0x0C}, {0x11,0x12,0x14,0x18,0x14,0x12,0x11},
    {0x10,0x10,0x10,0x10,0x10,0x10,0x1F}, {0x11,0x1B,0x15,0x15,0x11,0x11,0x11},
    {0x11,0x11,0x19,0x15,0x13,0x11,0x11}, {0x0E,0x11,0x11,0x11,0x11,0x11,0x0E},
    {0x1E,0x11,0x11,0x1E,0x10,0x10,0x10}, {0x0E,0x11,0x11,0x11,0x15,0x12,0x0D},
    {0x1E,0x11,0x11,0x1E,0x14,0x12,0x11}, {0x0F,0x10,0x10,0x0E,0x01,0x01,0x1E},
    {0x1F,0x04,0x04,0x04,0x04,0x04,0x04}, {0x11,0x11,0x11,0x11,0x11,0x11,0x0E},
    {0x11,0x11,0x11,0x11,0x11,0x0A,0x04}, {0x11,0x11,0x11,0x15,0x15,0x15,0x0A},
    {0x11,0x11,0x0A,0x04,0x0A,0x11,0x11}, {0x11,0x11,0x11,0x0A,0x04,0x04,0x04},
    {0x1F,0x01,0x02,0x04,0x08,0x10,0x1F}
};

void dessiner_texte(SDL_Renderer *rendu, char *texte, int x, int y, int taille) {
    int pos_x = 0;
    for (int i = 0; texte[i] != '\0'; i++) {
        char c = texte[i];
        if (c < 32 || c > 126) continue;
        
        int idx = c - 32;
        for (int ligne = 0; ligne < 7; ligne++) {
            for (int col = 0; col < 5; col++) {
                if (police[idx][ligne] & (1 << (4 - col))) {
                    SDL_FRect rect = {x + pos_x + col * taille, y + ligne * taille, taille, taille};
                    SDL_RenderFillRect(rendu, &rect);
                }
            }
        }
        pos_x += 6 * taille;
    }
}

void dessiner_grille(Jeu *jeu) {
    SDL_SetRenderDrawColor(jeu->rendu, GRILLE_R, GRILLE_G, GRILLE_B, 255);
    
    for (int i = 1; i < jeu->taille_grille; i++) {
        SDL_RenderLine(jeu->rendu, i * jeu->taille_case, ZONE_MENU, 
                      i * jeu->taille_case, HAUTEUR);
        SDL_RenderLine(jeu->rendu, i * jeu->taille_case + 1, ZONE_MENU, 
                      i * jeu->taille_case + 1, HAUTEUR);
    }
    
    for (int i = 1; i < jeu->taille_grille; i++) {
        SDL_RenderLine(jeu->rendu, 0, ZONE_MENU + i * jeu->taille_case, 
                      LARGEUR, ZONE_MENU + i * jeu->taille_case);
        SDL_RenderLine(jeu->rendu, 0, ZONE_MENU + i * jeu->taille_case + 1, 
                      LARGEUR, ZONE_MENU + i * jeu->taille_case + 1);
    }
}

void dessiner_x(Jeu *jeu, int ligne, int col) {
    int x = col * jeu->taille_case;
    int y = ZONE_MENU + ligne * jeu->taille_case;
    int marge = jeu->taille_case / 5;
    
    SDL_SetRenderDrawColor(jeu->rendu, X_R, X_G, X_B, 255);
    
    for (int i = 0; i < 6; i++) {
        SDL_RenderLine(jeu->rendu, x + marge + i, y + marge,
                      x + jeu->taille_case - marge + i, y + jeu->taille_case - marge);
        SDL_RenderLine(jeu->rendu, x + marge + i, y + jeu->taille_case - marge,
                      x + jeu->taille_case - marge + i, y + marge);
    }
}

void dessiner_o(Jeu *jeu, int ligne, int col) {
    int centre_x = col * jeu->taille_case + jeu->taille_case / 2;
    int centre_y = ZONE_MENU + ligne * jeu->taille_case + jeu->taille_case / 2;
    int rayon = jeu->taille_case / 2 - jeu->taille_case / 5;
    
    SDL_SetRenderDrawColor(jeu->rendu, O_R, O_G, O_B, 255);
    
    for (int epaisseur = 0; epaisseur < 6; epaisseur++) {
        int r = rayon - epaisseur;
        for (int angle = 0; angle < 360; angle++) {
            int x = centre_x + r * cos(angle * M_PI / 180);
            int y = centre_y + r * sin(angle * M_PI / 180);
            SDL_RenderPoint(jeu->rendu, x, y);
        }
    }
}

void dessiner_ligne_victoire(Jeu *jeu) {
    if (!jeu->ligne_victoire.existe) return;
    
    int debut_x = jeu->ligne_victoire.col_debut * jeu->taille_case + jeu->taille_case / 2;
    int debut_y = ZONE_MENU + jeu->ligne_victoire.ligne_debut * jeu->taille_case + jeu->taille_case / 2;
    int fin_x = jeu->ligne_victoire.col_fin * jeu->taille_case + jeu->taille_case / 2;
    int fin_y = ZONE_MENU + jeu->ligne_victoire.ligne_fin * jeu->taille_case + jeu->taille_case / 2;
    
    SDL_SetRenderDrawColor(jeu->rendu, VICTOIRE_R, VICTOIRE_G, VICTOIRE_B, 255);
    
    for (int i = 0; i < 8; i++) {
        SDL_RenderLine(jeu->rendu, debut_x + i - 4, debut_y, fin_x + i - 4, fin_y);
    }
}

void dessiner_bouton(Jeu *jeu, Bouton *btn, bool survol) {
    if (survol) {
        SDL_SetRenderDrawColor(jeu->rendu, BOUTON_SURVOL_R, BOUTON_SURVOL_G, BOUTON_SURVOL_B, 255);
    } else {
        SDL_SetRenderDrawColor(jeu->rendu, BOUTON_R, BOUTON_G, BOUTON_B, 255);
    }
    
    SDL_FRect rect = {btn->x, btn->y, btn->largeur, btn->hauteur};
    SDL_RenderFillRect(jeu->rendu, &rect);
    
    SDL_SetRenderDrawColor(jeu->rendu, BORDURE_R, BORDURE_G, BORDURE_B, 255);
    SDL_RenderRect(jeu->rendu, &rect);
    SDL_FRect rect2 = {btn->x + 1, btn->y + 1, btn->largeur - 2, btn->hauteur - 2};
    SDL_RenderRect(jeu->rendu, &rect2);
    
    SDL_SetRenderDrawColor(jeu->rendu, TEXTE_R, TEXTE_G, TEXTE_B, 255);
    int largeur_texte = strlen(btn->texte) * 6 * 2;
    int x_texte = btn->x + (btn->largeur - largeur_texte) / 2;
    int y_texte = btn->y + (btn->hauteur - 14) / 2;
    dessiner_texte(jeu->rendu, btn->texte, x_texte, y_texte, 2);
}

void dessiner_ecran_demarrage(Jeu *jeu) {
    SDL_SetRenderDrawColor(jeu->rendu, FOND_R, FOND_G, FOND_B, 255);
    SDL_RenderClear(jeu->rendu);
    
    SDL_SetRenderDrawColor(jeu->rendu, TITRE_R, TITRE_G, TITRE_B, 255);
    char titre[] = "MORPION";
    int largeur_titre = strlen(titre) * 6 * 8;
    int x_titre = (LARGEUR - largeur_titre) / 2;
    dessiner_texte(jeu->rendu, titre, x_titre, 150, 8);
    
    bool survol = (jeu->souris_x >= boutons[0].x && jeu->souris_x <= boutons[0].x + boutons[0].largeur &&
                   jeu->souris_y >= boutons[0].y && jeu->souris_y <= boutons[0].y + boutons[0].hauteur);
    dessiner_bouton(jeu, &boutons[0], survol);
    
    SDL_RenderPresent(jeu->rendu);
}

void dessiner_menu(Jeu *jeu, char *titre) {
    SDL_SetRenderDrawColor(jeu->rendu, FOND_R, FOND_G, FOND_B, 255);
    SDL_RenderClear(jeu->rendu);
    
    SDL_SetRenderDrawColor(jeu->rendu, TITRE_R, TITRE_G, TITRE_B, 255);
    int largeur_titre = strlen(titre) * 6 * 4;
    int x_titre = (LARGEUR - largeur_titre) / 2;
    dessiner_texte(jeu->rendu, titre, x_titre, 120, 4);
    
    for (int i = 0; i < nombre_boutons; i++) {
        bool survol = (jeu->souris_x >= boutons[i].x && jeu->souris_x <= boutons[i].x + boutons[i].largeur &&
                       jeu->souris_y >= boutons[i].y && jeu->souris_y <= boutons[i].y + boutons[i].hauteur);
        dessiner_bouton(jeu, &boutons[i], survol);
    }
    
    SDL_RenderPresent(jeu->rendu);
}

void dessiner_plateau(Jeu *jeu) {
    // Zone menu
    SDL_SetRenderDrawColor(jeu->rendu, MENU_R, MENU_G, MENU_B, 255);
    SDL_FRect zone_menu = {0, 0, LARGEUR, ZONE_MENU};
    SDL_RenderFillRect(jeu->rendu, &zone_menu);
    
    // Bouton menu
    Bouton btn_menu = {LARGEUR - 110, 10, 100, 40, "MENU"};
    dessiner_bouton(jeu, &btn_menu, false);
    
    // Afficher difficulte si contre ordi
    if (jeu->type_jeu == CONTRE_ORDI) {
        SDL_SetRenderDrawColor(jeu->rendu, TEXTE_R, TEXTE_G, TEXTE_B, 255);
        char texte_diff[20];
        if (jeu->difficulte == FACILE) strcpy(texte_diff, "IA: FACILE");
        else if (jeu->difficulte == MOYEN) strcpy(texte_diff, "IA: MOYEN");
        else strcpy(texte_diff, "IA: DIFFICILE");
        dessiner_texte(jeu->rendu, texte_diff, 10, 10, 2);
    }
    
    // Zone de jeu
    SDL_SetRenderDrawColor(jeu->rendu, FOND_R, FOND_G, FOND_B, 255);
    SDL_FRect zone_jeu = {0, ZONE_MENU, LARGEUR, HAUTEUR - ZONE_MENU};
    SDL_RenderFillRect(jeu->rendu, &zone_jeu);
    
    dessiner_grille(jeu);
    
    // Dessiner les X et O
    for (int i = 0; i < jeu->taille_grille; i++) {
        for (int j = 0; j < jeu->taille_grille; j++) {
            if (jeu->plateau[i][j] == JOUEUR_X) {
                dessiner_x(jeu, i, j);
            } else if (jeu->plateau[i][j] == JOUEUR_O) {
                dessiner_o(jeu, i, j);
            }
        }
    }
    
    dessiner_ligne_victoire(jeu);
    
    // Message de fin de jeu
    if (jeu->jeu_termine) {
        SDL_SetRenderDrawColor(jeu->rendu, FOND_R, FOND_G, FOND_B, 240);
        SDL_FRect fond_msg = {LARGEUR/6, HAUTEUR/2 - 70, LARGEUR*2/3, 120};
        SDL_RenderFillRect(jeu->rendu, &fond_msg);
        
        SDL_SetRenderDrawColor(jeu->rendu, O_R, O_G, O_B, 255);
        SDL_RenderRect(jeu->rendu, &fond_msg);
        
        char message[50];
        if (jeu->gagnant == JOUEUR_X) {
            strcpy(message, "JOUEUR 'X' A GAGNE!");
            SDL_SetRenderDrawColor(jeu->rendu, X_R, X_G, X_B, 255);
        } else if (jeu->gagnant == JOUEUR_O) {
            if (jeu->type_jeu == CONTRE_ORDI) {
                strcpy(message, "ORDINATEUR A GAGNE!");
            } else {
                strcpy(message, "JOUEUR 'O' A GAGNE!");
            }
            SDL_SetRenderDrawColor(jeu->rendu, O_R, O_G, O_B, 255);
        } else {
            strcpy(message, "MATCH NUL!");
            SDL_SetRenderDrawColor(jeu->rendu, TEXTE_R, TEXTE_G, TEXTE_B, 255);
        }
        
        int largeur_msg = strlen(message) * 6 * 3;
        int x_msg = LARGEUR/2 - largeur_msg/2;
        int y_msg = HAUTEUR/2 - 30;
        dessiner_texte(jeu->rendu, message, x_msg, y_msg, 3);
        
        SDL_SetRenderDrawColor(jeu->rendu, TEXTE_R, TEXTE_G, TEXTE_B, 255);
        char rejouer[] = "CLIQUEZ POUR JOUER A NOUVEAU";
        int largeur_rejouer = strlen(rejouer) * 6 * 2;
        int x_rejouer = LARGEUR/2 - largeur_rejouer/2;
        dessiner_texte(jeu->rendu, rejouer, x_rejouer, y_msg + 35, 2);
    }
    
    SDL_RenderPresent(jeu->rendu);
}