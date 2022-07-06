
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
/*LA LECTURE DES DONNEES DES ETUDIANTS*/
/*Interfaces des modules d'initialisation des structures de données*/
int     lect_modules    (module_ptr *m);
int     lect_etudiant   (etudiant_ptr *t);
void    lect_notes_alea (etudiant_ptr *t, module_ptr m, int nbgr, int nbmd);
void    moyen           (module_ptr m, etudiant_ptr e, int nbmd);



/*Implémentation des modules d'initialisation des structures de données*/
int lect_modules(module_ptr* m)
{   //ROLE: LIRE LES NOMS DES MODULES ET LEUR COEFICIENTS DEPUIS LA CLAVIER

    //cette fonctions retourne le nombre des modules étudiees (qui est donne aussi par l'utilisateur)
    //pour généraliser la fonction (l'apllication maintenant accepte n'importe quelle nombre de modules)
    //ce nombre est utlisé par les autre fonction de l'application
    int nbmod;
    int i;
    char n[50];
    int c;
    module_ptr p1,p2;
    p2=NULL;

    printf("Entrer le nombre des modules etudies dans le semestre:");
    /*=====================================================================================================
    =======================================================================================================
    NOTER: La lecture de toutes les données peut se faire dans la fonction "main" puis les passer à l'entree
    de nos modules, mais pour assurer la lisibilité et l'élégance de la fonction "main" et pur minimaiser
               les erreurs nous avons choisi de lire les donnée à l'intérieur des modules
    =======================================================================================================
    =======================================================================================================*/
    scanf("%d",&nbmod);
    printf("Entrer les noms des modules puis leurs coeficient dans l'ordre inverse:\n");//cette fonction utilise la lecture à l'inverse d'une LLC (vue au cours ALSDD)
    for(i=1;i<=nbmod;i++)                                                               //parce que ce procedure est fait une fois dans la vie de l'apllication
    {                                                                                   //c'est pas un grand problème!
        allouer_mod(&p1);
        scanf("%s%d",n,&c);
        aff_nom_mod(p1,n);
        aff_coef(p1,c);
        aff_adr_m(p1,p2);
        p2=p1;
    }
    (*m)=p1;
    return nbmod;
}

