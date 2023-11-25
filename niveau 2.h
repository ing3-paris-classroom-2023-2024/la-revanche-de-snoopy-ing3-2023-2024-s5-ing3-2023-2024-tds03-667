#include <stdio.h>
#include <string.h>
#include <conio.h>
#include <stdio.h>

int lignes = 10;
int colonnes = 20;

// TD3 GROUPE 667
char traduction_bloc(int number) {
    if (number == 0) {return ' ';}
    if (number == 1) {return 0x16;} // bloc cassable
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

void affichage_terrain(int plateau_de_jeu[][20], int lignes, int colonnes){
    printf("\n\n");

    for(int l = 0; l != lignes; l ++) {
        for (int c = 0; c != colonnes; c++) {
            printf("%c", traduction_bloc(plateau_de_jeu[l][c]));
        }
        printf("\n");
    }
}

void deplacement_snoopy(int position_snoopy[2], int terrain[][20],int lignes, int colonnes){
    // modifie position_snoopy en la nouvelle position de snoopy
    int input = getch();
    // position_snoopy[2] = [x,y]
    if (input == 'd' ||  input == 'D') {
        position_snoopy[1] += 1;
    }
    if (input == 's'||  input == 'S') {
        position_snoopy[0] += 1;
    }
    if (input == 'q' ||  input == 'Q') {
        position_snoopy[1] -=1;
    }
    if (input == 'z' ||  input == 'Z') {
        position_snoopy[0] -=  1;
    }
    if (input == 'P' ||  input == 'p') {
        input = 0;
        while (input != 'P' &&  input != 'p')
            input = getch();
    }
}



void **init_terrain_niveau_2(int plateau_de_jeu[][colonnes], int position_snoopy[2]) {

    // Met les oiseaux aux 4 coins
    plateau_de_jeu[0][0] = 9;
    plateau_de_jeu[0][colonnes - 1] = 9;
    plateau_de_jeu[lignes - 1][0] = 9;
    plateau_de_jeu[lignes - 1][colonnes - 1] = 9;

    // fais un carré de mur
    int largeur = 3;
    for(int c = position_snoopy[1] - largeur ; c <= position_snoopy[1] + largeur  ; c++) {
        plateau_de_jeu[position_snoopy[0] + largeur][c] = 11;
        plateau_de_jeu[position_snoopy[0] - largeur][c] = 11;
    }
    for(int l = position_snoopy[0] - largeur ; l <= position_snoopy[0] + largeur  ; l++) {
        plateau_de_jeu[l][position_snoopy[1] + largeur] = 11;
        plateau_de_jeu[l][position_snoopy[1] - largeur] = 11;
    }
    plateau_de_jeu[position_snoopy[0] - 3][position_snoopy[1] +4] = 2;
    plateau_de_jeu[position_snoopy[0] - 3][position_snoopy[1] +5] = 2;
    plateau_de_jeu[position_snoopy[0] - 3][position_snoopy[1] +6] = 2;
    plateau_de_jeu[position_snoopy[0] - 2][position_snoopy[1] +7] = 1;
    plateau_de_jeu[position_snoopy[0] - 1][position_snoopy[1] +6] = 1;
    plateau_de_jeu[position_snoopy[0] - 1][position_snoopy[1] +5] = 1;
    plateau_de_jeu[position_snoopy[0] - 1][position_snoopy[1] +4] = 1;
    // Positionne un téléporteur
    plateau_de_jeu[position_snoopy[0] - 2][position_snoopy[1] +2] = 10;

}

int deplacement_correcte(int position_snoopy[2], int plateau_de_jeu[][20]){
    if (  plateau_de_jeu[position_snoopy[0]][position_snoopy[1]]  == 11){
        affichage_terrain(plateau_de_jeu, lignes, colonnes);
        printf("Snoopy ne peut pas avancer dans ce sens car il y a un mur\n");
        return 0;
    }
    if ( position_snoopy[0] < 0 || position_snoopy[1] < 0 ||
         position_snoopy[1] > colonnes - 1 || position_snoopy[0] > lignes - 1 ){
        affichage_terrain(plateau_de_jeu, lignes, colonnes);
        printf("Vous sortez du terrain\n");
        return 0;
    }
    if ( plateau_de_jeu[position_snoopy[0]][position_snoopy[1]]  == 10){
        affichage_terrain(plateau_de_jeu, lignes, colonnes);
        printf("Vous avez trouvé un téléporteur\n");
        position_snoopy[1] += 3;
        return 1;
    }
    if ( plateau_de_jeu[position_snoopy[0]][position_snoopy[1]]  == 0){
        affichage_terrain(plateau_de_jeu, lignes, colonnes);
        return 1;
    }
    if (plateau_de_jeu[position_snoopy[0]][position_snoopy[1]] == 1) {
        int input = getch();
        if (input == 'd') {
            plateau_de_jeu[position_snoopy[0]][position_snoopy[1] + 1] = 1;
        } else if (input == 's') {
            plateau_de_jeu[position_snoopy[0] + 1][position_snoopy[1]] = 1;
        } else if (input == 'q') {
            plateau_de_jeu[position_snoopy[0]][position_snoopy[1] - 1] = 1;
        } else if (input == 'z') {
            plateau_de_jeu[position_snoopy[0] - 1][position_snoopy[1]] = 1;
        }
        plateau_de_jeu[position_snoopy[0]][position_snoopy[1]] = 0;
        affichage_terrain(plateau_de_jeu, lignes, colonnes);
        printf("Vous avez casse un bloc !\n");
    }
    if (plateau_de_jeu[position_snoopy[0]][position_snoopy[1]] == 2) {
        int input = getch();

        if (input == 'z') {
                // Faites disparaître le bloc en -1 de Snoopy
                plateau_de_jeu[position_snoopy[0] - 1][position_snoopy[1]] = 0;
                // Faites apparaître le bloc en -2 de Snoopy
                plateau_de_jeu[position_snoopy[0] - 2][position_snoopy[1]] = 2;
                // Faites avancer Snoopy d'une case
                position_snoopy[0] -= 1;
                affichage_terrain(plateau_de_jeu, lignes, colonnes);
                printf("Vous avez pousse un bloc vers le haut et avancez !\n");
        }
    }




    // conditon de victoire
    if ( plateau_de_jeu[position_snoopy[0]][position_snoopy[1]]  == 9) {
        plateau_de_jeu[position_snoopy[0]][position_snoopy[1]]  = 0;
        affichage_terrain(plateau_de_jeu, lignes, colonnes);
        printf("Vous avez ramassé un oiseau \n");
        return 1;
    }
}

void niveau_2() {
    int const lignes = 10;
    int const colonnes = 20;
    int win = 0;

    //on positionne de snoopy et on lui donne 3 vie
    int position_snoopy[2] = {lignes / 2, colonnes / 2}; // x,y
    int sauvegarde_position_snoopy[2] = {lignes / 2, colonnes / 2}; // x,y

    //plateau
    int plateau_de_jeu[10][20] = {0}; // contient des chiffres de 0 a 9
    init_terrain_niveau_2(plateau_de_jeu, position_snoopy);
    plateau_de_jeu[position_snoopy[0]][position_snoopy[1]] = 7;


    while (win != 1) {
        affichage_terrain(plateau_de_jeu, lignes, colonnes);
        sauvegarde_position_snoopy[0] = position_snoopy[0];
        sauvegarde_position_snoopy[1] = position_snoopy[1];
        deplacement_snoopy(position_snoopy, plateau_de_jeu, lignes, colonnes);

        //test si le deplacement es tcorrecte, si oui on remet un 0 ou etait snoopy
        if (deplacement_correcte(position_snoopy, plateau_de_jeu) == 1) {
            plateau_de_jeu[sauvegarde_position_snoopy[0]][sauvegarde_position_snoopy[1]] = 0;
        } else {
            position_snoopy[0] = sauvegarde_position_snoopy[0];
            position_snoopy[1] = sauvegarde_position_snoopy[1];

        }
        plateau_de_jeu[position_snoopy[0]][position_snoopy[1]] = 7;
        // condition de victoire
        if ((plateau_de_jeu[0][0] == 0) &&
            (plateau_de_jeu[0][colonnes - 1] == 0) &&
            (plateau_de_jeu[lignes - 1][0] == 0) &&
            (plateau_de_jeu[lignes - 1][colonnes - 1] == 0)) {
            affichage_terrain(plateau_de_jeu, lignes, colonnes);
            printf("Vous avez gagné");
            win = 1;
        }
    }
}

int main() {
    printf("Debut du programme \n");
    niveau_2();
    return 0;
}
