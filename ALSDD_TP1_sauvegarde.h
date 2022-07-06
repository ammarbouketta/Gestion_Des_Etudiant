#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void sauvegarde(etudiant_ptr *t , module_ptr m, int nbgr, int nbmd);

void sauvegarde(etudiant_ptr *t , module_ptr m, int nbgr, int nbmd)
{   //ROLE: SAUVEGARDER LA LISTE DES ETUDIANTS ET LEURS NOTES DANS LE FICHIER "RESULTAT.TXT"
    module_ptr n;
    etudiant_ptr e;
    int i,j;
    FILE *fptr=fopen("Resultats.txt","w");

    fputs("Modules\n",fptr);
    for(n=m;n!=NULL;n=m_suivant(n))
    {
        fprintf(fptr,"%s\t",n->nom_mod);
    }
    for(i=0;i<nbgr;i++)
    {
        fprintf(fptr,"\nGroupe%d\n",i+1);
        for(e=t[i];e!=NULL;e=e_suivant(e))
        {
            fprintf(fptr,"%s\t%s %s\n",e->IdEtud,e->NomEtud,e->PrenEtud);
            for(j=0;j<nbmd;j++)
            {
                fprintf(fptr,"%.2f\t",e->NotesEtud[j]);
            }
            fprintf(fptr,"\n%.2f\n",e->MoyEtud);
        }
    }
    fclose(fptr);
}

