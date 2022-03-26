#ifndef LIVRE_H_INCLUDED
#define LIVRE_H_INCLUDED
#include "membre.h"

typedef struct {
    char titre[50];
    char auteur [20];
    char code[8];
    int nbrEx;       //nbr d'exemplaire
    int nbrExDisp;
}bd_livres;

bd_livres * StockageL(bd_livres * ListL, int L);
void EcrireFL(bd_livres * ListL, int L);
void convertir(int n,bd_livres * ListL, int L);
void AfficheL(bd_livres * ListL, int L);
bd_livres * TriL(bd_livres * ListL, char c, int L);     // tri en fonction des critères
void RechercherAff_L(bd_livres * ListL,char choix,int L); // Recherche un livre selon critère et affiche le livre
void AjouterL(bd_livres * ListL,int *L);  // Ajoute si il existe pas
void SuppL(bd_livres * ListL,int *L);    // Si le livre n'est emprunter par personne

#endif // LIVRE_H_INCLUDED
