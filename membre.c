#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "membre.h"
#include "livre.h"

bd_membres * StockageM(bd_membres * ListM, int M){    /// va stocker les informations du fichierM dans un tableau dyna de struc membre
    int i;

    ListM =realloc(ListM,(sizeof(bd_membres)*M)); // realloue avec la taille de M qui change si c'est la cas

    FILE *FicAdres = fopen("FichierAdres.txt", "r+");
    if (FicAdres == NULL) // Vérifie que le fichier est ouvert (FicM de base est un pointeur)
        exit(1);

        fgets(ListM[0].adresse,50,FicAdres);     //Juste pour sauter la premiere ligne du fichier
     for(i=0;i<M;i++){
        fgets(ListM[i].adresse,50,FicAdres);

    }

    fclose(FicAdres);

    FILE *FicM = fopen("FichierM.txt", "r");
    if (FicM == NULL) // Vérifie que le fichier est ouvert (FicM de base est un pointeur)
        exit(1);
    fscanf(FicM,"%d",&M);
    for(i=0;i<M;i++){
       fscanf(FicM,"%s %s %s %s",ListM[i].prenom,ListM[i].nom,ListM[i].metier,ListM[i].mail);
       fscanf(FicM,"%s %s %s",ListM[i].listpret[0].code,ListM[i].listpret[1].code,ListM[i].listpret[2].code);
       fscanf(FicM,"%d %d %d",&ListM[i].listpret[0].DateR.jour,&ListM[i].listpret[0].DateR.mois,&ListM[i].listpret[0].DateR.annee);
       fscanf(FicM,"%d %d %d",&ListM[i].listpret[1].DateR.jour,&ListM[i].listpret[1].DateR.mois,&ListM[i].listpret[1].DateR.annee);
       fscanf(FicM,"%d %d %d",&ListM[i].listpret[2].DateR.jour,&ListM[i].listpret[2].DateR.mois,&ListM[i].listpret[2].DateR.annee);

   }
fclose(FicM);

return ListM;
}

/// AFFICHE LISTE DE MEMBRES ///
void AfficherM(bd_membres * ListM, int M){
    int i,n,j;
    char nom[50];
    bd_membres ordre;
/// CLASSER PAR ALPHABETIQUE ///

for (i=0;i<M;i++){
    for(j=i;j<M;j++){
        strcpy(nom,ListM[i].nom);        //copie ListM[i].nom dans nom
        n=strcmp(nom,ListM[j].nom);      // n = (s1,s2) positif si s2<s1

        if (n>0){
            ordre = ListM[i];
            ListM[i] = ListM[j];   // copie case de départ dans "ordre"
            ListM[j] = ordre;      // on copie le mot avec alphabet + petit dans la case de départ
                                   // on copie la case de départ (copié plus tôt dans "ordre") dans la case ou il y avait le mot
                                   // En clair, on interchange la case de départ avec le mot dont l'alphabet est plus petit
        }
    }
  }
    for(i=0;i<M;i++){

        printf("\n%s %s\n",ListM[i].nom,ListM[i].prenom);
        printf("%s\n",ListM[i].metier);
        printf("%s\n",ListM[i].mail);
        printf("%s\n",ListM[i].adresse);
        for(j=0;j<3;j++){
            if (ListM[i].listpret[j].code[0]!=47){    // Si différent de "/" ca veut dire le livre est emprunté alors on affiche les livre
                    printf("Code livre : %s Rendre avant : %d/%d/%d\n",ListM[i].listpret[j].code,ListM[i].listpret[j].DateR.jour,ListM[i].listpret[j].DateR.mois,ListM[i].listpret[j].DateR.annee);
            }

        }
        printf("\n-------------------------------------------------------\n");
    }
}

/// COMPARE LES DATES ///
int compareDates(date d1, date d2){

    int n; //prend 0 si d1=d2, 1 si d1>d2, et −1 si d1<d2

    if(d1.annee<d2.annee)
        n = -1;
    else if (d1.annee>d2.annee)
        n = 1;
    else if(d1.mois<d2.mois)
        n = -1;
    else if (d1.mois>d2.mois)
        n = 1 ;
    else if(d1.jour<d2.jour)
        n = -1;
    else if (d1.jour>d2.jour)
        n = 1;
    else
        n = 0;
    return n;
}

