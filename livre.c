#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "membre.h"
#include "livre.h"

bd_livres * StockageL(bd_livres *ListL, int L){
    int i;
    ListL = realloc(ListL,(sizeof(bd_membres)*L));

    FILE *FicP = fopen("FichierPret.txt", "r");
    if (FicP == NULL) // Vérifie que le fichier est ouvert (FicM de base est un pointeur)
        exit(1);

    fscanf(FicP,"%d",&i);   // Pour faire sauter la première ligne
    for(i=0;i<L;i++){
            fscanf(FicP,"%s %d %d",ListL[i].code,&ListL[i].nbrEx, &ListL[i].nbrExDisp);
        }
        fclose(FicP);

    FILE *FicL = fopen("FichierL.txt", "r");
    if (FicL == NULL) // Vérifie que le fichier est ouvert (FicM de base est un pointeur)
        exit(1);

    fscanf(FicL,"%d",&L);
    for(i=0;i<L;i++){
        fscanf(FicL,"%s",ListL[i].titre);
        fscanf(FicL,"%s",ListL[i].auteur);

        }
        fclose(FicL);
        convertir(0,ListL, L);  //Convertie les "/" en espace


    return ListL;
}

/// AFFICHE LISTE DE LIVRE ///
void AfficheL(bd_livres * ListL, int L){
    int i;
     convertir(0,ListL, L);            //Convertie les "/" en espace pour l'affichage

    for(i=0;i<L;i++){
        printf("\nTitre : %s\n",ListL[i].titre);
        printf("Auteur : %s\n",ListL[i].auteur);
        printf("Code : %s\n",ListL[i].code);
        printf("Nombre d'exemplaires disponibles : %d\n",ListL[i].nbrExDisp);
        printf("Nombre d'exemplaires total : %d\n",ListL[i].nbrEx);

    }
}

/// TRIER SELON UN ORDRE CHOISIE ///
bd_livres * TriL(bd_livres * ListL, char c, int L){
    int i,n,j;
    char nom[50];
    bd_livres ordre;
    if(c =='A'){                                   // CODE
        for(i=0;i<L;i++){
            for(j=i;j<L;j++){
                strcpy(nom,ListL[i].code);
                n=strcmp(nom,ListL[j].code);
                if (n>0){
                    ordre = ListL[i];
                    ListL[i] = ListL[j];
                    ListL[j] = ordre ;

                }
             }
        }
    }
    else if (c =='B'){                           // TITRE
       for (i=0;i<L;i++){
          for(j=i;j<L;j++){
              strcpy(nom,ListL[i].titre);
               n=strcmp(nom,ListL[j].titre);

               if (n>0){
                  ordre = ListL[i];
                  ListL[i] = ListL[j];
                  ListL[j] = ordre;
                }
           }
       }
    }
    else {                                        // AUTEUR
       for (i=0;i<L;i++){
          for(j=i;j<L;j++){
              strcpy(nom,ListL[i].auteur);
               n=strcmp(nom,ListL[j].auteur);

               if (n>0){
                  ordre = ListL[i];
                  ListL[i] = ListL[j];
                  ListL[j] = ordre;
                }
           }
       }

    }

 return ListL;
}

