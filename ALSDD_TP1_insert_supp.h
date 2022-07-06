#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

void         supp_etud              (etudiant_ptr *t, int nbgr);
void         insert_etud            (etudiant_ptr *t , module_ptr m, int nbgr, int nbmd);
void         chang_etud             (etudiant_ptr *t);
void         regler                 (char *n, char *pr);
void         affich_LLC_mod         (module_ptr m);
void         chang_note             (etudiant_ptr *t , module_ptr m, int nbgr, int nbmd);
etudiant_ptr rech_etud_npr          (etudiant_ptr *t, int nbgr, char *n ,char *pr);
etudiant_ptr rech_etud_id           (etudiant_ptr *t, int nbgr, char *id);

void supp_etud(etudiant_ptr *t, int nbgr)
{   //ROLE: SUPPRIMER UN ETUDIANT DE LISTE DES ETUDIANT DE LA PROMOTION
    etudiant_ptr p1,p2;
    int i;
    char n[50];
    char pr[50];
    int found=0;

    printf("Donner le nom de l'etudiant: ");
    fgets(n,49,stdin);
    printf("Donner le prenom de l'etudiant: ");
    fgets(pr,49,stdin);
    regler(n,pr);

    for(i=0;(i<nbgr)&&(!found);i++)
    {
        p2=t[i];
        while ((p2!=NULL)&&(!found))
        {
            if ((!strcmp(p2->NomEtud,n))&&(!strcmp(p2->PrenEtud,pr))) found=1;
            else
            {
                p1=p2;
                p2=e_suivant(p2);
            }
        }
    }
    if(found)
    {
        if (p2==t[i])
        {
            t[i]=e_suivant(p2);
            liberer_etud(p2);
        }
        else
        {
            aff_adr_e(p1,e_suivant(p2));
            liberer_etud(p2);
        }
    }
    else printf("L'etudiant n'est pas trouvee!\n");
    printf("\nL'etudiant a ete supprime avec succes!\n");
}

void insert_etud(etudiant_ptr *t , module_ptr m, int nbgr, int nbmd)
{   //ROLE: INSERER UN ETUDIANT DE LISTE DES ETUDIANT D'UN GRUOPE
    etudiant_ptr p1,p2,e;
    int i;
    int j;
    int found=0;
    int matr;
    char matrstr[10];
    char id[10];
    char n[50];
    char pr[50];

    srand(time(NULL));
    printf("Donner le nom de l'etudiant: ");
    fgets(n,49,stdin);
    printf("Donner le prenom de l'etudiant: ");
    fgets(pr,49,stdin);
    regler(n,pr);

    printf("Donner le numero du groupe: ");
    scanf("%d",&i);
    //Générer un matricule pour le nouveau etudiant et vérifier q'elle est unique.
    strcpy(id,"19/0");
    do
    {
        found=0;
        matr=rand()%999;
        itoa(matr,matrstr,10);
        strcat(id,matrstr);
        p2=rech_etud_id(t,nbgr,id);
        if (p2==NULL) printf("Le matricule de nouveau etudiant est: %s",id);
        else found=1;

    }while(found);


    allouer_etud(&e);
    aff_nometud(e,n);
    aff_prenetud(e,pr);
    aff_idetud(e,id);
    for(j=0;j<nbmd;j++)
    {
        e->NotesEtud[j]=(rand()%15)+5+(rand()%100)/100.0;
    }
    moyen(m,e,nbmd);

    found=0;
    p2=t[i-1];
    while ((p2!=NULL)&&(!found))
    {
        if (strcmp(n,p2->NomEtud)<=0)
        {
            if (!strcmp(n,p2->NomEtud))
            {
                if (strcmp(pr,p2->PrenEtud)<=0) found=1;
            }
            else found=1;
        }
        else
        {
            p1=p2;
            p2=e_suivant(p2);
        }
    }

    if (p2==t[i-1])
    {
         aff_adr_e(e,p2);
         t[i-1]=e;
    }
    else
    {
        aff_adr_e(e,p2);
        aff_adr_e(p1,e);
    }
    printf("\nL'etudiant a ete insere avec succes!\n");
}

