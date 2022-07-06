#include <stdlib.h>
#include <stdio.h>
#include <string.h>
/*========================================================================================
==========================================================================================
NOTER:* Les modules de cette application utilise comme des precautions:
-La fonction fgets (au lieu de "gets" et "scanf") parce qu'elle fournit le
controle de nombre maximum des caractère lus pour empecher "buffer over flow"
(precaution de sécurité).
-La lecture des choix de l'utilisateur comme une chaine de caractères puis
la convertir au nombre par la fonction "atoi"(input control precaution).
-Construction du module "regler" (déclarer et implementer dans ALSDD_TP1_insrt_supp.h)
pour corriger la forme des noms et prenoms entres par l'utilisateur(input control precaution)
*La fonction affich_LLC_mod est pour but d'afficher les choix des modules apartir de la
liste des modules ex: 1-ALSDD 2-SYS2 3-MECA ...
===========================================================================================
===========================================================================================*/
void            affich_etudnote     (etudiant_ptr *t, module_ptr m, int nbgr, int nbmod);
void            affich_groupnote    (etudiant_ptr *t, module_ptr m, int nbgr, int nbmod);
void            affich_ne           (etudiant_ptr *t, module_ptr m, int nbgr, int nbmd);
float           promo_moy           (etudiant_ptr *t, int nbmod, int nbgr);
void            affich_promo_moy    (etudiant_ptr *t, module_ptr m, int nbgr, int nbmd);
float           group_moy           (etudiant_ptr *t, int nbgr, int nbmod);
etudiant_ptr    rech_etud_npr       (etudiant_ptr *t, int nbgr, char *n ,char *pr);
etudiant_ptr    rech_etud_id        (etudiant_ptr *t, int nbgr, char *id);


void affich_etudnote(etudiant_ptr *t,module_ptr m, int nbgr, int nbmod)
{   //ROLE: AFFICHER LES NOTES D'UN ETUDIANT"
    char n[50];
    char pr[50];
    etudiant_ptr p;
    module_ptr k;
    char choixstr[3];
    int choix,i;

    printf("Donner le nom de l'etudiant:\t");
    fgets(n,49,stdin);
    printf("Donner le prenom de l'etudiant:\t");
    fgets(pr,49,stdin);
    regler(n,pr);

    p=rech_etud_npr(t,nbgr,n,pr);
    if (p==NULL) printf("Etudiant n'est pas trouves!");
    else
    {
        printf("Voulez-vous afficher\n1- La note d'un module\n2- Toutes les notes de l'etudiants\nEntrer votre choix:  ");
        fgets(choixstr,2,stdin);
        choix=atoi(choixstr);
        if (choix==1)
        {
            affich_LLC_mod(m);
            printf("\nDonner le numero du module: ");
            scanf("%d",&choix);
            getchar();
            if ((choix<=nbmod) && (choix>0)) printf("%.2f",p->NotesEtud[choix-1]);
            else
            {
                printf("\nChoix invalide!\n");
            }
        }
        else if(choix==2)
        {
            k=m;
            while (k!=NULL)
            {
                printf("%s\t|\t",n_mod(k));
                k=m_suivant(k);
            }
            printf("\n");
            for(i=0;i<nbmod;i++)
            {
                printf("%.2f\t|\t",p->NotesEtud[i]);
            }
        }
        else
        {
            printf("\nChoix invalide!\n");
        }
    }
}

void affich_groupnote(etudiant_ptr *t, module_ptr m, int nbgr, int nbmod)
{   //ROLE: AFFICHER LA MOYENNE D'UN GROUPE
    int choixg,choixm,i;
    module_ptr k;

    printf("\nDonner le numero du groupe:\t");
    scanf("%d",&choixg);
    if ((choixg<=nbgr) && (choixg>0))
    {
        printf("Voulez-vous afficher la moyenne:\n1-D'un module specifie\n2-De tous les modules\nEntrer le numero de votr choix: ");
        scanf("%d",&choixm);
        if (choixm==1)
        {
            affich_LLC_mod(m);
            printf("\nDonner le numero du module: ");
            scanf("%d",&choixm);
            if ((choixm<=nbmod) && (choixm>0)) printf("La moyenne est:\t %.2f",group_moy(t,choixg,choixm));
            else
            {
                printf("\nChoix invalide!\n");
            }
        }
        else if(choixm==2)
        {
            k=m;
            i=0;
            while(k!=NULL)
            {
                printf("La moyenne de %s est: %.2f\n",k->nom_mod,group_moy(t,choixg,i+1));
                k=m_suivant(k);
                i++;
            }
        }
    }
    else
    {
        printf("\nChoix invalide!\n");
    }
}