/// RECHERCHE PAR TYPE ///
void RechercherAff_L(bd_livres * ListL,char c,int L){
    char mot[50];
    int i,j;
    if (c =='A'){
        j=0;
        printf("Veuillez saisir le code du livre : ");
        scanf("%s",&mot);
        for(i=0;i<L;i++){
            if (strcmp(mot,ListL[i].code)==0){            //compare la saisie de l'utilisateur avec les codes de la liste des livres
                printf("\nTitre : %s\n",ListL[i].titre);
                printf("Auteur : %s\n",ListL[i].auteur);
                printf("Code : %s\n",ListL[i].code);
                printf("Nombre d'exemplaires disponibles : %d\n",ListL[i].nbrExDisp);
                printf("Nombre d'exemplaires total : %d\n",ListL[i].nbrEx);
                j=1;
            }
        }
        if (j==0){
            printf("Ce livre n'existe pas ! \n");
        }
    }
    else if (c =='B'){
        j=0;
        printf("Veuillez saisir le titre du livre : ");
        getchar();
        gets(mot);                                        //scanf fait des lecteures formater (%d...) alors que gets comprend les espace
        for(i=0;i<L;i++){                                 //en mettant getchar problème de mémoire tampon régler (laisse le temps)
            if (strcmp(mot,ListL[i].titre)==0){
                printf("\nTitre : %s\n",ListL[i].titre);
                printf("Auteur : %s\n",ListL[i].auteur);
                printf("Code : %s\n",ListL[i].code);
                printf("Nombre d'exemplaires disponibles : %d\n",ListL[i].nbrExDisp);
                printf("Nombre d'exemplaires total : %d\n",ListL[i].nbrEx);
                j=1;
            }
        }
        if (j==0){
            printf("Ce livre n'existe pas ! \n");
        }
    }
    else {
        j=0;
        printf("Veuillez saisir le nom de l'auteur : ");
        getchar();
        gets(mot);
        for(i=0;i<L;i++){
            if (strcmp(mot,ListL[i].auteur)==0){
                printf("\nTitre : %s\n",ListL[i].titre);
                printf("Auteur : %s\n",ListL[i].auteur);
                printf("Code : %s\n",ListL[i].code);
                printf("Nombre d'exemplaires disponibles : %d\n",ListL[i].nbrExDisp);
                printf("Nombre d'exemplaires total : %d\n",ListL[i].nbrEx);
                j=1;
            }
        }
        if (j==0){
            printf("Ce livre n'existe pas ! \n");
        }
    }
}

/// AFFICHE LES LIVRES EN RETARD ///
void RetardL(bd_livres * ListL,int L, bd_membres * ListM, int M){
    int i,n,j,k,l,m;
    date Date;
    printf("Veuillez saisir la date d'aujourd'hui\n");
    printf("Le jour : ");
    scanf("%d",&Date.jour);
    printf("Le mois : ");
    scanf("%d",&Date.mois);
    printf("L'annee : ");
    scanf("%d",&Date.annee);

    for(i=0;i<M;i++){
        m=0;                        // Pour afficher le membre une seule fois
        for(k=0;k<3;k++){
            n = compareDates(Date, ListM[i].listpret[k].DateR);
            if (n==1){                         // 1 si d1>d2 la date de ojd plus grande
                for(l=0;l<L;l++){
                    if(strcmp(ListM[i].listpret[k].code,ListL[l].code)==0){  //compare le code dans membre et dans le livre
                       m=1;
                       printf("\n     LIVRE EN RETARD :\n");
                       printf("\nTitre : %s\n",ListL[l].titre);
                       printf("Auteur : %s\n",ListL[l].auteur);
                       printf("Code : %s\n",ListL[l].code);
                       printf("Nombre d'exemplaires disponibles : %d\n",ListL[l].nbrExDisp);
                       printf("Nombre d'exemplaires total : %d\n",ListL[l].nbrEx);
                     }
                 }
             }
         }
            if (m==1){                                             //Affiche le membre si au moins 1 de ses livre sont en retard
             printf("\n     INFORMATION DU MEMBRE :\n");
             printf("\n%s %s\n",ListM[i].nom,ListM[i].prenom);
             printf("%s\n",ListM[i].metier);
             printf("%s\n",ListM[i].mail);
             printf("%s",ListM[i].adresse);
             for(j=0;j<3;j++){
                if (ListM[i].listpret[j].code[0]!=47){    // Si différent de "/" ca veut dire le livre est emprunté alors on affiche les livre
                    printf("Code livre : %s Rendre avant : %d/%d/%d\n",ListM[i].listpret[j].code,ListM[i].listpret[j].DateR.jour,ListM[i].listpret[j].DateR.mois,ListM[i].listpret[j].DateR.annee);
                }
             }
             printf("\n-------------------------------------------------------\n");
        }

    }
}