int lect_etudiant(etudiant_ptr *t)
{   //ROLE: LIRE LES MATRICULES, LES NOMS ET LES PRENOMS DES ETUDIANTS DEPUIS LE FICHIER "ETUDIANT.TXT"
    int i=0;//pour parcourire le tableau du groupes et va contenir le nombre total du group à la fin
            //ce nombre est retournée par la fonction pour généraliser l'application
    int j;
    char id[8];//va contenir les matricules des étudiants
    char n[50];//va contenir les noms des étudiants
    char p[50];//va contenir les prénoms des étudiants
    char g[15];//va contenir le groupe
    char c[50]={'\0'};//pour parcourir le fichier "Etudiant.txt"

    etudiant_ptr tete,p1,p2;
    FILE *fptr;


    fptr=fopen("Etudiant.txt","r");//le fichier "Etudiant.txt" doit exister dans le repertoire du fichier excutable "ALSDD_TP1"
    while (!feof(fptr))//tant qu'on a pas atteit la fin du fichier
    {   //Cette fonction utilise la lecture du LLC au direction direct
        //PARTIE 1:ALLOUER LA TETE DU GROUPE (LA PREMIERE MAILLON)
        p2=NULL;
        fscanf(fptr,"%s",g);//le groupe (ex: Groupe1) est dans g , donc maintenat fptr pointe vers le matricule du premier étudiant
        allouer_etud(&tete);
        fscanf(fptr,"%s",id);//id contient le matricule
        aff_idetud(tete,id);
        c[0]=fgetc(fptr);//c[0] contient l'espace (le blanc) entre le matricule et le nom du premier etudiant
        c[0]=fgetc(fptr);//c[0] contient le premier caractère du nom de l'etudiant
        if (c[0]=='"')//le nom du premier étudiant est de plus de 1 mot, on le copier dans n par une boucle
        {
            j=0;
            c[0]=fgetc(fptr);
            while(c[0]!='"')
            {
                n[j]=c[0];
                c[0]=fgetc(fptr);
                j++;
            }
            n[j]='\0';//une precaution pour terminer la chaine
            aff_nometud(tete,n);
        }
        else
        {
            fscanf(fptr,"%s",n);
            strcat(c,n);//c contenir le premier caractère du nom et n contenir le reste (ex: c: "A" , n:"BABSA")
                        //Donc il faut concaténer les deux chaines par strcat (fonction standard de C déclarer dans <sting.h>
                        //int strcat( char* str1 , const char* str2) (ex: strcat(c,n) c:"ABABSA"
            aff_nometud(tete,c);
            c[1]='\0';//terminer la chaine c, c[0] va etre utilser pour compléter le parcours
        }

        c[0]=fgetc(fptr);//c[0] contenir l'espace entre le nom et le prenom du premier étudiant
        c[0]=fgetc(fptr);//c[0] contenir le premier caractére du prenom du premier étudiant
        if (c[0]=='"')
        {
            j=0;
            c[0]=fgetc(fptr);
            while(c[0]!='"')
            {
                p[j]=c[0];
                c[0]=fgetc(fptr);
                j++;
            }
            p[j]='\0';
            aff_prenetud(tete,p);
        }
        else
        {
            fscanf(fptr,"%s",p);
            strcat(c,p);
            aff_prenetud(tete,c);
            c[1]='\0';
        }

        aff_adr_e(tete,p2);
        p2=tete;
        c[0]=fgetc(fptr);
        c[0]=fgetc(fptr);
        //PARTIE 2: ALLOUER LE RESTE DE LA LISTE DU GROUPE (LES AUTRES MAILLONS) (par la meme méthode)
        do
        {
            allouer_etud(&p1);
            fscanf(fptr,"%s",id);
            strcat(c,id);
            aff_idetud(p1,c);
            c[1]='\0';
            c[0]=fgetc(fptr);
            c[0]=fgetc(fptr);
            if (c[0]=='"')
            {
                j=0;
                c[0]=fgetc(fptr);
                while(c[0]!='"')
                {
                    n[j]=c[0];
                    c[0]=fgetc(fptr);
                    j++;
                }
                n[j]='\0';
                aff_nometud(p1,n);
            }
            else
            {
                fscanf(fptr,"%s",n);
                strcat(c,n);
                aff_nometud(p1,c);
                c[1]='\0';
            }

            c[0]=fgetc(fptr);
            c[0]=fgetc(fptr);
            if (c[0]=='"')
            {
                j=0;
                c[0]=fgetc(fptr);
                while((c[0]!='"')&&(c[0]!=EOF))
                {
                    p[j]=c[0];
                    c[0]=fgetc(fptr);
                    j++;
                }
                p[j]='\0';
                aff_prenetud(p1,p);
            }
            else
            {
                fscanf(fptr,"%s",p);
                strcat(c,p);
                aff_prenetud(p1,c);
                c[1]='\0';
            }

            aff_adr_e(p2,p1);
            p2=p1;
            c[0]=fgetc(fptr);
            c[0]=fgetc(fptr);
        }while((c[0]!='G')&&(c[0]!=EOF));
        aff_adr_e(p1,NULL);
        t[i]=tete;
        i++;
    }
    fclose(fptr);
    return i;
}



void lect_notes_alea(etudiant_ptr *t , module_ptr m, int nbgr, int nbmd)
{   //ROLE: GENERER LES NOTES DE TOUS LES ETUDIANTS ALEATIOREMENT
    int i;
    int j;
    etudiant_ptr p;
    srand(time(NULL));
    for(i=0;i<nbgr;i++)
    {
        p=t[i];
        while(p!=NULL)
        {
            for(j=0;j<nbmd;j++)
            {
                p->NotesEtud[j]=(rand()%15)+5+(rand()%100)/100.0;//Générer une note aléatoire entre 5 et 20 avec précision 10^-2
            }
            moyen(m,p,nbmd);
            p=e_suivant(p);
        }
    }
}

void moyen(module_ptr m, etudiant_ptr e, int nbmd)
{   //ROLE: GENERER LES MOYENNES DES ETUDIANTS
    //moyen=(la somme de (note*coeficient)) / la somme des coeficients
    int i;
    int cpt=0;//pour la somme des coeficients
    float moy=0;//pour la resultat

    for (i=0;i<nbmd;i++)
    {
        cpt+=m->coef;
        moy+=(m->coef)*(e->NotesEtud[i]);
        m=m_suivant(m);
    }
    moy/=cpt;
    e->MoyEtud=moy;
}


