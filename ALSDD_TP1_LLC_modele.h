#include <stdlib.h>
#include <stdio.h>
#include <string.h>
/*LE MODELE DES LLC*/
/*Noter: Dés que le modèle du LLC présenté là est pratiquement le meme vue au cours ALSDD, un minimum d'explication est fourni*/
/*Définition des structures de données utilisées*/
typedef struct module module;//Pour ne pas répéter le mot "structure" à chaque fois
struct module
{
    char nom_mod[10];
    int coef;
    module *suivant;
};

typedef struct etudiant etudiant;//Pour ne pas répéter le mot "structure" à chaque fois
struct etudiant
{
    char IdEtud[50];
    char NomEtud[50];
    char PrenEtud[50];
    float NotesEtud[20];
    float MoyEtud;
    etudiant *suivant;
};


typedef module* module_ptr;//remplaçer module* par module_ptr(un pointeur vers la structure module) et
typedef etudiant* etudiant_ptr;//etudiant* par etudiant_ptr un pointeur vers la structure etudiant)
                               //pour améliorer la lisibilité du code


/*Interfaces (prototypes) des modules de modèle LLC pour la structure "module"*/
void        allouer_mod (module_ptr* m);//
void        liberer_mod (module_ptr m);
void        aff_nom_mod (module_ptr m, char* mod);
void        aff_coef    (module_ptr m, int c);
void        aff_adr_m   (module_ptr m, module_ptr n);
char*       n_mod       (module_ptr m);
int         c_mod       (module_ptr m);
module_ptr  m_suivant   (module_ptr m);

/*Interfaces (prototypes des modules de modèle LLC pour la structure "etudiant"*/
void allouer_etud   (etudiant_ptr* e);
void liberer_etud   (etudiant_ptr e);

void aff_idetud     (etudiant_ptr e, char* id);
void aff_nometud    (etudiant_ptr e, char* n);
void aff_prenetud   (etudiant_ptr e, char* p);
void aff_moy        (etudiant_ptr e, float m);
void aff_adr_e      (etudiant_ptr e, etudiant_ptr f);

char*           idetud      (etudiant_ptr e);
char*           nometud     (etudiant_ptr e);
char*           prenetud    (etudiant_ptr e);
float           moyetud     (etudiant_ptr e);
etudiant_ptr    e_suivant   (etudiant_ptr e);


/*Implémentation du modèle LLC pour la structure "module"*/
void allouer_mod(module_ptr* m)
{
    *m=(module_ptr)malloc(sizeof(module));
}

void liberer_mod(module_ptr m)
{
    free(m);
}

void aff_nom_mod(module_ptr m, char* mod)
{

    strcpy(m->nom_mod,mod);//strcpy fonction standard déclarée dans <string.h> int strcpy(char *str1, const char str2) ex:
}                          //str1[10]={'H','e','l','l','o'}
                            //str2[15]={'W','o','r','l','d'}
                            //strcpy(str1,str2)    str1[10] contenir "World"

void aff_coef(module_ptr m, int c)
{
    m->coef=c;
}

void aff_adr_m(module_ptr m, module_ptr n)
{
    m->suivant=n;
}

char* n_mod(module_ptr m)
{
    return m->nom_mod;
}

int c_mod(module_ptr m)
{
    return m->coef;
}

module_ptr m_suivant(module_ptr m)
{
   return m->suivant;
}

/*Implémentaion de modules de modèle LLC pour la structure "etudiant"*/
void allouer_etud(etudiant_ptr* e)
{
    (*e)=(etudiant_ptr)malloc(sizeof(etudiant));
}

void liberer_etud(etudiant_ptr e)
{
    free(e);
}

void aff_idetud(etudiant_ptr e, char* id)
{
    strcpy(e->IdEtud,id);
}

void aff_nometud(etudiant_ptr e, char* n)
{
    strcpy(e->NomEtud,n);
}

void aff_prenetud(etudiant_ptr e, char* p)
{
    strcpy(e->PrenEtud,p);
}
void aff_moy(etudiant_ptr e, float m)
{
    e->MoyEtud=m;
}

void aff_adr_e(etudiant_ptr e, etudiant_ptr f)
{
    e->suivant=f;
}

char* idetud(etudiant_ptr e)
{
    return e->IdEtud;
}

char* nometud(etudiant_ptr e)
{
    return e->NomEtud;
}

char* prenetud(etudiant_ptr e)
{
    return e->PrenEtud;
}

float moyetud(etudiant_ptr e)
{
    return e->MoyEtud;
}

etudiant_ptr e_suivant(etudiant_ptr e)
{
   return e->suivant;
}