/// AJOUTE UN MEMBRE ///
void AjouterM(bd_membres * ListM, int *M){
    char mot[50];
    char mot2[50];
    int i,k=0;
    printf("Saisir le nom :");
    scanf("%s",&mot);
    printf("Saisir le prenom :");
    scanf("%s",&mot2);

    for(i=0;i<*M;i++){
        if((strcmp(ListM[i].nom,mot)==0)&&(strcmp(ListM[i].prenom,mot2)==0)){ //Compare avec la liste de membre
            printf("\nCe membre existe deja ! \n");
            k++;
        }
    }
    if(k==0){                               //Si k n'est pas accrémenter k=0 et il n'y a pas de doublons

    FILE *ficM = fopen("FichierM.txt", "a");  // écrire à la fin du fichier
    if (ficM == NULL)
        exit(1);

    fprintf(ficM,"\n%s",mot2); //le prenom
    fprintf(ficM," %s",mot); //le nom

    printf("Saisir le metier :");
    scanf("%s",&mot);                           // METIER
    fprintf(ficM," %s",mot);

    printf("Saisir le mail :");                //MAIL
    scanf("%s",&mot);
    fprintf(ficM," %s",mot);

    fprintf(ficM,"\n/ / /");                   //POUR LES PRETS
    fprintf(ficM,"\n0 0 0");
    fprintf(ficM,"\n0 0 0");
    fprintf(ficM,"\n0 0 0");

   fclose(ficM);

   FILE *FicAdres = fopen("FichierAdres.txt", "a");
   if (FicAdres == NULL)
        exit(1);

   printf("Saisir votre adresse :");              //ADRESSE
   getchar();
   gets(mot);
   fprintf(FicAdres,"\n");
   fputs(mot,FicAdres);

   fclose(FicAdres);

    printf("\nLe membre a bien ete ajoute !\n");
    *M=*M+1;                                   // Puisque le membre a ete ajouter on accremente M

    FILE *FicM = fopen("FichierM.txt", "r+"); // LIRE ET ECRIRE DANS LE FICHIER EXISTANT
    if (FicM == NULL)
        exit(1);
    fprintf(FicM,"%d",*M);           //On copie la nouvelle valeur de M dans le fichier

    fclose(FicM);
    }
}

/// SUPPRIMER UN MEMBRE ///
void SuppM(bd_membres * ListM, int *M){
    int i,j,k=0;
    char nom[40];
    char prenom[40];
    printf("\nVoici les membres pouvant etre supprimer :\n");

    for(i=0;i<*M;i++){

        if (ListM[i].listpret[0].code[0]==47){    // Si dans liste pret le premier élément dans code est '/' ca veut dire membre n'a pas emprunter de livre

             printf("\n%s %s\n",ListM[i].nom,ListM[i].prenom);
             printf("%s\n",ListM[i].metier);                            //Affiche les membres pouvant être supprimés
             printf("%s\n",ListM[i].mail);
             printf("%s",ListM[i].adresse);
             printf("\n-------------------------------------------------------\n");
             }
    }
    printf("\n Veuillez saisir le nom et le prenom du membre a supprimer\n");
    printf("\nNom : ");
    scanf("%s",&nom);
    printf("Prenom : ");
    scanf("%s",&prenom);

     /// On copie les éléments du dernier membre dans la case du membre à supprimer///
    for(i=0;i<*M;i++){
        if((strcmp(ListM[i].nom,nom)==0)&&(strcmp(ListM[i].prenom,prenom)==0)&&(ListM[i].listpret[0].code[0]==47)){
            k=1;                                     //entre dans la boucle et accrémente k si les nom prenom existe dans la liste
            strcpy(ListM[i].nom,ListM[*M-1].nom);    // et si il n'a rien emprunté, sinon k non accrémenter
            strcpy(ListM[i].prenom,ListM[*M-1].prenom);
            strcpy(ListM[i].metier,ListM[*M-1].metier);
            strcpy(ListM[i].mail,ListM[*M-1].mail);
            strcpy(ListM[i].adresse,ListM[*M-1].adresse);

            for(j=0;j<3;j++){
                strcpy(ListM[i].listpret[j].code,ListM[*M-1].listpret[j].code);
                ListM[i].listpret[j].DateR.annee=ListM[*M-1].listpret[j].DateR.annee;
                ListM[i].listpret[j].DateR.mois=ListM[*M-1].listpret[j].DateR.mois;
                ListM[i].listpret[j].DateR.jour=ListM[*M-1].listpret[j].DateR.jour;
            }
        }

    }

    if (k==1){
    *M=*M-1;            //On change directement la valeur de M par adresse
    ///On recopie toute la listM dans le fichier///
    ListM =realloc(ListM,(sizeof(bd_membres)*(*M)));
    EcrireFM(ListM, *M);

    printf("\nLe membre a bien ete supprime !");
    }

    else {    //k non accrémenter donc la saisie est pas correcte
        printf(" \nVotre saisie est invalide !");
    }

}

