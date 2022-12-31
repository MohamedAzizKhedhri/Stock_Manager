#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "Produit.h"
#include "Affichage.h"

void historique()
{
        int choix;
        //historique
        system("cls");
        choix = sousMenu();
        if (choix == 1)
        {
            //affichage du l'historique
            affichage(2);
            FILE *file;
            Date dat;
            file = fopen("historique.txt","r");
            printf(" 1- afficher l'hisorique d'un jour donne\n");
            printf(" 2- afficher l'historique mois par mois\n");
            printf(" Saisir le numero du choix SVP : ");
            scanf("%d", &choix);
            fflush(stdin);
            while (choix != 1 && choix != 2)
            {
                system("cls");
                printf("->->-> votre choix est invalide veuillez reessayer\n\n");
                printf(" 1- afficher l'hisorique d'un jour donne\n");
                printf(" 2- afficher l'historique mois par mois\n");
                printf(" Saisir le numero du choix SVP : ");
                scanf("%d", &choix);
                fflush(stdin);
            }
            if (choix == 1)
            {
                system("cls");
                printf(" donner la date du jour sous la forme jj mm aaaa : ");
                int jj,mm,aa;
                scanf("%d%d%d", &jj,&mm,&aa);
                fflush(stdin);
                while (!(jj >0 && jj <= 31) || !(mm>=1 && mm <= 12))
                {
                    system("cls");
                    printf("->->-> La date est invalide veuillez reessayer\n\n");
                    printf(" donner la date du jour sous la forme jj mm aaaa : ");
                    scanf("%d%d%d", &jj,&mm,&aa);
                    fflush(stdin);
                }
                affichage(1);
                while(fread(&dat,sizeof(Date), 1,file))
                {

                    if ((dat.j == jj) && (dat.m== mm) && (dat.a == aa))
                    {
                        printf(" %02d-%02d-%4d \t %10d \t %9s \t %20s \t %21d \t %14.2f \n",dat.j,dat.m,dat.a,dat.prod.id,dat.prod.nom,dat.prod.cat,dat.prod.qte,dat.prod.prix);
                    }
                    if ((dat.a == aa && dat.m < mm) || (dat.a < aa))
                        break;

                }



            }
            else if (choix == 2)
            {
                system("cls");
                affichage(1);
                while(fread(&dat,sizeof(Date), 1,file))
                {
                    printf(" %2d-%02d-%4d \t %10d \t %9s \t %20s \t %21d \t %14.2f \n",dat.j,dat.m,dat.a,dat.prod.id,dat.prod.nom,dat.prod.cat,dat.prod.qte,dat.prod.prix);
                }

            }



        }
        else if (choix == 2)
        {
            // effacer l'historique-----------------------------------
            FILE *file;
            file = fopen("historique.txt","w");
            fclose(file);
            // fin ---------------------------------------------------
            system("cls");
            affichage(3);
        }

        else
        {

            printf("->->-> votre choix est invalide veuillez reessayer\n\n");

        }

}

int sousMenu()
{
    affichage(8);
    printf(" 1- Afficher l'historique\n");
    printf(" 2- Effacer l'historique\n");
    printf(" Saisir le numero du choix SVP : ");
    int choix;
    scanf("%d", &choix);
    fflush(stdin);
    return choix;
}


