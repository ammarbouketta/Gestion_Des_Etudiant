# Gestion_Des_Etudiants
Cette application est réaliser avec le language C
ÉNONCÉ
   L’école nationale supérieure d’informatique souhaite développer une application de gestion des étudiants de 1ère année préparatoire (année universitaire 2019/2020). Pour ce faire, le service de scolarité de l’école fait appel à votre expertise en programmation pour le développement de cette application.
Dans cette application, les listes des 11 groupes sont stockées dans un tableau de 12 cases :
• La 1ère case du tableau contient une liste des noms et coefficients des modules enseignés durant le semestre en cours (ListeModules).
• Les autres cases contiennent les listes des étudiants de chaque groupe :
- Chaque groupe d’étudiants est représenté par une liste linéaire chaînée (ListeGroupe). Les listes de groupes sont ordonnées, selon l'ordre alphabétique croissant.
- Un étudiant est représenté par un enregistrement contenant les informations suivantes :
1. Matricule de l’étudiant (IdEtud) : une chaîne de caractères.
2. Nom (NomEtud) : une chaîne de caractères.
3. Prénom (PrenEtud) : une chaîne de caractères.
4. Notes (NotesEtud) : un tableau contenant les notes des étudiants dans les modules enseignés durant le semestre en cours.
5. Moyenne (MoyEtud) : un réel indiquant la moyenne semestrielle de l’étudiant

TRAVAIL DEMANDÉ
   Dans un premier temps, programmez le modèle des LLC . Par la suite, programmez en Langage C
les procédures et les fonctions suivantes :
1. INITIALISATION DES STRUCTURES DE DONNÉES
    a) Le service de scolarité commence par introduire les noms et les coefficients des modules du semestre en cours.
    b) Ensuite, et afin d’éviter la saisie des données à partir du clavier, construisez les listes des étudiants (par groupe) à partir du fichier texte (Etudiants.txt).
    c) Toutes les notes doivent être générées aléatoirement (notes comprises entre 5 et 20).
2. PARCOURS DES LISTES
    a) On veut connaitre les notes d’un étudiant donné :
        • Afficher toutes les notes de cet étudiant.
        • Afficher la note d’un module donné.
    b) On veut connaitre les moyenne d’un groupe donné :
        • Afficher les moyennes de tous les modules.
        • Afficher la moyenne d’un module donné.
    c) On veut connaitre les étudiants ayant une note éliminatoire :
        • Afficher tous les étudiants ayant une note éliminatoire dans un module donné.
        • Afficher les étudiants ayant au moins une note éliminatoire ordonnés par groupe.
3. INSERTION/SUPPRESSION/MISE À JOUR D’ÉLÉMENTS
    a) On veut donner la possibilité au service de scolarité de gérer les demandes de changement de groupe.
     N.B : Les listes des groupes doivent rester ordonnées après chaque changement de groupe.
    b) On veut mettre à jour la note d’un module donné pour un étudiant donné (toutes les moyennes doivent être recalculées).
4. TRI/INTERCLASSEMENT DES LISTES
    a) On veut connaitre le classement des étudiants :
        • Afficher la liste des étudiants d’un groupe par ordre de mérite.
        • Afficher la liste de tous les étudiants de la promotion par ordre de mérite.
5. SAUVEGARDE DES RÉSULTATS
    a) À la fin de l’exécution de l’application, on veut enregistrer toutes les modifications apportées aux listes dans un fichier (Resultats.txt)dont le format est donné ci-dessous
                Modules
                NomModule1 NomModule2 … NomModuleN
                Groupe1
                IdEtud1 NomEtud1 PrenEtud1
                Note1 Note2 … NoteN
                MoyEtud1
                IdEtud2 NomEtud2 PrenEtud2
                Note1 Note2 … NoteN
                MoyEtud2
                …
                Groupe2
                IdEtud1 NomEtud1 PrenEtud1
                Note1 Note2 … NoteN
                MoyEtud1
                …
                Groupe11
                IdEtud1 NomEtud1 PrenEtud1
                Note1 Note2 … NoteN
                MoyEtud1
