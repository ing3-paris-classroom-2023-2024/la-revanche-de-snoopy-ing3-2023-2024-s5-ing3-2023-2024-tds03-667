#include <stdio.h>
#include <string.h>
#include <conio.h>
#include <stdio.h>
#include <windows.h>



void curseur(int colonne, int ligne) {
    COORD coord;
    coord.X = colonne;
    coord.Y = ligne;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void annonce(char *msg){
    curseur(0, 13);
    printf(msg);
}

void affichage_vie(int vie){
    curseur(23, 5);
    printf("Il vous reste %d vies", vie);
}


// TD3 GROUPE 667

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
    annonce("Caractere inconnu");
    return 'E';
}

void affichage_terrain(int plateau_de_jeu[][20], int lignes, int colonnes){
    curseur(0,0);
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



void **init_terrain_niveau_1(int plateau_de_jeu[][20], int position_snoopy[2],int colonnes,int lignes) {

    // Met les oiseaux aux 4 coins
    plateau_de_jeu[1][1] = 9;
    plateau_de_jeu[1][colonnes - 2] = 9;
    plateau_de_jeu[lignes - 2][1] = 9;
    plateau_de_jeu[lignes - 2][colonnes - 2] = 9;

    // Ajout d'une bordure de murs
    for (int c = 0; c < colonnes; c++) {
        plateau_de_jeu[0][c] = 11; // Mur en haut
        plateau_de_jeu[lignes - 1][c] = 11; // Mur en bas
    }
    for (int l = 0; l < lignes; l++) {
        plateau_de_jeu[l][0] = 11; // Mur à gauche
        plateau_de_jeu[l][colonnes - 1] = 11; // Mur à droite
    }

    // fais un carré de mur
    int largeur = 2;
    for(int c = position_snoopy[1] - largeur ; c <= position_snoopy[1] + largeur  ; c++) {
        plateau_de_jeu[position_snoopy[0] + largeur][c] = 11;
        plateau_de_jeu[position_snoopy[0] - largeur][c] = 11;
    }
    for(int l = position_snoopy[0] - largeur ; l <= position_snoopy[0] + largeur  ; l++) {
        plateau_de_jeu[l][position_snoopy[1] + largeur] = 11;
        plateau_de_jeu[l][position_snoopy[1] - largeur] = 11;
    }

    // Positionne un téléporteur
    plateau_de_jeu[position_snoopy[0] - 1][position_snoopy[1] + 1] = 10;

}

int deplacement_correcte(int position_snoopy[2], int plateau_de_jeu[][20], int colonnes, int lignes){
    if (  plateau_de_jeu[position_snoopy[0]][position_snoopy[1]]  == 11){
        annonce("Snoopy ne peut pas avancer dans ce sens car il y a un mur\n");
        return 0;
    }
    if ( position_snoopy[0] < 0 || position_snoopy[1] < 0 ||
         position_snoopy[1] > colonnes - 1 || position_snoopy[0] > lignes - 1 ){
        annonce("Vous sortez du terrain\n");

        return 0;
    }
    if ( plateau_de_jeu[position_snoopy[0]][position_snoopy[1]]  == 10){
        annonce("Vous avez trouve un teleporteur\n");

        position_snoopy[1] += 3;
        return 1;
    }
    if ( plateau_de_jeu[position_snoopy[0]][position_snoopy[1]]  == 0){
        annonce("                                                                ");
        return 1;
    }
    // conditon de victoire
    if ( plateau_de_jeu[position_snoopy[0]][position_snoopy[1]]  == 9) {
        plateau_de_jeu[position_snoopy[0]][position_snoopy[1]]  = 0;
        annonce("Vous avez ramasse un oiseau \n");

        return 1;
    }


}

void niveau_1() {
    int const lignes = 10;
    int const colonnes = 20;
    int win = 0;

    //on positionne de snoopy et on lui donne 3 vie
    int position_snoopy[2] = {lignes / 2, colonnes / 2}; // x,y
    int sauvegarde_position_snoopy[2] = {lignes / 2, colonnes / 2}; // x,y

    //plateau
    int plateau_de_jeu[10][20] = {0}; // contient des chiffres de 0 a 9
    init_terrain_niveau_1(plateau_de_jeu, position_snoopy,colonnes,lignes);
    plateau_de_jeu[position_snoopy[0]][position_snoopy[1]] = 7;

    // boucle de jeu
    //affichage_terrain(plateau_de_jeu, lignes, colonnes);

    while (win != 1) {
        sauvegarde_position_snoopy[0] = position_snoopy[0];
        sauvegarde_position_snoopy[1] = position_snoopy[1];
        deplacement_snoopy(position_snoopy, plateau_de_jeu, lignes, colonnes);


        //test si le deplacement est correcte, si oui on remet un 0 ou etait snoopy
        if (deplacement_correcte(position_snoopy, plateau_de_jeu, colonnes,lignes) == 1) {
            plateau_de_jeu[sauvegarde_position_snoopy[0]][sauvegarde_position_snoopy[1]] = 0;
        } else {
            position_snoopy[0] = sauvegarde_position_snoopy[0];
            position_snoopy[1] = sauvegarde_position_snoopy[1];

        }
        plateau_de_jeu[position_snoopy[0]][position_snoopy[1]] = 7;

        affichage_terrain(plateau_de_jeu, lignes, colonnes);
        // condition de victoire
        if ( (               (plateau_de_jeu[1][1] == 7) || (plateau_de_jeu[1][1] == 0) ) &&
                ( (plateau_de_jeu[1][colonnes - 2] == 7) || (plateau_de_jeu[1][colonnes - 2] == 0) ) &&
                  ( (plateau_de_jeu[lignes - 2][1] == 7) || (plateau_de_jeu[lignes - 2][1] == 0) ) &&
                  ( (plateau_de_jeu[lignes - 2][colonnes - 2] == 7) || (plateau_de_jeu[lignes - 2][colonnes - 2] == 0) ) ){
            affichage_terrain(plateau_de_jeu, lignes, colonnes);
            annonce("Vous avez gagne                    \n Appuyez sur une touche pour continuer");
            getch();
            win = 1;
        }
    }
}


int main() {

    printf("Debut du programme \n");
    niveau_1();
    return 0;
}