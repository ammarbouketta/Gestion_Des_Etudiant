#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void         affich_group_ord   (etudiant_ptr *t, int nbmd);
void         affich_promo_ord   (etudiant_ptr *t, int nbrg, int nbmd);
void         affich_top_10      (etudiant_ptr *t, int nbgr, int nbmd);
etudiant_ptr copier_LLC_etud    (etudiant_ptr e,  int nbmd);
etudiant_ptr copier_etud        (etudiant_ptr e,  int nbmd);
void         permut_etud        (etudiant_ptr e , etudiant_ptr f, int nbmd);
void         affich_LLC_etud    (etudiant_ptr tete);
void         ord_LLC_etud       (etudiant_ptr tete, int nbmd);
etudiant_ptr interclasse_etud   (etudiant_ptr e , etudiant_ptr f);
void         liberer_LLC_etud   (etudiant_ptr tete);


void affich_group_ord(etudiant_ptr *t, int nbmd)
{   //ROLE: AFFICHER LA LISTE DES ETUDIANTS D'UN GROUPE ORDONNEE PAR L'ORDRE DE LA MOYENNE
    int choixg;
    etudiant_ptr tete;

    printf("Entrer le numero du groupe: ");
    scanf("%d",&choixg);
    tete=copier_LLC_etud(t[choixg-1], nbmd);
    ord_LLC_etud(tete,nbmd);
    affich_LLC_etud(tete);
    liberer_LLC_etud(tete);
}

void affich_promo_ord(etudiant_ptr *t, int nbrg, int nbmd)
{   //ROLE: AFFICHER LA LISTE DES ETUDIANTS DU PROMOTION ORDONNE PAR LA MOYENNE
    int i=0;
    etudiant_ptr tete1,tete2;

    tete1=copier_LLC_etud(t[i],nbmd);
    ord_LLC_etud(tete1,nbmd);
    for(i=1;i<nbrg;i++)
    {
        tete2=copier_LLC_etud(t[i],nbmd);
        ord_LLC_etud(tete2,nbmd);
        tete1=interclasse_etud(tete1,tete2);
    }
    affich_LLC_etud(tete1);
    liberer_LLC_etud(tete1);
}

void affich_top_10(etudiant_ptr *t, int nbgr, int nbmd)
{
    etudiant_ptr tete1,tete2, que;
    int longueur=1;
    int i;

    tete1=copier_LLC_etud(t[0],nbmd);
    que=tete1;
    while (e_suivant(que)!=NULL)
    {
        que=e_suivant(que);
        longueur++;
    }


    for(i=1;i<nbgr;i++)
    {
        tete2=copier_LLC_etud(t[i],nbmd);
        aff_adr_e(que,tete2);
        que=tete2;
        longueur++;
        while (e_suivant(que)!=NULL)
        {
            que=e_suivant(que);
            longueur++;
        }
    }
    ord_LLC_etud(tete1,nbmd);
    longueur/=10;
    for(i=0;i<longueur;i++)
    {
        printf("%d- ",i+1);
        textcolor(2);
        printf("%s\t",idetud(tete1));
        textcolor(15);
        printf("%s %s ",nometud(tete1),prenetud(tete1));
        textcolor(9);
        printf("%.2f\n",moyetud(tete1));
        textcolor(15);
        tete1=e_suivant(tete1);
    }
    liberer_LLC_etud(tete1);

}

etudiant_ptr copier_LLC_etud(etudiant_ptr e, int nbmd)
{   //ROLE: CREER UNE COPIE D'UNE LISTE DES ETUDIANTS
    etudiant_ptr tete,p,q1,q2;

    tete=copier_etud(e,nbmd);
    p=e_suivant(e);
    q1=tete;
    while(p!=NULL)
    {
        q2=copier_etud(p,nbmd);
        aff_adr_e(q1,q2);
        q1=q2;
        p=e_suivant(p);
    }
    aff_adr_e(q2,NULL);
    return tete;
}