void Emprunter(bd_membres * ListM, int M,bd_livres * ListL,int L){
    int i,j,n=0,k,h=0;
    int jour,mois,annee;
    char nom[40];
    char prenom[40];
    char titre[50];
    char auteur[40];

    k=0;
    printf("Saisir votre nom : ");
    scanf("%s",&nom);
    printf("Saisir votre prenom : ");
    scanf("%s",&prenom);

    for(i=0;i<M;i++){          //entre si le membre existe, et si il a une case d'emprunt disponible
        if((strcmp(ListM[i].nom,nom)==0)&&(strcmp(ListM[i].prenom,prenom)==0)&&(ListM[i].listpret[2].code[0]==47))   {
            k=1;
            printf("Saisir le titre du livre : ");
            getchar();
            gets(titre);
            printf("Saisir le nom de l'auteur : ");
            gets(auteur);
            for(j=0;j<L;j++){        //Si le livre existe et si y a des livres disponible ( donc diff de 0)
                if((strcmp(ListL[j].titre,titre)==0)&&(strcmp(ListL[j].auteur,auteur)==0)&&(ListL[j].nbrExDisp!=0)){ /// VERIFICATION
                   k=2;
                   while((h<3)&&(n==0)){                        //Pour parcourir les prets
                      if(ListM[i].listpret[h].code[0]==47){
                         strcpy(ListM[i].listpret[h].code,ListL[j].code);       //Remplie LE CODE des prets du membre

                         ListL[j].nbrExDisp=(ListL[j].nbrExDisp)-1;             //Le nombre de livre dispo diminu

                         printf("\nSaisir la date du jour : \n");
                         printf("Jour : ");
                         scanf("%d",&jour);
                         printf("Mois : ");
                         scanf("%d",&mois);
                         printf("Annee : ");
                         scanf("%d",&annee);

                         ListM[i].listpret[h].DateR.jour = jour;
                         ListM[i].listpret[h].DateR.mois = mois+1;            //On lui donne 1 mois pour rendre
                         ListM[i].listpret[h].DateR.annee = annee;

                        n=1;                                            //Sort de la boucle
                      }
                      else{
                        h=h+1;                     //sinon on continu dans la boucle jusuq'à qu'il y a une place vide dans liste prets
                      }
                   }
            }
        }
      }
    }
    if(k==0){  // k=0 ca veut dire qu'il n'est pas rentrer dans la premiere boucle concernant les membres
        printf("\nCe membre n'existe pas ou bien vous ne pouvez plus emprunter !\n");
    }
    else if(k==1){  // ca veut dire il n'est pas rentrer dans la boucle concernant le livre
        printf("\nCe livre n'existe pas ou n'est plus disponible\n");
    }
        /// On recopie les informations du tableau dans le fichier ///
    else{   //ici k=2
            EcrireFM(ListM,M);
            EcrireFL(ListL,L);
           printf("Le livre est emprunter !");
    }

}

