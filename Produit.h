#ifndef PRODUIT_H_INCLUDED
#define PRODUIT_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "Affichage.h"

typedef struct{
	char nom[100];
	int id;
	char cat[100];
	int qte;
	float prix;

}produit;

typedef struct
{
    int j;
    int m;
    int a;
    produit prod;
}Date;
//int choix;
int menu();
void Ajouter();
void affdes();
void supp();
void modif ();
int recherche(int id);
void aff_stock();
void historique();
int sousMenu();

#endif // PRODUIT_H_INCLUDED
