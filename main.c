#include <stdio.h>
#include <string.h>
#include <conio.h>
#include <stdio.h>



void remplissage_oiseau(int plateau_de_jeu[lignes][colonnes]) {
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
    printf("Caractere inconnu");
    return 'E';
}

void affichage_terrain(int plateau_de_jeu[][colonnes]){
    for(int l = 0; l != lignes; l ++) {
        for (int c = 0; c != colonnes; c++) {
            printf("%c", traduction_bloc(plateau_de_jeu[l][c]));
        }
        printf("\n");
    }
}



int *deplacement_snoopy(int position_snoopy[2], int terrain[][colonnes]){
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

int main() {
    int const lignes = 10;
    int const colonnes = 20;

    printf("Debut du programme \n");
    int bloc = 1;
    //plateau
    int plateau_de_jeu[lignes][colonnes] = {0}; // contient des chiffres de 0 a 9
    char blocs[lignes * colonnes]; //j * colonnes + lignes
    remplissage_oiseau(plateau_de_jeu);
    //on positionne de snoopy et on lui donne 3 vie
    int position_snoopy[2] = {5,10}; // x,y
    plateau_de_jeu[position_snoopy[0]][position_snoopy[1]] = 7;
    int vie_snoopy = 3;

    affichage_terrain(plateau_de_jeu);
    deplacement_snoopy(position_snoopy,plateau_de_jeu);
    system("pause");

    return 0;
}
