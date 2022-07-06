#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <windows.h>
#include <unistd.h>
#include <conio.h>
#include "conio.h"

#include "ALSDD_TP1_LLC_modele.h"
#include "ALSDD_TP1_initialisation.h"
#include "ALSDD_TP1_insert_supp.h"
#include "ALSDD_TP1_LLC_parcours.h"
#include "ALSDD_TP1_sauvegarde.h"
#include "ALSDD_TP1_tri_interclass.h"

static int __FOREGROUND = 0;
void textcolor (int color);

void textcolor (int color)
{
    __FOREGROUND = color;
    SetConsoleTextAttribute (GetStdHandle (STD_OUTPUT_HANDLE), color);
}

int main ()
{
    etudiant_ptr t[30];
    module_ptr m;
    int choix,sortir=0,nbgr,nbmd;
    char rep;

    textcolor(14);
    printf("***********************************************************************************************************************\n");
    printf("                                            Concue et Realise par:                                                     \n");
    printf("                                               BOUKETTA Ammar                                                          \n");
    printf("                              -ESI:Ecole Nationale Superieur d'Informatique EX:INI-                                    \n");
    printf("                                                 Promotion:2019                                                        \n");
    printf("***********************************************************************************************************************\n");
    textcolor(4);

    printf("IMPORTANT: Afin que cette application fonctionne normalement il faut verifier le suivant:\n");
    printf("\t-Une fichier untitule 'Etudiants.txt' existe dans le repertoire de l'application.\n");
    printf("\t-Ne pas ajouter aucune espace (blanc) apres le nom ou le prenom des etudiants.\n");
    printf("\nSi ses instructions n'est pas respecte le comportement de l'application est indefini\n");
    printf("***********************************************************************************************************************\n");
    textcolor(15);
    nbgr=lect_etudiant(t);
    nbmd=lect_modules(&m);
    lect_notes_alea(t,m,nbgr,nbmd);
    do
    {
        printf("\n***********************************************************************************************************************\n");
        textcolor(15);
        printf("Que-ce que vous voulez faire:\n");
        textcolor(14);
        printf("SERVICES ESSENTIELLES:\n");
        textcolor(13);
        printf("1-Afficher les notes d'un etudiant.\n");
        printf("2-Afficher la moyenne d'un groupe.\n");
        printf("3-Afficher les etudiants qui ont une/des note(s) eleminatoire(s).\n");
        printf("4-Afficher la liste des etudiants d'un groupe ordonnee par merite.\n");
        printf("5-Afficher la liste des etudiants du promotion ordonnee par merite.\n");
        printf("6-Changer le groupe d'un etudiant.\n");
        printf("7-Changer la note d'un etudiant dans un module.\n");
        textcolor(14);
        printf("SERVICES SUPPLEMENTAIRES:\n");
        textcolor(13);
        printf("8-Supprimer un etudiant de la liste des etudiants.\n");
        printf("9-Inserer un etudiant dans la liste des etudiants.\n");
        printf("10-Afficher la moyenne de la promotion\n");
        printf("11-Afficher la liste des premiers 10 %% etudiants.\n");
        textcolor(14);
        printf("12-SORTIRE DE L'APPLICATION\n");
        textcolor(15);
        printf("\nEntrer votre choix:\n");
        scanf("%d",&choix);
        getchar();
        printf("************************************************************************************************************************\n");

        textcolor(15);
        switch (choix)
        {
        case 1:
            affich_etudnote(t,m,nbgr,nbmd);
            break;
        case 2:
            affich_groupnote(t,m,nbgr,nbmd);
            break;
        case 3:
            affich_ne(t,m,nbgr,nbmd);
            break;
        case 4:
            affich_group_ord(t,nbmd);
            break;
        case 5:
            affich_promo_ord(t,nbgr,nbmd);
            break;
        case 6:
            chang_etud(t);
            break;
        case 7:
            chang_note(t,m,nbgr,nbmd);
            break;
        case 8:
            supp_etud(t,nbgr);
            break;
        case 9:
            insert_etud(t,m,nbgr,nbmd);
            break;
        case 10:
            affich_promo_moy(t,m,nbgr,nbmd);
            break;
        case 11:
            affich_top_10(t,nbgr,nbmd);
            break;
        case 12:
            sortir=1;
            break;
        default:
            textcolor(4);
            printf("\nChoix invalide!\n");
            textcolor(15);
        }
    sauvegarde(t,m,nbgr,nbmd);
    if (sortir==0)
    {
        textcolor(1);
        printf("\nVoulez-vous continuer? (o/n) :");
        do
        {
            scanf("%c",&rep);
        }while(rep=='\n');
    }
    else rep='n';
    }while(tolower(rep)=='o');
    textcolor(15);
    printf("\nPour signaler les bugs et les erreurs:\n");
    printf("\tja_bouketta@esi.dz\n");
    printf("\n© 2020 Toutes les droits reservees.\n");
    return 0;
}

