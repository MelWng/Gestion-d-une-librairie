#ifndef MEMBRE_H_INCLUDED
#define MEMBRE_H_INCLUDED
#include "livre.h"

typedef struct {
int jour;
int mois;
int annee;
}date;

typedef struct {
    char code [7] ;   /// Code du livre
    date DateR      ; /// Date de retour

}pret;

typedef struct {
    char nom[50];
    char prenom[50];
    char adresse[50];
    char mail[50];
    char metier[50];
    pret listpret[3];
}bd_membres;


int compareDates(date  d1, date  d2);
bd_membres * StockageM(bd_membres * ListM, int M); //Fonction qui stock les info dans la liste_M
void AfficherM(bd_membres * ListM, int M);
void AjouterM(bd_membres * ListM, int *M);
void EcrireFM(bd_membres * ListM, int M); // Copie les élément du tableau dans le fichier
void SuppM(bd_membres * ListM, int *M);     // Si une membre n'a rien emprunter
void Emprunter(bd_membres * ListM, int M, bd_livres * ListL,int L);
void RendreL(bd_membres * ListM, int M, bd_livres * ListL,int L);
//void FreeM(bd_membres * ListM, int M);


#endif // MEMBRE_H_INCLUDED
