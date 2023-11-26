#include <stdio.h>
#include <string.h>
#include <conio.h>
#include <windows.h>
#include <time.h>


char traduction_bloc(int number) {
    if (number == 0) {return ' ';}
    if (number == 1) {return 0x01;} // bloc cassable
    if (number == 2) {return 0x1A;} // le bloc poussable à déplacement
    if (number == 3) {return 0x05;} // le bloc piégé
    if (number == 4) {return 0x0F;} // bloc invincible
    if (number == 5) {return 0x1E;} // bloc disparition/apparition
    if (number == 6) {return 0x16;} // bloc à pousser case par case
    if (number == 7) {return 0x01;} // Snoopy
    if (number == 8) {return 0x0B;} // balle
    if (number == 9) {return 0x0E;} // oiseau
    if (number == 10) {return 0x7F;} // teleporteur
    if (number == 11) {return 0xB2;} // mur normal
    printf("Caractere inconnu");
    return 'E';
}

// Affichage des bordures de temps et du terrain
void affichage_jeu_et_temps(int plateau_de_jeu[][20], int lignes, int colonnes, int plateau_de_temps[30][30], int lignestemps, int colonnestemps) {
    // Afficher la bordure de temps supérieure

    for (int c = 0; c < colonnestemps; c++) {
        printf("%c", traduction_bloc(plateau_de_temps[0][c]));
    }
    printf("\n");

    // Afficher le terrain de jeu avec les bordures de temps latérales
    for (int l = 0; l < lignes; l++) {
        // Bordure de temps gauche
        printf("%c", traduction_bloc(plateau_de_temps[l][0]));

        // Terrain de jeu
        for (int c = 0; c < colonnes; c++) {
            printf("%c", traduction_bloc(plateau_de_jeu[l][c]));
        }

        // Bordure de temps droite
        printf("%c\n", traduction_bloc(plateau_de_temps[l][colonnestemps - 1]));
    }

    // Afficher la bordure de temps inférieure
    for (int c = 0; c < colonnestemps; c++) {
        printf("%c", traduction_bloc(plateau_de_temps[lignestemps - 1][c]));
    }
    printf("\n");
}

void deplacement_snoopy(int position_snoopy[2], int terrain[][20]) {
    int input = getch();
    if (input == 'd' || input == 'D') position_snoopy[1] += 1;
    if (input == 's' || input == 'S') position_snoopy[0] += 1;
    if (input == 'q' || input == 'Q') position_snoopy[1] -= 1;
    if (input == 'z' || input == 'Z') position_snoopy[0] -= 1;
}

void init_terrain_niveau_3(int plateau_de_jeu[][20], int position_snoopy[2]) {
    int lignes = 10;
    int colonnes = 20;
    plateau_de_jeu[0][0] = 9;
    plateau_de_jeu[0][colonnes - 1] = 9;
    plateau_de_jeu[lignes - 1][0] = 9;
    plateau_de_jeu[lignes - 1][colonnes - 1] = 9;
    int largeur = 3;
    for(int c = position_snoopy[1] - largeur; c <= position_snoopy[1] + largeur; c++) {
        plateau_de_jeu[position_snoopy[0] + largeur][c] = 11;
        plateau_de_jeu[position_snoopy[0] - largeur][c] = 11;
    }
    for(int l = position_snoopy[0] - largeur; l <= position_snoopy[0] + largeur; l++) {
        plateau_de_jeu[l][position_snoopy[1] + largeur] = 11;
        plateau_de_jeu[l][position_snoopy[1] - largeur] = 11;
    }
    plateau_de_jeu[position_snoopy[0] - 2][position_snoopy[1] + 2] = 10;
}

