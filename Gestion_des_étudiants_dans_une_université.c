#include <stdio.h>
#include <string.h>


// Définir les constants
#define MAX_NOM 50
#define MAX_PRENOM 50

// Définir la structure de la date
typedef struct {
    int jour;
    int mois;
    int annee;
} Date;

// Définir la structure d'etudiante
typedef struct {
    int id;
    char nom[100];
    char prenom[100];
    Date dateDeNaissance;
    int departement;
    float noteGenerale;
} Etudiant;

// Définir les global variables
Etudiant etudiants[100];
int nombreDesEtudiants = 0;

char departements[][20] = {"Science Math", "Science Physique", "Science SVT", "Science Economique", "Science Informatique"};

// Définier les fonctions
void afficherSousMenuDajoutation();
void ajouteDesEtudiants(int n);
int obtenirDepartementIndice();

void scanString(char string[], int size);

// --------- Le Main Fonction ---------
int main(){

    int travail = 1;

    // La menu principale
    while (travail)
    {
        puts("\n#### Gestion des etudiants d'universite ####");
        puts("\n\t1. Ajouter Des Etudiants");
        puts("\t2. Afficher Tous Les Taches");
        puts("\t3. Manipulation D'un Tache");
        puts("\t4. Rechercher Un Tache");
        puts("\t5. Statistiques");
        puts("\t6. Quitter Le Program");

        printf("\nEntrer votre choix: ");
        int choix;
        scanf("%d", &choix); // Nettoyer le buffer
        while (getchar() != '\n');

        switch (choix)
        {
        case 1:
            afficherSousMenuDajoutation();
            continue;
        case 2:
            // afficherSousMenuDeAffichageDesTaches();
            continue;
        case 3:
            // afficherSousMenuDeManipulation();
            continue;
        case 4:
            // afficherSousMenuDeRecherche();
            continue;
        case 5:
            // afficherSousMenuDesStatistiques();
            continue;
        case 6:
            travail = 0;
            break;
        
        default:
            puts("Choix invalid.");
        }

        // Pour retour au menu principal
        choix = 0;
        while (choix != 1 && travail != 0) {
            puts("\n----------------");
            puts("1. Retour");
            printf("Entrez votre choix: ");
            scanf("%d", &choix);
            while (getchar() != '\n');
        }
    }

    return 0;
}


// --------- Les Fonction D'Ajoutation ---------
void afficherSousMenuDajoutation(){
    int choix;

    while (1) {
        
        puts("\n\t1. Ajoute Un Etudiant");
        puts("\t2. Ajoute Multiple Etudiants");
        puts("\t3. Retour au menu principal");
        
        printf("\nEntrer votre choix: ");
        scanf("%d", &choix);
        while (getchar() != '\n');

        switch (choix) {
            case 1:
                ajouteDesEtudiants(1);
                break;
            case 2:
                ajouteDesEtudiants(0);
                break;
            case 3:
                return; // Retourne au menu principal
            default:
                puts("Choix invalid.");
        }

        // Retour au menu principal
        choix = 0;
        while (choix != 1) {
            puts("\n----------------");
            puts("1. Retour");
            printf("Entrez votre choix: ");
            scanf("%d", &choix);
            while (getchar() != '\n'); // Nettoyer le buffer
        }
    }
}

void ajouteDesEtudiants(int n){
    char nom[MAX_NOM];
    char prenom[MAX_PRENOM];
    int departement;
    float noteGenerale;
    Date dateDeNaissance;

    if (n == 0)
    {
        printf("Combien des etudiants vous voulez entrer: ");
        scanf("%d", &n);
        while (getchar() != '\n'); // Nettoyer le buffer
    }

    if (n < 1)
    {
        return;
    }
    
    if (n == 1)
    {
        puts("Ajouter Un Etudiant: ");
    }
    else{
        puts("Ajouter Multiple Etudiants: ");
    }
    
    for (int i = 0; i < n; i++)
    {
        if (n > 1)
        {
            printf("\n\t--------- Entrer Les Informations de %d Etudiant ----------\n", i + 1);
        }
        
        printf("\tEntrer le nom: ");
        scanString(nom, sizeof(nom));
        
        printf("\tEntrer le prenom: ");
        scanString(prenom, sizeof(prenom));

        printf("\tEntrer l'annee de naissance: ");
        scanf("%d", &dateDeNaissance.annee);

        printf("\tEntrer le mois de naissance: ");
        scanf("%d", &dateDeNaissance.mois);

        printf("\tEntrer le jour de naissance: ");
        scanf("%d", &dateDeNaissance.jour);

        printf("\tEntrer la note generale: ");
        scanf("%f", &noteGenerale);
        while (getchar() != '\n');  // Nettoyer le buffer

        printf("\n");

        Etudiant etudiant;

        int indice = nombreDesEtudiants;

        etudiant.id = indice + 1;
        strcpy(etudiant.nom, nom);
        strcpy(etudiant.prenom, prenom);
        etudiant.noteGenerale = noteGenerale;
        etudiant.dateDeNaissance = dateDeNaissance;

        departement = obtenirDepartementIndice();
        if (departement == -1)
        {
            puts("\nChoix invalid.");
            return;
        }
        
        etudiants[indice] = etudiant;

        nombreDesEtudiants++;
    }
    

    printf("\n");
    if (n == 1)
    {
        puts("L'Etudient ajoutee avec succes.");
    }
    else
    {
        puts("Les Etudients sont ajoutee avec succes.");
    }
}

int obtenirDepartementIndice(){ // Retourner l'indice de departement si exister, si non retourner -1

    int len = sizeof(departements) / sizeof(departements[0]);
    int choix;

    for (int i = 0; i < len; i++)
    {
        printf("\t%d. %s\n", i + 1, departements[i]);
    }
    
    printf("\n\tChoisir un departement: ");
    scanf("%d", &choix);
    while (getchar() != '\n'); // Nettoyer le buffer

    if (choix < 1 || choix > len)
    {
        return -1;
    }

    
    return choix - 1; // Pour obtenu l'indice
}


















void scanString(char string[], int size){
    if (fgets(string, size, stdin) != NULL) {
        string[strcspn(string, "\n")] = '\0';
    }
}