/// AJOUTE UN LIVRE ///
void AjouterL(bd_livres * ListL,int *L){   //On pointe L pour modifier directement l'adresse sans renvoyer L
    char mot[50];
    char mot2[50];
    int i,k=0,j,l=0,m=0;

    printf("Saisir le titre du livre :");
    getchar();
    gets(mot);

    j=strlen(mot);          //Convertie les espaces en "/"
    for(i=0;i<j;i++){
           if (mot[i]==32){
               mot[i]=47;
           }
    }
    for(i=0;i<*L;i++){                         // COMPARE
        if(strcmp(ListL[i].titre,mot)==0){
            printf("\nCe livre existe deja ! \n");
            k++;
        }
    }
    if(k==0){

    FILE *ficL = fopen("FichierL.txt", "a");  // écrire à la fin du fichier
    if (ficL == NULL)
        exit(1);

    fprintf(ficL,"\n");
    fputs(mot,ficL);
    printf("Saisir le nom de l'auteur :");
    gets(mot);

    j=strlen(mot);          //Convertie les espaces en "/"
    for(i=0;i<j;i++){
           if (mot[i]==32){
               mot[i]=47;
           }
    }


    fprintf(ficL,"\n");
    fputs(mot,ficL);

    fclose(ficL);

    FILE *FicP = fopen("FichierPret.txt", "a");  // écrire à la fin du fichier
    if (FicP == NULL)
        exit(1);

    printf("Quel est le theme du livre :\n\n");
    printf("-ROM : ROMAN \n-BAD : Bande Dessinee \n-THE : THEATRE\n-POE : POEME\n\nSaisir : ");
    scanf("%s",&mot2);
    mot2[3]='-';              // Le tiret à la position 3
    j=1;                      // à 1 et non 0 car on veut le nombre total de livre dans le thème +1, si c'est 0 on aura 2fois le même code
    for(i=0;i<*L;i++){
        if ((ListL[i].code[0]==mot2[0])&&(ListL[i].code[1]==mot2[1])&&(ListL[i].code[2]==mot2[2])){  //Compare les 3 premieres lettres si c'est le cas on accrémente
            j++;
            if (j==10){
                j=0;
                l++;
                if (l==10){
                    l=0;
                    m++;
                }
            }
        }
    }

    fprintf(FicP,"\n%s",mot2);    //On copie les 3 lettres et le tiret
    fprintf(FicP,"%d%d%d",m,l,j); //On copie les chiffres à la fin dans le fichier

    printf("\nSaisir le nombre total d'exemplaires : ");
    scanf("%d",&i);
    fprintf(FicP," %d %d",i,i);
    fclose(FicP);

    printf("\nLe livre a bien ete ajoute !\n");
    *L=*L+1;                                   // Puisque le membre a ete ajouter on accremente L

    FILE *FicL = fopen("FichierL.txt", "r+"); // LIRE ET ECRIRE DANS LE FICHIER EXISTANT
    if (FicL == NULL)
        exit(1);
    fprintf(FicL,"%d",*L);           //On copie la nouvelle valeur de L dans le fichier à la premiere ligne

    fclose(FicL);
    }
}


