#include <stdio.h>
#include <string.h>
#include <conio.h>
#include <windows.h>
#include <time.h>
void curseur3(int colonne, int ligne) {
    COORD coord;
    coord.X = colonne;
    coord.Y = ligne;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void annonce3(char *msg){
    curseur3(0, 13);
    printf(msg);
}


char traduction_bloc3(int number) {
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


// Affiche le plateau de jeu et la bordure de temps
void affichage_jeu_et_temps3(int plateau_de_jeu[][20], int lignes, int colonnes, int plateau_de_temps[30][30], int lignestemps, int colonnestemps) {
    curseur3(0,0);

    // Affiche la bordure supérieure de temps
    for (int c = 0; c < colonnestemps; c++) {
        printf("%c", traduction_bloc3(plateau_de_temps[0][c]));
    }
    printf("\n");

    // Affiche chaque ligne du terrain avec les bordures latérales de temps
    for (int l = 0; l < lignes; l++) {
        // Bordure gauche
        printf("%c", traduction_bloc3(plateau_de_temps[l][0]));

        // Affiche les éléments du jeu
        for (int c = 0; c < colonnes; c++) {
            printf("%c", traduction_bloc3(plateau_de_jeu[l][c]));
        }

        // Bordure droite
        printf("%c\n", traduction_bloc3(plateau_de_temps[l][colonnestemps - 1]));
    }

    // Affiche la bordure inférieure de temps
    for (int c = 0; c < colonnestemps; c++) {
        printf("%c", traduction_bloc3(plateau_de_temps[lignestemps - 1][c]));
    }
    printf("\n");
}

// Gère les déplacements de Snoopy dans le jeu
void deplacement_snoopy3(int position_snoopy[2], int terrain[][20]) {
    int input = getch();
    // Détecte la direction et met à jour la position de Snoopy
    if (input == 'd' || input == 'D') position_snoopy[1]++;
    if (input == 's' || input == 'S') position_snoopy[0]++;
    if (input == 'q' || input == 'Q') position_snoopy[1]--;
    if (input == 'z' || input == 'Z') position_snoopy[0]--;
}


#include <stdio.h>

// Initialisation du terrain pour le niveau 3 du jeu.
void init_terrain_niveau_3(int plateau_de_jeu[][20], int position_snoopy[2]) {
    int lignes = 10;
    int colonnes = 20;

    // Placement des éléments spéciaux sur le terrain.
    plateau_de_jeu[0][0] = 9; // Oiseau en haut à gauche.
    plateau_de_jeu[0][colonnes - 1] = 9; // Oiseau en haut à droite.
    plateau_de_jeu[lignes - 1][0] = 9; // Oiseau en bas à gauche.
    plateau_de_jeu[lignes - 1][colonnes - 1] = 9; // Oiseau en bas à droite.

    // Création d'une zone murée autour de Snoopy.
    int largeur = 3;
    for(int c = position_snoopy[1] - largeur; c <= position_snoopy[1] + largeur; c++) {
        plateau_de_jeu[position_snoopy[0] + largeur][c] = 11; // Mur horizontal.
        plateau_de_jeu[position_snoopy[0] - largeur][c] = 11; // Mur horizontal.
    }
    for(int l = position_snoopy[0] - largeur; l <= position_snoopy[0] + largeur; l++) {
        plateau_de_jeu[l][position_snoopy[1] + largeur] = 11; // Mur vertical.
        plateau_de_jeu[l][position_snoopy[1] - largeur] = 11; // Mur vertical.
    }

    // Placement d'un téléporteur près de Snoopy.
    plateau_de_jeu[position_snoopy[0] - 2][position_snoopy[1] + 2] = 10;

    // Bloc normaux
    plateau_de_jeu[position_snoopy[0] - 1][position_snoopy[1] +8] = 5;
    plateau_de_jeu[position_snoopy[0] - 1][position_snoopy[1] +9] = 5;
    plateau_de_jeu[position_snoopy[0] - 1][position_snoopy[1] +7] = 5;
    plateau_de_jeu[position_snoopy[0] - 1][position_snoopy[1] +6] = 5;
    plateau_de_jeu[position_snoopy[0] - 1][position_snoopy[1] +5] = 5;
    plateau_de_jeu[position_snoopy[0] - 1][position_snoopy[1] +4] = 5;

    plateau_de_jeu[position_snoopy[0] - 1][position_snoopy[1] -8] = 5;
    plateau_de_jeu[position_snoopy[0] - 1][position_snoopy[1] -9] = 5;
    plateau_de_jeu[position_snoopy[0] - 1][position_snoopy[1] -7] = 5;
    plateau_de_jeu[position_snoopy[0] - 1][position_snoopy[1] -6] = 5;
    plateau_de_jeu[position_snoopy[0] - 1][position_snoopy[1] -5] = 5;
    plateau_de_jeu[position_snoopy[0] - 1][position_snoopy[1] -4] = 5;
    plateau_de_jeu[position_snoopy[0] - 1][position_snoopy[1] -10] = 5;

    plateau_de_jeu[position_snoopy[0] - 3][position_snoopy[1] -10] = 5;
    plateau_de_jeu[position_snoopy[0] - 3][position_snoopy[1] -8] = 5;
    plateau_de_jeu[position_snoopy[0] - 3][position_snoopy[1] -9] = 5;
    plateau_de_jeu[position_snoopy[0] - 3][position_snoopy[1] -7] = 5;
    plateau_de_jeu[position_snoopy[0] - 3][position_snoopy[1] -6] = 5;
    plateau_de_jeu[position_snoopy[0] - 3][position_snoopy[1] -5] = 5;
    plateau_de_jeu[position_snoopy[0] - 3][position_snoopy[1] -4] = 5;

    plateau_de_jeu[position_snoopy[0] +1][position_snoopy[1] -10] = 5;
    plateau_de_jeu[position_snoopy[0] +1][position_snoopy[1] -9] = 5;
    plateau_de_jeu[position_snoopy[0] +1][position_snoopy[1] -8] = 5;
    plateau_de_jeu[position_snoopy[0] +1][position_snoopy[1] -7] = 5;
    plateau_de_jeu[position_snoopy[0] +1][position_snoopy[1] -6] = 5;
    plateau_de_jeu[position_snoopy[0] +1][position_snoopy[1] -5] = 5;
    plateau_de_jeu[position_snoopy[0] +1][position_snoopy[1] -4] = 5;

    plateau_de_jeu[position_snoopy[0] +4][position_snoopy[1] -1] = 11;
    plateau_de_jeu[position_snoopy[0] +3][position_snoopy[1] -1] = 11;
    plateau_de_jeu[position_snoopy[0] +5][position_snoopy[1] -1] = 11;



}

// Vérifie si le déplacement de Snoopy est valide et met à jour le terrain en conséquence.
int deplacement_correcte3(int lignestemps, int colonnestemps, int position_snoopy[2], int plateau_de_jeu[][20], int plateau_de_temps[30][30]) {
    int lignes = 10;
    int colonnes = 20;

    // Vérifie si Snoopy rencontre un mur.
    if (plateau_de_jeu[position_snoopy[0]][position_snoopy[1]] == 11||plateau_de_jeu[position_snoopy[0]][position_snoopy[1]]==5) {
        affichage_jeu_et_temps3(plateau_de_jeu, lignes, colonnes, plateau_de_temps, lignestemps, colonnestemps);
        printf("Snoopy ne peut pas avancer dans ce sens car il y a un mur\n");
        return 0;
    }

    // Vérifie si Snoopy sort du terrain.
    if (position_snoopy[0] < 0 || position_snoopy[1] < 0 || position_snoopy[1] > colonnes - 1 || position_snoopy[0] > lignes - 1) {
        affichage_jeu_et_temps3(plateau_de_jeu, lignes, colonnes, plateau_de_temps, lignestemps, colonnestemps);
        printf("Vous sortez du terrain\n");
        return 0;
    }

    // Vérifie si Snoopy trouve un téléporteur.
    if (plateau_de_jeu[position_snoopy[0]][position_snoopy[1]] == 10) {
        affichage_jeu_et_temps3(plateau_de_jeu, lignes, colonnes, plateau_de_temps, lignestemps, colonnestemps);
        printf("Vous avez trouvé un téléporteur\n");
        position_snoopy[1] += 3;
        return 1;
    }

    // Vérifie si la case est vide ou contient un oiseau.
    if (plateau_de_jeu[position_snoopy[0]][position_snoopy[1]] == 0 || plateau_de_jeu[position_snoopy[0]][position_snoopy[1]] == 9) {
        if (plateau_de_jeu[position_snoopy[0]][position_snoopy[1]] == 9) {
            printf("Vous avez ramassé un oiseau \n");
            plateau_de_jeu[position_snoopy[0]][position_snoopy[1]] = 0;
        }
        affichage_jeu_et_temps3(plateau_de_jeu, lignes, colonnes, plateau_de_temps, lignestemps, colonnestemps);
        return 1;
    }

    return 0; // Retour par défaut si aucune condition n'est remplie.
}


void mettreAJourBalle3(int *positionBalleX, int *positionBalleY, int *directionX, int *directionY, int plateau_de_jeu[][20], int position_snoopy[2], int position_initiale_snoopy[2]) {
    int vie = 3; // Nombre de vies de Snoopy
    int lignes = 10, colonnes = 20; // Dimensions du terrain

    // Sauvegarde de l'ancienne position de la balle
    int ancienX = *positionBalleX;
    int ancienY = *positionBalleY;

    // Calcule la nouvelle position de la balle
    int suivantX = *positionBalleX + *directionX;
    int suivantY = *positionBalleY + *directionY;

    // Gestion des collisions avec les murs et changement de direction
    if (suivantX < 0 || suivantX >= colonnes || plateau_de_jeu[*positionBalleY][suivantX] == 11) {
        *directionX *= -1; // Change la direction sur l'axe X
    } else {
        *positionBalleX = suivantX; // Met à jour la position X
    }

    if (suivantY < 0 || suivantY >= lignes || plateau_de_jeu[suivantY][*positionBalleX] == 11) {
        *directionY *= -1; // Change la direction sur l'axe Y
    } else {
        *positionBalleY = suivantY; // Met à jour la position Y
    }

    // Efface l'ancienne position de la balle si nécessaire
    if (plateau_de_jeu[ancienY][ancienX] != 9 && plateau_de_jeu[ancienY][ancienX] != 7) {
        plateau_de_jeu[ancienY][ancienX] = 0;
    }


    // Collision avec Snoopy
    if (plateau_de_jeu[*positionBalleY][*positionBalleX] == 7) {
        printf("Snoopy est touché par la balle!\n");
        vie -= 1; // Décrémente le nombre de vies
        // Réinitialise la position de Snoopy
        position_snoopy[0] = position_initiale_snoopy[0];
        position_snoopy[1] = position_initiale_snoopy[1];
        curseur3(23, 5);
        printf("Vies restantes : %d\n", vie);
        if (vie == 0) {
            // Logique pour retourner au menu principal ou finir le jeu
        }
    }

    // Met à jour la position de la balle sur le plateau
    if (plateau_de_jeu[*positionBalleY][*positionBalleX] != 9 && plateau_de_jeu[*positionBalleY][*positionBalleX] != 7) {
        plateau_de_jeu[*positionBalleY][*positionBalleX] = 8;
    }
}

// Initialisation des cases intérieures du tableau de gestion du temps
// Ces cases représentent les espaces vides autour du terrain de jeu
void init_temps_terrain3(int plateau_de_temps[30][30], int lignestemps, int colonnestemps) {
    int c, l;
    for (c = 0; c < colonnestemps; c++) {
        // Initialisation des cases supérieures et inférieures à vide
        plateau_de_temps[0][c] = 0;
        plateau_de_temps[lignestemps - 1][c] = 0;
    }
    for (l = 0; l < lignestemps; l++) {
        // Initialisation des cases latérales gauche et droite à vide
        plateau_de_temps[l][0] = 0;
        plateau_de_temps[l][colonnestemps - 1] = 0;
    }
}

// Initialisation des bordures du tableau de gestion du temps
// Ces bordures servent à indiquer le temps restant dans le jeu
void init_temps_bordure3(int plateau_de_temps[30][30], int lignestemps, int colonnestemps) {
    int c, l;
    for (c = 0; c < colonnestemps; c++) {
        // Définition des bordures supérieure et inférieure
        plateau_de_temps[0][c] = 11;
        plateau_de_temps[lignestemps - 1][c] = 11;
    }
    for (l = 0; l < lignestemps; l++) {
        // Définition des bordures latérales gauche et droite
        plateau_de_temps[l][0] = 11;
        plateau_de_temps[l][colonnestemps - 1] = 11;
    }
}

// Gestion de la défaite dans le jeu
// Cette fonction met à jour la bordure de temps en fonction du temps écoulé
void defaite3(int plateau_de_temps[30][30], int lignestemps, int colonnestemps, int *caseSupprimer) {
    int totalBordures = (lignestemps + colonnestemps - 1) * 2;
    int position = *caseSupprimer % totalBordures;

    // Mise à jour de la bordure de temps en fonction de la positio
    if (position < colonnestemps) {
        // Mise à jour de la bordure supérieure
        plateau_de_temps[0][position] = 0;
    } else if (position < colonnestemps + lignestemps - 2) {
        // Mise à jour de la bordure droite
        plateau_de_temps[position - colonnestemps + 1][colonnestemps - 1] = 0;
    } else if (position < 2 * colonnestemps + lignestemps - 3) {
        // Mise à jour de la bordure inférieure
        plateau_de_temps[lignestemps - 1][2 * colonnestemps + lignestemps - 4 - position] = 0;
    } else {
        // Mise à jour de la bordure gauche
        plateau_de_temps[2 * (lignestemps + colonnestemps) - 6 - position][0] = 0;
    }

    // Incrémentation du compteur pour la prochaine mise à jour
    *caseSupprimer += 1;

}
void initCompteARebours3(int* temps, int duree) {
    *temps = duree;
}

// Mise à jour et affichage du compte à rebours

void majCompteARebours3(int* temps, clock_t* dernierTemps) {
    clock_t tempsActuel = clock();
    double tempsEcoule = ((double)(tempsActuel - *dernierTemps)) / CLOCKS_PER_SEC;

    // Réduire le compte à rebours d'une seconde si une seconde s'est écoulée
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

// Fonction principale du niveau 3 du jeu
void niveau_3() {
    int lignes = 10;
    int colonnes = 20;
    int temps, duree = 120; // Durée initiale du compte à rebours
    initCompteARebours3(&temps, duree);
    clock_t dernierTemps = clock();

    int plateau_de_temps[30][30];
    int lignestemps = 30, colonnestemps = 30;
    int caseSupprimer = 0; // Compteur pour la mise à jour de la bordure de temps
    init_temps_terrain3(plateau_de_temps, lignestemps, colonnestemps);
    init_temps_bordure3(plateau_de_temps, lignestemps, colonnestemps);

    int vie = 3; // Nombre de vies de Snoopy
    int win = 0; // Indicateur de victoire
    int position_snoopy[2] = {lignes / 2, colonnes / 2}; // Position initiale de Snoopy
    int position_initiale_snoopy[2] = {lignes / 2, colonnes / 2}; // Sauvegarde de la position initiale
    int sauvegarde_position_snoopy[2] = {lignes / 2, colonnes / 2}; // Pour restaurer la position en cas de besoin

    int plateau_de_jeu[10][20] = {0}; // Initialisation du plateau de jeu
    init_terrain_niveau_3(plateau_de_jeu, position_snoopy);

    int positionBalleX = 0, positionBalleY = 0; // Position initiale de la balle
    int directionBalleX = 1, directionBalleY = 1; // Direction initiale de la balle

    // Boucle principale du jeu
    while (win != 1 && temps > 0&& vie!=0) {
        majCompteARebours3(&temps, &dernierTemps);
        defaite3(plateau_de_temps, lignestemps, colonnestemps, &caseSupprimer);

        if (kbhit()) {
            deplacement_snoopy3(position_snoopy, plateau_de_jeu);
        }

        // Réinitialisation de la position précédente de Snoopy
        plateau_de_jeu[sauvegarde_position_snoopy[0]][sauvegarde_position_snoopy[1]] = 0;

        // Mise à jour de la position de Snoopy
        if (!deplacement_correcte3(lignestemps, colonnestemps, position_snoopy, plateau_de_jeu, plateau_de_temps)) {
            position_snoopy[0] = sauvegarde_position_snoopy[0];
            position_snoopy[1] = sauvegarde_position_snoopy[1];
        } else {
            sauvegarde_position_snoopy[0] = position_snoopy[0];
            sauvegarde_position_snoopy[1] = position_snoopy[1];
        }

        plateau_de_jeu[position_snoopy[0]][position_snoopy[1]] = 7; // Mise à jour de la position actuelle de Snoopy

        mettreAJourBalle3(&positionBalleX, &positionBalleY, &directionBalleX, &directionBalleY, plateau_de_jeu, position_snoopy, position_initiale_snoopy);

        // Vérifier si toutes les conditions de victoire sont remplies
        if ((plateau_de_jeu[0][0] == 0) && (plateau_de_jeu[0][colonnes - 1] == 0) && (plateau_de_jeu[lignes - 1][0] == 0) && (plateau_de_jeu[lignes - 1][colonnes - 1] == 0)) {
            printf("Vous avez gagné");
            win = 1;
        }

        affichage_jeu_et_temps3(plateau_de_jeu, lignes, colonnes, plateau_de_temps, lignestemps, colonnestemps);
        Sleep(100); // Délai pour ralentir la vitesse de la balle
    }
}