void RendreL(bd_membres * ListM, int M,bd_livres * ListL,int L){
    int i,j,n=0,k;
    char nom[40];
    char prenom[40];
    char code[10];
    char R[1]={'/'};
    date Date;
    printf("Veuillez saisir la date d'aujourd'hui\n");
    printf("Le jour : ");
    scanf("%d",&Date.jour);
    printf("Le mois : ");
    scanf("%d",&Date.mois);
    printf("L'annee : ");
    scanf("%d",&Date.annee);

    k=0;
    printf("Saisir votre nom : ");
    scanf("%s",&nom);
    printf("Saisir votre prenom : ");
    scanf("%s",&prenom);

    for(i=0;i<M;i++){          //entre si le membre existe
        if((strcmp(ListM[i].nom,nom)==0)&&(strcmp(ListM[i].prenom,prenom)==0))   {
            k=1;
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
            printf("\nSaisir le code du livre : ");
            getchar();
            gets(code);
            for(j=0;j<3;j++){   // Verif que le code est bien dans la list pret du membre
                   if((strcmp(ListM[i].listpret[j].code,code)==0)){ //entre si le livre est dans ses emprunts
                      k=2;

                      n = compareDates(Date, ListM[i].listpret[j].DateR);
                      if(n==1){
                        printf("Votre livre est en retard !\n");
                      }
                      strcpy(ListM[i].listpret[j].code,R); // copie '/' a la place du code du livre dans listpret
                      ListM[i].listpret[j].DateR.jour = 0;
                      ListM[i].listpret[j].DateR.mois = 0;            //initialise tout à 0
                      ListM[i].listpret[j].DateR.annee = 0;
                   }
            }
            for(j=0;j<L;j++){ // On modifie le fichier Livre
                if(k==2){     //ca veut dire le livre existait bien dans les pret du membres
                    ListL[j].nbrExDisp=(ListL[j].nbrExDisp)+1;      //Le nombre de livre dispo AUGMENTE

                }

            }

        }
    }
    if(k==0){  // k=0 ca veut dire qu'il n'est pas rentrer dans la premiere boucle concernant les membres
        printf("\nCe membre n'existe pas ou bien vous ne pouvez plus emprunter !\n");
    }
    else if(k==1){  // ca veut dire il n'est pas rentrer dans la boucle concernant le code
        printf("\nLe code est ne correspond pas a vos livres !\n");
    }
        /// On recopie les informations du tableau dans le fichier ///
    else{   //ici k=2
            EcrireFM(ListM,M);
            EcrireFL(ListL,L);
           printf("\nLe livre est rendu !");
    }

}



void EcrireFM(bd_membres * ListM, int M){
    int i,j;

    FILE *FicM = fopen("FichierM.txt", "w"); // supprimer tous les elements precedents et ecrit dans le fichier
    if (FicM == NULL)
        exit(1);

    fprintf(FicM,"%d",M);   // COPIE M = taille de membre

    for(i=0;i<M;i++){      // copie le prenom nom mail
        fprintf(FicM,"\n%s %s %s %s\n",ListM[i].prenom,ListM[i].nom,ListM[i].metier,ListM[i].mail);
        for(j=0;j<3;j++){     //copie les prets
           fprintf(FicM,"%s ",ListM[i].listpret[j].code);
        }
        for(j=0;j<3;j++){     //copie les dates
             fprintf(FicM,"\n%d %d %d",ListM[i].listpret[j].DateR.jour,ListM[i].listpret[j].DateR.mois,ListM[i].listpret[j].DateR.annee);
        }
    }
    fclose(FicM);

    FILE *FicA = fopen("FichierAdres.txt", "w");
    if (FicA == NULL)
        exit(1);

    fprintf(FicA,"%d\n",M);           // COPIE M = taille de membre

    for(i=0;i<M;i++){                //COPIE ADRESSE
       fputs(ListM[i].adresse,FicA);
    }

    fclose(FicA);
}


