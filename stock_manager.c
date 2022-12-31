#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "Produit.h"
#include "Affichage.h"

int main()
{
    int choix;
   char rep[4] ;
    do
    {
        int menu();
        switch(menu())
        {
        case 1:
            printf("vous avez choisit ajouter\n");
            Ajouter();
            break;
        case 2:
            printf("vous avez choisit Afficher description\n" );
            affdes();
            break;
        case 3:
            printf("vous avez choisit Supprimer un produit\n");
            supp();
            break;
        case 4:
            printf("vous avez choisit Modifier un produit \n");
            modif ();
            break;
        case 5:
            system("cls");
            affichage(5);
            printf(" donner le reference a chercher : ");
            int id;
            scanf("%d",&id);
            //printf("%d",recherche(id));
            if (recherche(id)== 1)
            {
                printf(" le Produit est dans le stock\n");
            }
            else
            {
                printf(" Le produit n existe pas dans le stock\n");
            }
            break;
        case 6:
            printf(" vous avez choisit afficher le stock.\n");
            aff_stock();
            break;
        //**********************************************************************************************
        case 7:
            historique();
            break;
        case 8:
        	system("cls");
    		affichage(12);
    		system("exit");

        }
        printf("\n voulez-vous continuer oui/non : ");
        gets(rep);
        fflush(stdin);
    }while(rep[0]=='o');
    system("cls");
    affichage(12);
    system("exit");

}