/// SUPPRIMER UN LIVRE ///
void SuppL(bd_livres * ListL,int *L){
    int i,k=0;
    char auteur[40];
    char titre[40];
    printf("\nVoici les livres pouvant etre supprimer :\n");

    for(i=0;i<*L;i++){

        if (ListL[i].nbrEx==ListL[i].nbrExDisp){    // Si dans liste pret explaire dispo = nombre exemplaire total
                printf("\nTitre : %s\n",ListL[i].titre);
                printf("Auteur : %s\n",ListL[i].auteur);
                printf("Code : %s\n",ListL[i].code);
                printf("Nombre d'exemplaires disponibles : %d\n",ListL[i].nbrExDisp);
                printf("Nombre d'exemplaires  : %d\n",ListL[i].nbrEx);
             printf("\n-------------------------------------------------------\n");
             }
    }
    printf("\n Veuillez saisir le nom de l'auteur et le titre du livre a supprimer\n");
    printf("\nAuteur : ");
    getchar();
    gets(auteur);
    printf("Titre : ");
    gets(titre);

     /// On copie les éléments du dernier livre dans la case du livre à supprimer///
    for(i=0;i<*L;i++){
        if((strcmp(ListL[i].auteur,auteur)==0)&&(strcmp(ListL[i].titre,titre)==0)&&(ListL[i].nbrEx==ListL[i].nbrExDisp)){
            k=1;                                     //entre dans la boucle et accrémente k si les auteur titre existe dans la liste
            strcpy(ListL[i].auteur,ListL[*L-1].auteur);    // et si aucun livre est emprunter, sinon k non accrémenter
            strcpy(ListL[i].titre,ListL[*L-1].titre);
            strcpy(ListL[i].code,ListL[*L-1].code);
            }
        }

    if (k==1){
    *L=*L-1;            //On change directement la valeur de L par adresse
    ///On recopie toute la listL dans le fichier///
    ListL =realloc(ListL,(sizeof(bd_livres)*(*L)));            //On réalloue l'espace
    EcrireFL(ListL,*L);

    printf("Le livre a bien ete supprime ! ");
    }

    else {    //k non accrémenter donc la saisie est pas correcte
        printf(" \nVotre saisie est invalide !");
    }
}

/// COPIE LES ELEMENTS DU TABLEAU DANS FICHIERL
void EcrireFL(bd_livres * ListL, int L){
    int i;
    FILE *FicL = fopen("FichierL.txt", "r+"); //On ecrit et lit
    if (FicL == NULL)
        exit(1);

    fprintf(FicL,"%d",L);                     //On change le L dans le fichier

    convertir(1,ListL,L);                         // ESPACE EN "/" pour copier sur le fichier

    for(i=0;i<L;i++){
    fprintf(FicL,"\n");
    fputs(ListL[i].titre,FicL);      // TITRE
    fprintf(FicL,"\n");
    fputs(ListL[i].auteur,FicL);     //AUTEUR
    }

    fclose(FicL);

    FILE *FicP = fopen("FichierPret.txt", "w");
    if (FicP == NULL)
        exit(1);

    fprintf(FicP,"%d",L);            // L = taille de liste livre
    for(i=0;i<L;i++){
        fprintf(FicP,"\n%s %d %d",ListL[i].code,ListL[i].nbrEx,ListL[i].nbrExDisp);  // copie les info du livres dans FICHIER
    }
    fclose(FicP);
    convertir(0,ListL,L); // reconvertir les "/" en espace
}

/// CONVERTI LES ESPACES EN '/' OU INVERSEMENT ///
void convertir(int n, bd_livres * ListL, int L){
    int i,j,k;
    if(n==0){

      for(i=0;i<L;i++){                      //Convertie les "/" en espace
        k=strlen(ListL[i].auteur);
        for(j=0;j<k;j++){
           if (ListL[i].auteur[j]==47){
               ListL[i].auteur[j]=32;
           }
        }
        k=strlen(ListL[i].titre);
        for(j=0;j<k;j++){
            if (ListL[i].titre[j]==47){
                ListL[i].titre[j]=32;
            }
        }
      }
    }
    else {
         for(i=0;i<L;i++){
            n=strlen(ListL[i].auteur);          //Convertie les espaces en "/"
            for(j=0;j<n;j++){
               if (ListL[i].auteur[j]==32){
                ListL[i].auteur[j]=47;
               }
             }
            n=strlen(ListL[i].titre);
            for(j=0;j<n;j++){
               if (ListL[i].titre[j]==32){
                  ListL[i].titre[j]=47;
                }
            }
         }
    }
}