int deplacement_correcte(int lignestemps,int colonnestemps,int position_snoopy[2], int plateau_de_jeu[][20], int plateau_de_temps[30][30]) {
    int lignes = 10;
    int colonnes = 20;
    if (plateau_de_jeu[position_snoopy[0]][position_snoopy[1]] == 11) {
        affichage_jeu_et_temps(plateau_de_jeu, lignes, colonnes, plateau_de_temps, lignestemps, colonnestemps);
        printf("Snoopy ne peut pas avancer dans ce sens car il y a un mur\n");
        return 0;
    }
    if (position_snoopy[0] < 0 || position_snoopy[1] < 0 || position_snoopy[1] > colonnes - 1 || position_snoopy[0] > lignes - 1) {
        affichage_jeu_et_temps(plateau_de_jeu, lignes, colonnes, plateau_de_temps, lignestemps, colonnestemps);
        printf("Vous sortez du terrain\n");
        return 0;
    }
    if (plateau_de_jeu[position_snoopy[0]][position_snoopy[1]] == 10) {
        affichage_jeu_et_temps(plateau_de_jeu, lignes, colonnes, plateau_de_temps, lignestemps, colonnestemps);
        printf("Vous avez trouvé un téléporteur\n");
        position_snoopy[1] += 3;
        return 1;
    }
    if (plateau_de_jeu[position_snoopy[0]][position_snoopy[1]] == 0) {
        affichage_jeu_et_temps(plateau_de_jeu, lignes, colonnes, plateau_de_temps, lignestemps, colonnestemps);
        return 1;
    }
    if (plateau_de_jeu[position_snoopy[0]][position_snoopy[1]] == 9) {
        plateau_de_jeu[position_snoopy[0]][position_snoopy[1]] = 0;
        affichage_jeu_et_temps(plateau_de_jeu, lignes, colonnes, plateau_de_temps, lignestemps, colonnestemps);
        printf("Vous avez ramassé un oiseau \n");
        return 1;
    }
}

void mettreAJourBalle(int *positionBalleX, int *positionBalleY, int *directionX, int *directionY, int plateau_de_jeu[][20]) {
    int lignes = 10;
    int colonnes = 20;
    // Sauvegarder l'ancienne position de la balle
    int ancienX = *positionBalleX, ancienY = *positionBalleY;

    // Calculer la nouvelle position de la balle
    int suivantX = *positionBalleX + *directionX;
    int suivantY = *positionBalleY + *directionY;

    // Vérifier si la balle rencontre un mur normal ou un oiseau sur l'axe X
    if (suivantX < 0 || suivantX >= colonnes || plateau_de_jeu[*positionBalleY][suivantX] == 11 || plateau_de_jeu[*positionBalleY][suivantX] == 9) {
        *directionX *= -1;
    } else {
        *positionBalleX = suivantX;
    }

    // Vérifier si la balle rencontre un mur normal ou un oiseau sur l'axe Y
    if (suivantY < 0 || suivantY >= lignes || plateau_de_jeu[suivantY][*positionBalleX] == 11 || plateau_de_jeu[suivantY][*positionBalleX] == 9) {
        *directionY *= -1;
    } else {
        *positionBalleY = suivantY;
    }

    // Effacer l'ancienne position de la balle si elle ne contenait ni un oiseau ni Snoopy
    if (plateau_de_jeu[ancienY][ancienX] != 9 && plateau_de_jeu[ancienY][ancienX] != 7) {
        plateau_de_jeu[ancienY][ancienX] = 0;
    }

    // Vérification de la collision avec Snoopy
    if (plateau_de_jeu[*positionBalleY][*positionBalleX] == 7) {
        printf("Snoopy est touché par la balle!\n");
        // Logique de fin de jeu ou de perte de vie
    }

    // Mise à jour de la position de la balle sur le plateau
    if (plateau_de_jeu[*positionBalleY][*positionBalleX] != 9 && plateau_de_jeu[*positionBalleY][*positionBalleX] != 7) {
        plateau_de_jeu[*positionBalleY][*positionBalleX] = 8;
    }
}


void init_temps_terrain(int plateau_de_temps[30][30], int lignestemps, int colonnestemps) {

    int c;
    int l;
    for(c =0 ; c < colonnestemps; c++) {
        plateau_de_temps[0][c] = 0;
        plateau_de_temps[lignestemps-1][c] = 0;
    }
    for( l = 0 ; l < lignestemps ; l++) {
        plateau_de_temps[l][0] = 0;
        plateau_de_temps[l][colonnestemps-1] = 0;
    }
}
void init_temps_bordure(int plateau_de_temps[30][30], int lignestemps, int colonnestemps) {
    int c;
    int l;
    for(c =0 ; c < colonnestemps; c++) {
        plateau_de_temps[0][c] = 11;
        plateau_de_temps[lignestemps-1][c] = 11;
    }
    for( l = 0 ; l < colonnestemps ; l++) {
        plateau_de_temps[l][0] = 11;
        plateau_de_temps[l][colonnestemps-1] = 11;
    }
}

