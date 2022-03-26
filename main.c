#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "membre.h"
#include "livre.h"

int main(){
    int L,M,n,c,k;
    char choix;
    FILE *FicM = fopen("FichierM.txt", "r");        /// On prend le M du fichier
                                                 // Si nous avons ajouté ou supp un membre et fermer le programme, le M du fichier contient le nombre de membre modifier
    if (FicM == NULL)           // Vérifie que le fichier est ouvert (FicM de base est un pointeur)
        exit(1);
    fscanf(FicM,"%d",&M);
    fclose(FicM);

    FILE *FicL = fopen("FichierL.txt","r");
    if (FicL == NULL)
        exit(1);
    fscanf(FicL,"%d",&L);
    fclose(FicL);

    bd_livres *Liste_L;          //liste dynamique de livre
    bd_membres *Liste_M;         //liste dynamique de membre
    Liste_M = malloc(sizeof(bd_membres)*M);
    Liste_L = malloc(sizeof(bd_livres)*L);
    Liste_L = StockageL(Liste_L,L);
    Liste_M = StockageM(Liste_M,M);

    printf("\n            BIENVENUE SUR LA BIBLIOTHEQUE EN LIGNE MA !\n");

while (k!=0){
    printf("\n\n1. Pour le menu de lecture\n" );
    printf("2. Pour le menu de modification\n");
    printf("3. Pour quitter\n");
    printf("\nSaisir le numero correspondant : ");
    while ((scanf("%d", &n) != 1)||((n!=1)&&(n!=2)&&(n!=3))) {
        printf("Erreur ! Veuillez saisir 1 pour le menu de lecture et 2 pour le menu de modification : ");
		while ((c=getchar()) != '\n' && c != EOF);
    }
    if (n==1){
            printf("\nA. Consulter la liste les membres\n");
            printf("B. Afficher la liste des livres selon un des ordres suivants : code, titre, auteur\n");
            printf("C. Rechercher des informations sur un livre\n");
            printf("D. Affichez la liste des livres empruntes dont la date de retour a ete depassee\n");
            printf("\n");

            do{
            printf("Saisir la lettre correspondante : ");
            scanf(" %c", &choix); }
            while(choix<'A'|| choix>'D');                            /// AFFICHER MEMBRE
            if (choix == 'A'){
                AfficherM(Liste_M, M);
            }
            if (choix == 'B'){
                    printf(" A. Afficher selon les codes\n ");
                    printf("B. Afficher selon les titres\n ");
                    printf("C. Afficher selon les auteurs\n ");              /// AFFICHER LIVRE PAR CLASSE
                    printf("\n");
                    do{
                    printf("Saisir la lettre correspondante : ");
                    scanf(" %c", &choix); }
                    while(choix<'A'|| choix>'C');

                    Liste_L = TriL(Liste_L,choix,L);
                    AfficheL(Liste_L, L);

            }
            if (choix == 'C'){
                    printf("A. Rechercher par code\n");
                    printf("B. Rechercher par titre\n");
                    printf("C. Rechercher par auteur\n");                       /// RECHERCHER LIVRE PAR CLASSE
                    printf("\n");
                    do{
                    printf("Saisir la lettre correspondante : ");
                    scanf(" %c", &choix); }
                    while(choix<'A'|| choix>'C');
                    Liste_L = TriL(Liste_L,choix,L);
                    RechercherAff_L(Liste_L, choix,L);
            }
            if (choix == 'D'){
                   RetardL(Liste_L, L, Liste_M, M);
            }
    }
    if (n==2){
            printf("\nA. Ajouter un nouveau membre \n");
            printf("B. Ajouter un nouveau livre\n");
            printf("C. Supprimer un adherent ou un livre\n");
            printf("D. Enregistrer un nouvel emprunt\n");
            printf("E. Rendre un livre\n");
            printf("\n");
            do{
            printf("Saisir la lettre correspondante : ");
            scanf(" %c", &choix); }
            while(choix<'A'|| choix>'E');

            if (choix=='A'){
               AjouterM(Liste_M, &M);                // Cette fonction ne fait que ecrire dans le fichier
               Liste_M = StockageM(Liste_M,M);       //réalloc avec le membre en plus
            }                                        //donc on doit rappeler la fonction Stockage pour restocker les informations
            if (choix=='B'){                         // dans le tableau
                AjouterL(Liste_L,&L);               //De même pour AjouterL
                Liste_L= StockageL(Liste_L,L);
            }
            if (choix=='C'){
                printf("\nA. Supprimer un membre\nB. Supprimer un livre\n ");
                do{
                printf("Saisir la lettre correspondante : ");
                scanf(" %c", &choix); }
                while(choix<'A'|| choix>'B');
                if (choix=='A'){
                    SuppM(Liste_M, &M);
                }

                if (choix=='B'){
                   SuppL(Liste_L,&L);
                }
            }
            if (choix=='D'){
                    Emprunter(Liste_M, M,Liste_L, L);
                }
            if (choix=='E'){
                RendreL(Liste_M,M,Liste_L,L);
            }
    }
    if (n==3) {
        printf("\n                   AUREVOIR !\n");
        k=0;
        free(Liste_M);
        free(Liste_L);
    }


}
  return 0;
}


/* Met un premier élément dans la 1er ligne du fichierAdress et Pret qui n'ont pas de role utile en soit
--> C'est pour l'affichage avec le (\n) lorsqu'on copie les element des tableaux dans le fichier et inversement
Car chaque retour à la ligne et espace a un impact
en mettant un premier élément à tous les fichiers :
1.ils seront tous au même niv
2.Pour ajouter il suffit de faire \n en debut de mot, sans qu'il n'y ait un espace vide à la première ligne (ca aurait
été le cas si il n'y avait aucun élément en premiere ligne, or ici on met un chiffre "inutil".

*/
