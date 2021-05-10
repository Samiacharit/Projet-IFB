#include <stdio.h>
#include <time.h>
#include <stdlib.h>

int nouvelle_partie();
int partie_existante();
int tirage(int joueur);
void grid(int N,char Tab[40][40]);
int partie_seule();
int partie_duo();
int jaune(int N, char Tab[40][40]);
int rouge(int N, char Tab[40][40]);
int reponse_p(int N, int colonne, char Tab[40][40], int couleur);
int reponse_e(int N, int colonne, char Tab[40][40], int couleur);

int main() {
    char menu;
    do{
        printf("Nouvelle partie : N \nPartie existante : P\nQuitter : Q\n");
        menu=getchar();
        fflush(stdin);

        switch(menu){
            case 'N' : nouvelle_partie();
                break;
            case 'P' : partie_existante();
                break;
            default: ;
        }
    }while(menu != 'N' && menu != 'P' && menu!='Q');

    return 0;
}


int nouvelle_partie(){

    int jouer;

    do {
        printf("== Jeu Puissance N ==\n 1. Jouer seul\n 2. Jouer a deux\n");
        scanf("%d", &jouer);

        switch (jouer) {
            case 1:
                printf("Vous avez choisi de jouer tout seul\n\n");
                break;
            case 2:
                printf("Vous avez choisi de jouer a deux\n");
                break;
            default:
                printf("Veuillez taper 1 ou 2\n\n");
                break;
        }
    } while (jouer != 1 && jouer != 2);

    if(jouer == 1){
        partie_seule();
    }
    else
        partie_duo();
    return 0;
}


int partie_existante(){
    FILE* f = fopen("partie_existante.text","a"); // a = ajouter , r = lecture, w = crÃ©er
    if(f != NULL){
        fprintf(f,"Test");
    }
    fclose(f);

    return 0;
}

int tirage(int joueur){

    srand(time(0));

    joueur = rand()%2;

    switch(joueur){
        case 0 : printf("Par tirage au sort, le joueur Jaune commence\n");
            break;
        case 1 : printf("Par tirage au sort, le joueur Rouge commence\n");
            break;
    }

    return joueur;
}

void grid(int N, char Tab[40][40]){
    int j,k;

    for (j=0;j<N;j++){
        for (k = 0; k < N; k++)
        {
            Tab[j][k]='_';
        }

    }

}


int partie_duo(){

    int N, joueur;
    char Tab[40][40];
    int i;

    printf("Combien de jetons voulez vous aligner pour gagner ?\n");
    scanf("%d",&N);

    N=N+2;

    joueur = tirage(joueur);


    grid(N,Tab);

    if(joueur == 1){
        i = 0;
        rouge(N,Tab);
    }
    else{
        i = 1;
        jaune(N,Tab);
    }

    for(i=i;i<=N*N;i++){
        if(i%2==0){
            jaune(N,Tab);
        }
        else
            rouge(N,Tab);
    }

    return 0;

}

int partie_seule(){
    printf("partie seule : SOON");
    return 0;
}

int rouge(int N, char Tab[40][40]){

    char reponse, rouge = 'X';
    int colonne;


    do{
        printf("\nJoueur Rouge, souhaitez-vous placer ou enlever un jeton ?\nPlacer : P\nEnlever : E");
        fflush(stdin);
        reponse = getchar();


        if(reponse == 'E'){
            reponse_e(N,colonne,Tab, rouge);
        }

        if(reponse == 'P'){
            reponse_p(N,colonne,Tab,rouge);
        }

    }while(reponse != 'P' && reponse != 'E');
}

int jaune(int N, char Tab[40][40]){

    char reponse, jaune = 'O';
    int colonne;

    do{
        printf("\nJoueur Jaune, souhaitez-vous placer ou enlever un jeton ?\nPlacer : P\nEnlever : E");
        fflush(stdin);
        reponse = getchar();

        if(reponse == 'E'){
            reponse_e(N,colonne,Tab, jaune);
        }

        if(reponse == 'P'){
            reponse_p(N,colonne,Tab, jaune);
        }

    }while(reponse != 'P' && reponse != 'E');
}

int reponse_p(int N, int colonne, char Tab[40][40], int couleur){
    int i,j,k;
    do{
        do{
            printf("\nQuelle colonne ? : Choisissez un nombre de 1 a %d\n",N);
            scanf("%d",&colonne);
        }while(colonne > N || colonne < 1);

        colonne = colonne-1;

        i=N-1;

        while(Tab[i][colonne] != '_' && i>=0){
            i--;
        }

        if(i < 0){
            printf("Desole, la colonne est entierement remplie, veuillez en choisir une autre.\n");
        }
        else
            for (j = 0;j < N;j++){
                for (k = 0; k < N; k++){
                    Tab[i][colonne] = couleur;
                    printf("%3c", Tab[j][k]);
                }
                printf("\n");
            }
    }while(i<0);
}

int reponse_e(int N, int colonne, char Tab[40][40], int couleur){

    int i,j,k;
    char reponse;
    reponse = 'O';

    do{
        do{
            printf("\nA quelle colonne souhaitez-vous retirer un jeton ? : Choisissez un nombre de 1 a %d.\n",N);
            scanf("%d",&colonne);
        }while(colonne > N || colonne < 1);


        colonne = colonne-1;

        i=N-1;

        while(Tab[i][colonne] != '_' && i>=0){
            i--;
        }
        i = i+1;

        if(Tab[i][colonne]== couleur){
            Tab[i][colonne] ='_';
            printf("Jeton retire !\n");

            for (j = 0;j < N;j++){
                for (k = 0; k < N; k++){
                    printf("%3c", Tab[j][k]);
                }
                printf("\n");
            }
        }
        else{
            printf("Vous ne pouvez pas retirer de jeton ici !\n\n");
            do{
                printf("Souhaitez-vous finalement placer un jeton ?\n\nOui : O\nNon : N");
                fflush(stdin);
                reponse = getchar();

            }while(reponse != 'O' && reponse != 'N');

            if (reponse == 'O'){
                reponse_p(N,colonne,Tab,couleur);
            }
        }
    }while(reponse != 'O');



}