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
int insertionParOrderDeNom(char nom[], char prenom[], Date dateDeNaissance, int noteGenerale);



void scanString(char string[], int size);

// --------- Le Main Fonction ---------
int main(){

    int travail = 1;

    // La menu principale
    while (travail)
    {
        puts("\n#### Gestion des etudiants d'universite ####");
        puts("\n\t1. Ajouter Des Etudiants");
        puts("\t2. Afficher Les Etudiants");
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
            // afficherSousMenuDeAffichageDesEtudiantes();
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

void ajouteDesEtudiants(int n){ // n Est le nombre des etudiants qui l'utilisateur va entrer
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

        if (insertionParOrderDeNom(nom, prenom, dateDeNaissance, noteGenerale) == -1)
        {
            puts("\nEurreur lors l'ajoutation.");
            return;
        }  
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

int insertionParOrderDeNom(char nom[], char prenom[], Date dateDeNaissance, int noteGenerale) { // Retourner 1 si l'ajoutation est succes, si non -1
    
    int indice = nombreDesEtudiants;

    for (int i = 0; i < nombreDesEtudiants; i++) {
        if (strcmp(nom, etudiants[i].nom) < 0) {
            indice = i;
            break;
        }
    }

    for (int i = nombreDesEtudiants; i > indice; i--) {
        etudiants[i] = etudiants[i - 1];
    }

    Etudiant etudiant;

    etudiant.id = nombreDesEtudiants + 1;
    strcpy(etudiant.nom, nom);
    strcpy(etudiant.prenom, prenom);
    etudiant.noteGenerale = noteGenerale;
    etudiant.dateDeNaissance = dateDeNaissance;

    int departement = obtenirDepartementIndice();
    if (departement == -1)
    {
        return -1;
    }
    
    etudiants[indice] = etudiant;

    nombreDesEtudiants++;

    return 1;
}





void scanString(char string[], int size){
    if (fgets(string, size, stdin) != NULL) {
        string[strcspn(string, "\n")] = '\0';
    }
}