//*********************************************************************************
int menu()
{
    system("cls");
    affichage(4);
    int choix;
    do{
        printf("\n Enter votre choix : ");
        scanf("%d",&choix);
    }while(choix<1 || choix>8 );
    return choix;
}
/////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
// --------- procedure ajouter un produit--------------
void Ajouter()
{

    int id;
    system("cls");
    affichage(7);
    printf(" Donner la referance du produit a ajouter : ");
    scanf("%d",&id);
    fflush(stdin);

    if (recherche(id)==-1)
        {

        FILE *F;
        produit prod;
        F=fopen("stock.txt","a" );
        prod.id=id;
        printf(" Donner le nom du produit : ");
        gets(prod.nom);
        fflush(stdin);
        printf(" Donner la categorie du produit : ");
        gets(prod.cat);
        fflush(stdin);
        printf(" Donner le prix du produit : ");
        float prix;
        scanf("%f",&prix);
        prod.prix=prix;
        fflush(stdin);
        int qte;
        printf(" Donner la quantite du produit a ajouter : ");
        scanf("%d",&qte);
        prod.qte=qte;
        fflush(stdin);
        fprintf(F,"\n%d\t%s\t%d\t\t%f\t%s",prod.id,prod.nom,prod.qte,prod.prix,prod.cat);
        fclose(F);
        //date----------------------------------------------
        Date dat;
        dat.prod = prod;
        time_t t = time(NULL);
        struct tm tm = *localtime(&t);
        dat.a = tm.tm_year + 1900;
        dat.m = tm.tm_mon + 1;
        dat.j= tm.tm_mday;
        //fichier historique---------------------------------
        FILE *fileDate = fopen("historique.txt", "a");
        fwrite(&dat, sizeof(Date), 1, fileDate);
        fclose(fileDate);
    }
    else
    {
        affichage(2);
        int qte;
        printf(" le produit existe deja \n");
        printf(" Donner la quantite a ajouter ou a retirer de ce produit : ");
        scanf("%d",&qte);
        fflush(stdin);
        FILE* Fich, *F;
        F=fopen("stock.txt","r");
        Fich=fopen("stock1.txt","w");

        do
        {
            produit prod;
            fscanf(F,"%d%s%d%f%s\n",&prod.id,prod.nom,&prod.qte,&prod.prix,prod.cat);
            if (id==prod.id)
            {
                //***********************
                prod.qte+= qte;
                fprintf(Fich,"%d\t%s\t%d\t\t%f\t%s \n",prod.id,prod.nom,prod.qte,prod.prix,prod.cat);
                //date----------------------------------------------
                Date dat;
                dat.prod = prod;
                dat.prod.qte = qte;
                time_t t = time(NULL);
                struct tm tm = *localtime(&t);
                dat.a = tm.tm_year + 1900;
                dat.m = tm.tm_mon + 1;
                dat.j= tm.tm_mday;
                //fichier historique---------------------------------
                FILE *fileDate = fopen("historique.txt", "a");
                fwrite(&dat, sizeof(Date), 1, fileDate);
                fclose(fileDate);
            }
            else
            {
                fprintf(Fich,"%d\t%s\t%d\t\t%f\t%s \n",prod.id,prod.nom,prod.qte,prod.prix,prod.cat);

            }
        }while(!feof(F));
        fclose(F);
        fclose(Fich);
        F=fopen("stock.txt","w");
        Fich=fopen("stock1.txt","r");
        do
                {
                    produit prod;
                    fscanf(Fich,"%d%s%d%f%s\n",&prod.id,prod.nom,&prod.qte,&prod.prix,prod.cat);
                    fprintf(F,"\n%d\t%s\t%d\t\t%f\t%s",prod.id,prod.nom,prod.qte,prod.prix,prod.cat);
                }while(!feof(Fich));
                fclose(F);
                fclose(Fich);
                Fich=fopen("stock1.txt","w");
                fclose(Fich);






    }
    affichage(3);


}
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
//----------procedure d'affichage du description d'un produit------------
void affdes()
{
    system("cls");
    affichage(9);
    FILE *F;
    F=fopen("stock.txt","r" );
    int id;
    printf(" Enter l'id du produit a afficher : ");
    scanf("%d",&id);
    fflush(stdin);
    if(recherche(id)==1)
    {
        do
    {
        produit prod;
        fscanf(F,"%d%s%d%f%s\n",&prod.id,prod.nom,&prod.qte,&prod.prix,prod.cat);
        if (id==prod.id)
        {
            printf(" ****** Description du Produit ****** \n \n");
            printf("\tId\t  : %d \n",prod.id);
            printf("\tNom\t  : %s \n",prod.nom);
            printf("\tQantite\t  : %d \n",prod.qte);
            printf("\tPrix\t  : %f \n",prod.prix);
            printf("\tCategorie : %s \n",prod.cat);

        }
    }while(!feof(F));
    fclose(F);
    }
    else{
        printf(" le produit n'existe pas ");
    }


}
///////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
// -------------------- procedure supprimer un produit -----------------

void supp()
{
    system("cls");
    affichage(11);
    char rep[4];
    int id;
    printf(" entrer la referance du produit a supprimer : ");
    scanf("%d",&id);
    fflush(stdin);
    if (recherche(id)==1);
    {
        printf("\n vous voulez vraimment supprimer ce produit oui/non ?? : ");
        scanf("%s",rep);
        fflush(stdin);

        if(rep[0]=='o')
            {
                FILE* Fich, *F;
                F=fopen("stock.txt","r");
                Fich=fopen("stock1.txt","w");

                do
                {

                    produit prod;
                    fscanf(F,"%d%s%d%f%s\n",&prod.id,prod.nom,&prod.qte,&prod.prix,prod.cat);

                    if (id!=prod.id)
                    {fprintf(Fich,"\n%d\t%s\t%d\t\t%f\t%s",prod.id,prod.nom,prod.qte,prod.prix,prod.cat);}
                    //ajouter la motification a l'historique *******************************************************
                    else
                    {

                        prod.qte = 0;
                        //date----------------------------------------------
                        Date dat;
                        dat.prod = prod;
                        time_t t = time(NULL);
                        struct tm tm = *localtime(&t);
                        dat.a = tm.tm_year + 1900;
                        dat.m = tm.tm_mon + 1;
                        dat.j= tm.tm_mday;
                        //fichier historique---------------------------------
                        FILE *fileDate = fopen("historique.txt", "a");
                        fwrite(&dat, sizeof(Date), 1, fileDate);
                        fclose(fileDate);
                    }
                }while(!feof(F));


                fclose(F);
                fclose(Fich);
                F=fopen("stock.txt","w");
                Fich=fopen("stock1.txt","r");
                do
                {
                    produit prod;
                    fscanf(Fich,"%d%s%d%f%s\n",&prod.id,prod.nom,&prod.qte,&prod.prix,prod.cat);
                    fprintf(F,"\n%d\t%s\t%d\t\t%f\t%s",prod.id,prod.nom,prod.qte,prod.prix,prod.cat);
                }while(!feof(Fich));
                affichage(3);
                fclose(F);
                fclose(Fich);


            }

    }


}
///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
// ------------------ procedure modifier un produit ------------------