etudiant_ptr copier_etud(etudiant_ptr e, int nbmd)
{   //ROLE: CREER UNE COPIE D'UNE MAILLON ETUDIANT
    int i;
    etudiant_ptr f;

    allouer_etud(&f);
    aff_idetud(f,idetud(e));
    aff_nometud(f,nometud(e));
    aff_prenetud(f,prenetud(e));
    aff_moy(f,moyetud(e));
    for(i=0;i<nbmd;i++)
    {
        f->NotesEtud[i]=e->NotesEtud[i];
    }

    return f;
}

void permut_etud(etudiant_ptr e , etudiant_ptr f, int nbmd)
{   //ROLE: PERMUTER DEUX MAILLON ETUDIANT DANS UNE LISTE DES ETUDIANTS
    char id[8];
    char n[50];
    char pr[50];
    float m;
    float s[nbmd];
    int i;

    strcpy(n,nometud(e));
    strcpy(pr,prenetud(e));
    strcpy(id,idetud(e));
    for(i=0;i<nbmd;i++)
    {
        s[i]=e->NotesEtud[i];
    }
    m=moyetud(e);

    aff_idetud(e,idetud(f));
    aff_nometud(e,nometud(f));
    aff_prenetud(e,prenetud(f));
    for(i=0;i<nbmd;i++)
    {
        e->NotesEtud[i]=f->NotesEtud[i];
    }
    aff_moy(e,moyetud(f));

    aff_idetud(f,id);
    aff_nometud(f,n);
    aff_prenetud(f,pr);
    for(i=0;i<nbmd;i++)
    {
        f->NotesEtud[i]=s[i];
    }
    aff_moy(f,m);
}

void affich_LLC_etud(etudiant_ptr tete)
{   //ROLE: AFFICHER UNE LISTE DES ETUDIANTS
    etudiant_ptr p=tete;
    while(p!=NULL)
    {
        textcolor(2);
        printf("%s\t",idetud(p));
        textcolor(15);
        printf("%s %s ",nometud(p),prenetud(p));
        textcolor(9);
        printf("%.2f\n",moyetud(p));
        textcolor(15);
        p=e_suivant(p);
    }
}

void ord_LLC_etud(etudiant_ptr tete, int nbmd)
{   //ROLE: ORDONNER UNE LISTE DES ETUDIANTS SELON LA MOYENNE
    etudiant_ptr p1,p2;
    int sorted;

    do
    {
        p1=tete;
        p2=e_suivant(p1);
        sorted=1;
        while(p2!=NULL)
        {
            if (moyetud(p1)<moyetud(p2))
             {
                permut_etud(p1,p2,nbmd);
                sorted=0;
             }
             p2=e_suivant(p2);
             p1=e_suivant(p1);
        }
    }while(!sorted);
}

etudiant_ptr interclasse_etud(etudiant_ptr e , etudiant_ptr f)
{   //ROLE: FAIRE L'INTERCLASSEMENT DE DEUX LISTE DES EYUDIANTS ORDONNEE PAR LA MOYENNE
    etudiant_ptr tete,res,e1,f1;

    if ((e!=NULL) || (f!=NULL))
    {
        if ((e!=NULL) && (f!=NULL))
        {
            if (moyetud(e)> moyetud(f))
            {
                tete=e;
                e1=e_suivant(e);
                f1=f;
            }
            else
            {
                tete=f;
                f1=e_suivant(f);
                e1=e;
            }

            res=tete;
            while((e1!=NULL) && (f1!=NULL))
            {
                if (moyetud(e1)>moyetud(f1))
                {
                    aff_adr_e(res,e1);
                    e1=e_suivant(e1);
                    res=e_suivant(res);
                }
                else
                {
                    aff_adr_e(res,f1);
                    f1=e_suivant(f1);
                    res=e_suivant(res);
                }
            }
            if (e1==NULL) aff_adr_e(res,f1);
            else aff_adr_e(res,e1);
            return tete;
        }
        else
        {
            if(e==NULL) return f;
            else return e;
        }
    }
    else return NULL;
}

void liberer_LLC_etud(etudiant_ptr tete)
{
    etudiant_ptr p;
    if (tete!=NULL)
    {
        p=e_suivant(tete);
        liberer_etud(tete);
        liberer_LLC_etud(p);
    }
}

