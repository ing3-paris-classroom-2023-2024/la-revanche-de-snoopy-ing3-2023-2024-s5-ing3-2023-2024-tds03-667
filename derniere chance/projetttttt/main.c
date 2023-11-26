#include <stdio.h>
#include <string.h>
#include <conio.h>
#include <windows.h>
#include <time.h>
#include "niveau 3.h"
#define Niv1_Mdp "niveau1"
#define Niv2_Mdp "niveau2"
#define Niv3_Mdp "niveau3"
#define Niv4_Mdp "niveau4"


// Sous progammes pour le menu principal


void afficherReglesDuJeu() {
    printf("Bienvenue dans 'La revanche de Snoopy'!\n");
    printf("Les regles sont les suivantes :\n");
    printf("- Utiliser les touches ZQSD pour deplacer Snoopy.\n");
    printf("- Collecter tous les oiseaux pour passer au niveau suivant.\n");
    printf("- Eviter la balle et ne vous faites pas toucher.\n");
    printf("- 120 secondes pour chaque niveau.\n");
}

void lancerNouveauJeu() {
    printf("Lancement d'un nouveau jeu...\n");
    niveau_1();
}

void chargerPartie() {
    printf("Chargement d'une partie sauvegardée...\n");

}

void lancerNiveau(int niveau) {
    switch(niveau) {
        case 1:
            niveau_1();
            break;
        case 2:
            niveau_2();
            break;
        case 3:
            niveau_3();
            break;
        case 4:
            //niveau_4();
            break;

        default:
            printf("Niveau inconnu.\n");
    }
}

void entrerMotDePasse() {
    char motDePasse[100];
    printf("Veuillez entrer le mot de passe pour debloquer le niveau correspondant: ");
    scanf("%99s", motDePasse);


    if (strcmp(motDePasse, Niv1_Mdp) == 0) {
        lancerNiveau(1);
    } else if (strcmp(motDePasse, Niv2_Mdp) == 0) {
        lancerNiveau(2);
    } else if (strcmp(motDePasse, Niv3_Mdp) == 0) {
        lancerNiveau(3);
    } else if (strcmp(motDePasse, Niv4_Mdp) == 0) {
        lancerNiveau(4);
    } else {
        printf("Mot de passe incorrect donc votre acces est refuse.\n");
    }
}


void afficherScores() {
    printf("Affichage des meilleurs scores...\n");
    FILE *file = fopen("scores.txt","r");
    if (file == NULL) {
        printf("Aucun score n'est disponible pour le moment.\n");
        return;
    }

    int score;
    int i = 0;
    printf("Scores:\n");
    while (fscanf(file, "%d", &score) == 1) {
        printf("Score #%d: %d\n", ++i, score);
    }

    if (i == 0) {
        printf("Aucun score n'est disponible pour le moment.\n");
    }

    fclose(file);
}


int main() {
    int lignes = 10;
    int colonnes = 20;
    int lignestemps=30, colonnestemps=30;
    printf("Debut du programme \n");
    char choix;
    int boucleMenu = 1;

    while (boucleMenu) {
        printf("\nMenu Principal\n");
        printf("1. Regles du jeu\n");
        printf("2. Lancer un nouveau jeu\n");
        printf("3. Charger une partie\n");
        printf("4. Mot de passe\n");
        printf("5. Scores\n");
        printf("6. Quitter\n");
        printf("Veuillez saisir votre choix: ");

        choix = getchar();
        while (getchar() != '\n'); // Nettoyer le buffer d'entrée

        switch (choix) {
            case '1':
                afficherReglesDuJeu();
                break;
            case '2':
                lancerNouveauJeu();
                break;
            case '3':
                chargerPartie();
                break;
            case '4':
                entrerMotDePasse();
                break;
            case '5':
                afficherScores();
                break;
            case '6':
                printf("Merci et à bientot!\n");
                boucleMenu = 0;
                break;
            default:
                printf("Choix invalide, veuillez réessayer.\n");
        }
    }


    return 0;
}