void defaite(int plateau_de_temps[30][30], int lignestemps, int colonnestemps, int *caseSupprimer) {
    int totalBordures = (30 + 30-1) * 2;
    int position = *caseSupprimer % totalBordures;

    if (position < colonnestemps) {
        plateau_de_temps[0][position] = 0;
    } else if (position < colonnestemps + lignestemps - 2) {
        plateau_de_temps[position - colonnestemps + 1][colonnestemps - 1] = 0;
    } else if (position < 2 * colonnestemps + lignestemps - 3) {
        plateau_de_temps[lignestemps - 1][2 * colonnestemps + lignestemps - 4 - position] = 0;
    } else {
        plateau_de_temps[2 * (lignestemps + colonnestemps) - 6 - position][0] = 0;
    }

    *caseSupprimer += 1;
}
void initCompteARebours(int* temps, int duree) {
    *temps = duree;
}

// Mise à jour et affichage du compte à rebours
void majCompteARebours(int* temps, clock_t* dernierTemps) {
    clock_t tempsActuel = clock();
    double tempsEcoule = ((double)(tempsActuel - *dernierTemps)) / CLOCKS_PER_SEC;

    if (tempsEcoule >= 1.0) {
        *dernierTemps = tempsActuel;
        if (*temps > 0) {
            printf("Temps restant : %d secondes\n", *temps);
            (*temps)--;
        } else {
            printf("Le temps est écoulé !\n");
        }
    }
}

void niveau_3() {
    int lignes = 10;
    int colonnes = 20;
    int temps, duree = 120;
    initCompteARebours(&temps, duree);
    clock_t dernierTemps = clock();
    int plateau_de_temps[30][30];
    int lignestemps = 30, colonnestemps = 30;
    int caseSupprimer = 0; // Initialisation de caseSupprimer
    init_temps_terrain(plateau_de_temps, lignestemps, colonnestemps);
    init_temps_bordure(plateau_de_temps, lignestemps, colonnestemps);
    int win = 0;
    int position_snoopy[2] = {lignes / 2, colonnes / 2}; // Position initiale de Snoopy
    int sauvegarde_position_snoopy[2] = {lignes / 2, colonnes / 2}; // Sauvegarde de la position de Snoopy
    int plateau_de_jeu[10][20] = {0}; // Initialisation du plateau de jeu
    init_terrain_niveau_3(plateau_de_jeu, position_snoopy);

    int positionBalleX = 0, positionBalleY = 0; // Position initiale de la balle
    int directionBalleX = 1, directionBalleY = 1; // Direction initiale de la balle

    while (win != 1&& temps>0) {
        majCompteARebours(&temps, &dernierTemps);
        affichage_jeu_et_temps(plateau_de_jeu, lignes, colonnes, plateau_de_temps, lignestemps, colonnestemps);
        defaite(plateau_de_temps, lignestemps, colonnestemps, &caseSupprimer);
        if (kbhit()) {
            deplacement_snoopy(position_snoopy, plateau_de_jeu);
        }

        plateau_de_jeu[sauvegarde_position_snoopy[0]][sauvegarde_position_snoopy[1]] = 0; // Effacer l'ancienne position de Snoopy

        if (!deplacement_correcte( lignestemps, colonnestemps, position_snoopy,  plateau_de_jeu,  plateau_de_temps)) {
            position_snoopy[0] = sauvegarde_position_snoopy[0];
            position_snoopy[1] = sauvegarde_position_snoopy[1];
        } else {
            sauvegarde_position_snoopy[0] = position_snoopy[0];
            sauvegarde_position_snoopy[1] = position_snoopy[1];
        }

        plateau_de_jeu[position_snoopy[0]][position_snoopy[1]] = 7; // Mettre à jour la nouvelle position de Snoopy

        mettreAJourBalle(&positionBalleX, &positionBalleY, &directionBalleX, &directionBalleY, plateau_de_jeu);



        if ((plateau_de_jeu[0][0] == 0) && (plateau_de_jeu[0][colonnes - 1] == 0) && (plateau_de_jeu[lignes - 1][0] == 0) && (plateau_de_jeu[lignes - 1][colonnes - 1] == 0)) {
            printf("Vous avez gagné");
            win = 1;
        }

        Sleep(1000); // Contrôle la vitesse de la balle
    }
}


