#include <stdio.h>
#include <string.h>
#include <conio.h>
#include <stdio.h>

int lignes = 10;
int colonnes = 20;

void  **remplissage_oiseau(int plateau_de_jeu[][20], int lignes, int colonnes) {
    // Met les oiseaux aux 4 coins
    plateau_de_jeu[0][0] = 9;
    plateau_de_jeu[0][colonnes - 1] = 9;
    plateau_de_jeu[lignes - 1][0] = 9;
    plateau_de_jeu[lignes - 1][colonnes - 1] = 9;

}

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

void affichage_terrain(int plateau_de_jeu[][20], int lignes, int colonnes){
    for(int l = 0; l != lignes; l ++) {
        for (int c = 0; c != colonnes; c++) {
            printf("%c", traduction_bloc(plateau_de_jeu[l][c]));
        }
        printf("\n");
    }
}

int *deplacement_snoopy(int position_snoopy[2], int terrain[][20],int lignes, int colonnes){

    char input = _getch();

    int new_position_snoopy[2];
    // position_snoopy[2] = [x,y]

    // check qu'il n'y a pas d'obstacle, on se déplace avec ZQSD
    // si il y a un mur on renvoit la position inchangé
    if (input == "z" ||  input == "Z"){
        new_position_snoopy[0] = position_snoopy[0];
        new_position_snoopy[1] = position_snoopy[1] + 1 ;
        if ( ( terrain[new_position_snoopy[0]] == 0) &&
        (terrain[new_position_snoopy[1]] == 0) ){
            return new_position_snoopy;
        }
        else{ printf("%s", "\nSnoopy ne peut pas aller vers le haut");
            return position_snoopy;
                }
    }
    if (input == "q" ||  input == "Q"){
        new_position_snoopy[0] = position_snoopy[0] - 1;
        new_position_snoopy[1] = position_snoopy[1];
        if ( ( terrain[new_position_snoopy[0]] == 0) &&
             (terrain[new_position_snoopy[1]] == 0) ){
            return new_position_snoopy;
        }
        else{ printf("%s", "\nSnoopy ne peut pas aller vers la gauche");
            return position_snoopy;
        }
    }
    if (input == "s" ||  input == "S"){
        new_position_snoopy[0] = position_snoopy[0];
        new_position_snoopy[1] = position_snoopy[1] - 1 ;
        if ( ( terrain[new_position_snoopy[0]] == 0) &&
             (terrain[new_position_snoopy[1]] == 0) ){
            return new_position_snoopy;
        }
        else{ printf("%s", "\nSnoopy ne peut pas aller vers le bas");
            return position_snoopy;
        }
    }
    if (input == "d" ||  input == "D"){
        new_position_snoopy[0] = position_snoopy[0] + 1;
        new_position_snoopy[1] = position_snoopy[1];
        if ( ( terrain[new_position_snoopy[0]] == 0) &&
             (terrain[new_position_snoopy[1]] == 0) ){
            return new_position_snoopy;
        }
        else{ printf("%s", "\nSnoopy ne peut pas aller vers la droite");
            return position_snoopy;
        }
    }

    printf("%s ", "\n Vous n'avez pas rentré un caractere correcte");
    return position_snoopy;
}

void **init_terrain_niveau_1(int plateau_de_jeu[][colonnes], int position_snoopy[2]) {

    // Met les oiseaux aux 4 coins
    plateau_de_jeu[0][0] = 9;
    plateau_de_jeu[0][colonnes - 1] = 9;
    plateau_de_jeu[lignes - 1][0] = 9;
    plateau_de_jeu[lignes - 1][colonnes - 1] = 9;

    // fais un carré de mur
    for(int c = position_snoopy[1] - 2 ; c != position_snoopy[1] + 2  ; c++) {
        plateau_de_jeu[position_snoopy[0] + 2][c] = 11;
        plateau_de_jeu[position_snoopy[0] - 2][c] = 11;
    }
    for(int l = position_snoopy[0] - 2 ; l != position_snoopy[0] + 2  ; l++) {
        plateau_de_jeu[l][position_snoopy[1]+2] = 11;
        plateau_de_jeu[l][position_snoopy[1]-2] = 11;
    }
}

void niveau_1(){
    int const lignes = 10;
    int const colonnes = 20;

    //on positionne de snoopy et on lui donne 3 vie
    int position_snoopy[2] = {lignes/2,colonnes/2}; // x,y

    //plateau
    int plateau_de_jeu[10][20] = {0}; // contient des chiffres de 0 a 9
    init_terrain_niveau_1(plateau_de_jeu, position_snoopy);


    affichage_terrain(plateau_de_jeu, lignes, colonnes);
    plateau_de_jeu[position_snoopy[0]][position_snoopy[1]] = 7;
    int *new_position_snoopy = deplacement_snoopy(position_snoopy,plateau_de_jeu,lignes,colonnes);
    affichage_terrain(plateau_de_jeu, lignes, colonnes);
    while(1){
    deplacement_snoopy(position_snoopy,plateau_de_jeu, lignes, colonnes);
    }
    system("pause");


}

int main() {

    printf("Debut du programme \n");
    niveau_1();
    return 0;
}