void modif ()
{
    system("cls");
    affichage(10);
    char rep[5];
    int id;
    printf(" entrer la referance du produit a modifier : ");
    scanf("%d",&id);
    fflush(stdin);
    if (recherche(id)==1)
    {
        printf("\n vous voulez vraimment modifier ce produit oui/non ?? " );
        gets(rep);
        fflush(stdin);
        if (rep[0]=='o')
            {
                affichage(2);
                FILE* Fich, *F;
                F=fopen("stock.txt","r");
                Fich=fopen("stock1.txt","w");
                produit produit;
                do
                {


                    fscanf(F,"%d%s%d%f%s\n",&produit.id,produit.nom,&produit.qte,&produit.prix,produit.cat);
                    if (id==produit.id)
                    {
                        produit.id=id;
                        printf("\n Donner le nouveau nom du produit : ");
                        gets(produit.nom);
                        printf("\n Donner la  nouvelle categorie du produit : ");
                        gets(produit.cat);
                        printf("\n Donner le nouveau prix du produit : ");
                        float prix;
                        scanf("%f",&prix);
                        produit.prix=prix;
                        printf("\n Donner la  nouvelle quantite du produit a ajouter : ");
                        int qte;
                        scanf("%d",&qte);
                        produit.qte=qte;
                        fflush(stdin);
                        fprintf(Fich,"%d\t%s\t%d\t\t%f\t%s\n",produit.id,produit.nom,produit.qte,produit.prix,produit.cat);
                                        //date----------------------------------------------
                        Date dat;
                        dat.prod = produit;
                        time_t t = time(NULL);
                        struct tm tm = *localtime(&t);
                        dat.a = tm.tm_year + 1900;
                        dat.m = tm.tm_mon + 1;
                        dat.j= tm.tm_mday;
                        //fichier historique---------------------------------
                        FILE *fileDate = fopen("historique.txt", "a");
                        fwrite(&dat, sizeof(Date), 1, fileDate);
                        fclose(fileDate);
                    }
                    else
                    {
                        fprintf(Fich,"%d\t%s\t%d\t\t%f\t%s\n",produit.id,produit.nom,produit.qte,produit.prix,produit.cat);
                    }


                }while(!feof(F));


                fclose(F);
                fclose(Fich);
                F=fopen("stock.txt","w");
                Fich=fopen("stock1.txt","r");
                //produit prod;
                do
                {

                    fscanf(Fich,"%d%s%d%f%s\n",&produit.id,produit.nom,&produit.qte,&produit.prix,produit.cat);
                    fprintf(F,"\n%d\t%s\t%d\t\t%f\t%s",produit.id,produit.nom,produit.qte,produit.prix,produit.cat);
                }while(!feof(Fich));
                fclose(F);
                fclose(Fich);
                affichage(3);
            }
            else
            {
                printf("\n la modification a ete annuler \n ");

            }
    }
    else
    {
        printf("\n cette referance n existe pas \n");

    }


}
////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
//----------------- fonction recherche dans le stock --------------------


int recherche(int id)
{

    FILE *F;
    F=fopen("stock.txt","r" );
    int rech=-1;
    do
    {
        produit prod;
        fscanf(F,"%d\t%s\t%d\t\t%f%s\n",&prod.id,prod.nom,&prod.qte,&prod.prix,prod.cat);
        fflush(stdin);
        if (prod.id==id)
            {
                rech=1;
                break;
            }
    }while(!feof(F) );
    fclose(F);
    return rech;




}
/////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
//-------------- procedure d'affichage du stock -------------

void aff_stock()
{
    system("cls");
    affichage(6);
    affichage(13);
    FILE *F;
    F=fopen("stock.txt","r");
    if (F != NULL)
    {
    char str[10000];
    fflush(stdin);
    int ch = getc(F);
    while (ch != EOF)
    {
        putchar(ch);
        ch = getc(F);
    }
    }
    printf("\n");

    fclose(F);


}