void affich_ne(etudiant_ptr *t, module_ptr m, int nbgr, int nbmd)
{   //ROLE: AFFICHER LES ETUDIANTS QUI ONT UNE(DES) NOTE(S) ELEMINATOIRE(S)
    int choix;
    float ne;
    int i,j;
    etudiant_ptr p;
    module_ptr k;



    printf("Voulez-vous afficher les etudiants qui ont une note eleminatoire:\n1-Dans un module specifiee\n2-Dans tous les modules\nEntrer le numero de votre choix:");
    scanf("%d",&choix);
    if (choix==1)
    {
        affich_LLC_mod(m);
        printf("\nEntrer le numero du module:\t");
        scanf("%d",&choix);
        ne=promo_moy(t,choix,nbgr)*0.6;
        for(i=0;i<nbgr;i++)
        {
            p=t[i];

            printf("\nGROUPE%d:\n",i+1);

            while(p!=NULL)
            {
                if (p->NotesEtud[choix-1]<ne)
                {

                    printf("%s\t",idetud(p));

                    printf("%s %s ",nometud(p),prenetud(p));

                    printf("%.2f\n",p->NotesEtud[choix-1]);

                }
                p=e_suivant(p);
            }
        }
    }

    else if (choix==2)
    {
        for(i=0;i<nbgr;i++)
        {
            k=m;

            printf("\nGROUPE%d:\n",i+1);

            for(j=0;j<nbmd;j++)
            {
                p=t[i];
                printf("%s:\n",k->nom_mod);
                ne=promo_moy(t,j+1,nbgr)*0.6;

                printf("\nNE=%.2f\n",ne);

                while(p!=NULL)
                {
                    if ((p->NotesEtud[j])<(ne))
                    {

                        printf("%s\t",idetud(p));

                        printf("%s %s ",nometud(p),prenetud(p));

                        printf("%.2f\n",p->NotesEtud[j]);

                    }
                    p=e_suivant(p);
                }
                k=m_suivant(k);
            }
        }
    }
    else
    {

        printf("\nChoix invalide!\n");

    }
}

float promo_moy(etudiant_ptr *t, int nbmod, int nbgr)
{   //ROLE: CALCULER LA MOYENNE DE LA PROMOTION DANS UN MODULES
    int i;
    etudiant_ptr p;
    float cpt=0;
    int nbetd=0;

    for(i=0;i<nbgr;i++)
    {
        p=t[i];
        while(p!=NULL)
        {
            cpt+=p->NotesEtud[nbmod-1];
            nbetd++;
            p=e_suivant(p);
        }
    }
    cpt=cpt/nbetd;
    return cpt;
}

void affich_promo_moy(etudiant_ptr *t, module_ptr m, int nbgr, int nbmd)
{
    char choixstr[50];
    int choix,i;


    printf("Voulez-vous afficher la moyenne de la promotion:\n1-Dans un module specifiee.\n2-Dans tous les modules.\nEntrer le numero de votre choix:\t");
    fgets(choixstr,49,stdin);
    choix=atoi(choixstr);

    if (choix==1)
    {
        affich_LLC_mod(m);
        printf("\nEntrer le numero du module: ");
        fgets(choixstr,49,stdin);
        choix=atoi(choixstr);
        if ((choix>0) &&(choix<=nbmd)) printf("%.2f",promo_moy(t,choix,nbgr));
        else
        {

            printf("\nChoix invalide!\n");

        }
    }
    else if (choix==2)
    {
        for(i=0;i<nbmd;i++)
        {

            printf("%s:\t",n_mod(m));

            printf("%.2f\n",promo_moy(t,i+1,nbgr));
            m=m_suivant(m);
        }
    }
    else
    {

        printf("\nChoix invalide!\n");

    }
}

float group_moy(etudiant_ptr *t , int nbgr , int nbmod)
{   //ROLE: CALCULER LA MOYENNE D'UN GROUPE DANS UN MODULE
    etudiant_ptr p;
    float cpt=0;
    int nbetud=0;

    for(p=t[nbgr-1];p!=NULL;p=e_suivant(p))
    {
        cpt+=p->NotesEtud[nbmod-1];
        nbetud++;
    }
    cpt/=nbetud;
    return cpt;
}

etudiant_ptr rech_etud_npr(etudiant_ptr *t, int nbgr, char *n ,char *pr)
{   //ROLE: DONNER UN PIONTEUR VERS LA MAILLON D'UN ETUDIANT CHERCHE PAR SON NOM ET SON PRENOM
    int i;
    int found=0;
    etudiant_ptr p;

    for(i=0;(i<nbgr)&&(!found);i++)
    {
        p=t[i];
        while((!found)&&(p!=NULL))
        {
            if (!strcmp(p->PrenEtud,pr)&&!strcmp(p->NomEtud,n)) found=1;
            else p=e_suivant(p);
        }
    }
    if (found) return p;
    else return NULL;
}

etudiant_ptr rech_etud_id(etudiant_ptr *t, int nbgr, char *id)
{   //ROLE: DONNER UN PIONTEUR VERS LA MAILLON D'UN ETUDIANT CHERCHE PAR SON MATRICULE
    int i;
    int found=0;
    etudiant_ptr p;

    for(i=0;(i<nbgr)&&(!found);i++)
    {
        p=t[i];
        while((!found)&&(p!=NULL))
        {
            if (!strcmp(idetud(p),id)) found=1;
            else p=e_suivant(p);
        }
    }
    if (found) return p;
    else return NULL;
}