void chang_etud(etudiant_ptr *t)
{   //ROLE: CHANGER LE GROUPE D'UN ETUDIANT
    etudiant_ptr p1,p2,p3;
    int i;
    char n[50];
    char pr[50];
    int found=0;

    printf("Donner le nom de l'etudiant: ");
    fgets(n,49,stdin);
    printf("Donner le prenom de l'etudiant: ");
    fgets(pr,49,stdin);
    regler(n,pr);

    printf("Entrer le numero de son groupe: ");
    scanf("%d",&i);
    p2=t[i-1];
    //PARTIE 01: RECHERCHE DE L'ETUDIANT
    while ((p2!=NULL)&&(!found))
    {
        if ((!strcmp(p2->NomEtud,n))&&(!strcmp(p2->PrenEtud,pr))) found=1;
        else
        {
            p1=p2;
            p2=e_suivant(p2);
        }
    }

    if(!found) printf("L'etudiant n'est pas trouvee!\n");
    //PARTIE 02: SUPPRESSION DE L'ETUDIANT DE SON ANCIEN GROUPE
    else
    {
        if (p2==t[i-1])
        {
            t[i-1]=e_suivant(p2);
        }
        else
        {
            aff_adr_e(p1,e_suivant(p2));
        }

        //PARTIE 03: INSERTION DE L'ETUDIANT DANS SON NOUVEAU GROUPE
        printf("Entrer son nouveau groupe: ");
        scanf("%d",&i);
        //PARTIE 03-01: RECHERCHE DE LA NOUVELLE POSITION
        found=0;
        p3=t[i-1];
        while ((p3!=NULL)&&(!found))
        {
            if (strcmp(n,p3->NomEtud)<=0)
            {
                if (!strcmp(n,p3->NomEtud))
                {
                    if (strcmp(pr,p3->PrenEtud)<=0) found=1;
                }
                else found=1;
            }
            else
            {
                p1=p3;
                p3=e_suivant(p3);
            }
        }
        //PARTIE 03-02: INSERTION DE L'ETUDIANT A SA POSITION
        if (p3==t[i-1])
        {
            aff_adr_e(p2,p3);
            t[i-1]=p2;
        }
        else
        {
            aff_adr_e(p2,p3);
            aff_adr_e(p1,p2);
        }
    }
    printf("\nLe groupe de l'etudiant a ete change avec succes!\n");
}

void chang_note(etudiant_ptr *t , module_ptr m, int nbgr, int nbmd)
{   //ROLE: CHANGER LA NOTE D'UN ETUDIANT DANS UN MODULE
    char n[50];
    char pr[50];
    etudiant_ptr e;
    int choixm;
    float note;

    printf("Donner le nom de l'etudiant: ");
    fgets(n,49,stdin);
    printf("Donner le prenom de l'etudiant: ");
    fgets(pr,49,stdin);
    regler(n,pr);

    e=rech_etud_npr(t,nbgr,n,pr);
    if(e==NULL) printf("\nL'etudiant n'est pas trouvee!\n");
    else
    {
        printf("Quel module voulez vous changer la note: ");
        affich_LLC_mod(m);
        printf("\nEntrer le numero du module: ");
        scanf("%d",&choixm);
        if ((choixm<=nbmd) && (choixm>0))
        {
            printf("Entrer la nouvelle note:");
            scanf("%f",&note);
            if ((note<=20) && (note>=0))
            {
                e->NotesEtud[choixm-1]=note;
                moyen(m,e,nbmd);
            }
            else
            {
                printf("\nNote invalide!\n");
            }
        }
        else
        {
            printf("\nChoix invalide!\n");
        }
    }
}

void regler(char *n, char *pr)
{   //ROLE: METTRE LE NOM n TOUS EN MAJISCULE, METTRE LE PREMIER CARACTERE DU PRENOM p EN MAJISCULE ET LE RESTE EN MINUSCULE
    //SUPPRIMER LE CARACTERE DE NOUVEAU LIGNE "\n" DU NOM ET PRENOM
    n[strlen(n)-1]='\0';//noter que "fgets" inclut "\n" dans la chaine du nom et le prenom donc il faut l'elever
    n=strupr(n);

    pr[strlen(pr)-1]='\0';
    pr=strlwr(pr);
    pr[0]=toupper(pr[0]);
}

void affich_LLC_mod(module_ptr m)
{   //ROLE: AFFICHER LA LISTE DES CHOIX DES MODULES
    module_ptr n=m;
    int i=1;
    while(n!=NULL)
    {
        printf("%d-%s ",i,n->nom_mod);
        i++;
        n=m_suivant(n);
    }
}

