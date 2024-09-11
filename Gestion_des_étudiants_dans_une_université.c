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
int id = 1;

char departements[][20] = {"Science Math", "Science Physique", "Science SVT", "Science Economique", "Science Informatique"};

// Définier les fonctions
void afficherSousMenuDajout();
void ajouteDesEtudiants(int n);
int obtenirDepartementIndice();
int ajouteUnEtudiant(char nom[], char prenom[], Date dateDeNaissance, int noteGenerale);

void afficherSousMenuDeAffichageDesEtudiantes();
void afficherLesEtudiants(Etudiant triEtudiants[], int croissante, int len);
void triEtAfficherLesEtudiantsParNom(int croissante);
void triEtAfficherLesEtudiantsParNoteGenerale(int croissante);
void triEtAfficherLesEtudiantsReussite(int croissante);

void afficherSousMenuDeManipulation();
void modifierUnEtudiant();
int rechercheParId(int id);

void printLesColonnes();
void printUnEtudiantLigne(Etudiant etudiant);
void printUnEtudiant(Etudiant etudiant);
void printNexistePas();
void printUnligne();

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
            afficherSousMenuDajout();
            continue;
        case 2:
            afficherSousMenuDeAffichageDesEtudiantes();
            continue;
        case 3:
            afficherSousMenuDeManipulation();
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


// --------- Les Fonction D'Ajoute ---------
void afficherSousMenuDajout(){
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

        if (ajouteUnEtudiant(nom, prenom, dateDeNaissance, noteGenerale) == -1)
        {
            puts("\nEurreur lors l'ajoutation.");
            return;
        }  
    }
    

    printf("\n");
    if (n == 1)
    {
        puts("L'Etudiant ajoutee avec succes.");
    }
    else
    {
        puts("Les Etudiants sont ajoutee avec succes.");
    }
}

int obtenirDepartementIndice(){ // Retourner l'indice de departement si exister, si non retourner -1

    int len = sizeof(departements) / sizeof(departements[0]);
    int choix;

    // Afficher les departements
    for (int i = 0; i < len; i++)
    {
        printf("\t%d. %s\n", i + 1, departements[i]);
    }
    
    printf("\n\tChoisi le departement: ");
    scanf("%d", &choix);
    while (getchar() != '\n'); // Nettoyer le buffer

    // Validatiton de choix
    if (choix < 1 || choix > len)
    {
        return -1;
    }

    
    return choix - 1; // Pour obtenu l'indice
}

int ajouteUnEtudiant(char nom[], char prenom[], Date dateDeNaissance, int noteGenerale) { // Retourner 1 si l'ajout est succes, si non -1
    
    Etudiant etudiant;

    int indice = nombreDesEtudiants;

    int departement = obtenirDepartementIndice();
    if (departement == -1) return -1;

    etudiant.id = id++;
    strcpy(etudiant.nom, nom);
    strcpy(etudiant.prenom, prenom);
    etudiant.noteGenerale = noteGenerale;
    etudiant.dateDeNaissance = dateDeNaissance;

    etudiant.departement = departement;
    
    etudiants[indice] = etudiant;

    nombreDesEtudiants++;

    return 1;
}


// --------- Les Fonction D'affichage ---------
void afficherSousMenuDeAffichageDesEtudiantes(){
    int choix;

    while (1) {
        
        puts("\n\t1. Selon l'ordre de nom (croissante)");
        puts("\t2. Selon l'ordre de nom (decroissante)");
        puts("\t3. Selon l'ordre de note generale (croissante)");
        puts("\t4. Selon l'ordre de note generale (decroissante)");
        puts("\t5. Afficher les etudiants reussite (croissante)");
        puts("\t6. Afficher les etudiants reussite (decroissante)");
        puts("\t7. Retour au menu principal");
        
        printf("\nEntrer votre choix: ");
        scanf("%d", &choix);
        while (getchar() != '\n');

        switch (choix) {
            case 1:
                triEtAfficherLesEtudiantsParNom(1); // croissante
                break;
            case 2:
                triEtAfficherLesEtudiantsParNom(0); // decroissante
                break;
            case 3:
                triEtAfficherLesEtudiantsParNoteGenerale(1); // croissante
                break;
            case 4:
                triEtAfficherLesEtudiantsParNoteGenerale(0); // decroissante
                break;
            case 5:
                triEtAfficherLesEtudiantsReussite(1);
                break;
            case 6:
                triEtAfficherLesEtudiantsReussite(0);
                break;
            case 7:
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
            while (getchar() != '\n');
        }
    }
}

void afficherLesEtudiants(Etudiant triEtudiants[], int croissante, int len){
    puts("Les Etudiants: \n");

    // Afficher les colonnes
    printLesColonnes();

    if (len == 0)
    {
        printNexistePas();
    }

    // Afficher les lignes
    for (int i = 0; i < len; i++)
    {
        int indice = croissante ? i : len - 1 - i;
        printUnEtudiantLigne(triEtudiants[indice]);
    }
}

void triEtAfficherLesEtudiantsParNom(int croissante){
    Etudiant cpy[100];
    memcpy(cpy, etudiants, nombreDesEtudiants * sizeof(Etudiant));

    // Tri á bulles
    for (int i = 0; i < nombreDesEtudiants; i++)
    {
        for (int j = 0; j < nombreDesEtudiants - 1 - i; j++)
        {
            if (strcmp(cpy[j].nom, cpy[j + 1].nom) > 0)
            {
                Etudiant temp = cpy[j];
                cpy[j] = cpy[j + 1];
                cpy[j + 1] = temp;
            }
        } 
    }

    afficherLesEtudiants(cpy, croissante, nombreDesEtudiants);
}

void triEtAfficherLesEtudiantsParNoteGenerale(int croissante){
    Etudiant cpy[100];
    memcpy(cpy, etudiants, nombreDesEtudiants * sizeof(Etudiant));

    // Tri á bulles
    for (int i = 0; i < nombreDesEtudiants; i++)
    {
        for (int j = 0; j < nombreDesEtudiants - 1 - i; j++)
        {
            if (cpy[j].noteGenerale > cpy[j + 1].noteGenerale)
            {
                Etudiant temp = cpy[j];
                cpy[j] = cpy[j + 1];
                cpy[j + 1] = temp;
            }
        } 
    }

    afficherLesEtudiants(cpy, croissante, nombreDesEtudiants);
}

void triEtAfficherLesEtudiantsReussite(int croissante){

    Etudiant cpy[100];

    int count = 0;

    for (int i = 0; i < nombreDesEtudiants; i++)
    {
        if (etudiants[i].noteGenerale >= 10)
        {
            cpy[count] = etudiants[i];
            count++;
        }
    } 

    // Tri á bulles
    for (int i = 0; i < nombreDesEtudiants; i++)
    {
        for (int j = 0; j < nombreDesEtudiants - 1 - i; j++)
        {
            if (cpy[j].noteGenerale > cpy[j + 1].noteGenerale)
            {
                Etudiant temp = cpy[j];
                cpy[j] = cpy[j + 1];
                cpy[j + 1] = temp;
            }
        } 
    }

    afficherLesEtudiants(cpy, croissante, count);
}


// --------- Les Fonction De Manipulation ---------
void afficherSousMenuDeManipulation(){
    int choix;

    while (1) {
        
        puts("\n\t1. Modifier Un Etudiant");
        puts("\t2. Supprimer Un Etudiant");
        puts("\t3. Retour au menu principal");
        
        printf("\nEntrer votre choix: ");
        scanf("%d", &choix);
        while (getchar() != '\n');

        switch (choix) {
            case 1:
                modifierUnEtudiant();
                break;
            case 2:
                // supprimerUnEtudiant();
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
            while (getchar() != '\n');
        }
    }
}

void modifierUnEtudiant(){
    int id;

    puts("Modifier Un Etudiant: \n");

    printf("\tEntrer le ID d'etudiant: ");
    scanf("%d", &id);
    while (getchar() != '\n');  // Nettoyer le buffer

    int indice = rechercheParId(id);

    if (indice == -1)
    {
        puts("\nCette etudiant n'existe pas.");
        return;
    }
    
    char nom[MAX_NOM];
    char prenom[MAX_PRENOM];
    int departement;
    float noteGenerale;
    Date dateDeNaissance;
    
    printf("\tEntrer le nouvelle nom: ");
    scanString(nom, sizeof(nom));
    
    printf("\tEntrer le nouvelle prenom: ");
    scanString(prenom, sizeof(prenom));

    printf("\tEntrer l'annee de naissance: ");
    scanf("%d", &dateDeNaissance.annee);

    printf("\tEntrer le mois de naissance: ");
    scanf("%d", &dateDeNaissance.mois);

    printf("\tEntrer le jour de naissance: ");
    scanf("%d", &dateDeNaissance.jour);

    printf("\tEntrer la nouvelle note generale: ");
    scanf("%f", &noteGenerale);
    while (getchar() != '\n');  // Nettoyer le buffer

    printf("\n");
    departement = obtenirDepartementIndice();
    if (departement == -1){
        puts("Choix Invalid.");
        return;
    }

    strcpy(etudiants[indice].nom, nom);
    strcpy(etudiants[indice].prenom, prenom);
    etudiants[indice].noteGenerale = noteGenerale;
    etudiants[indice].dateDeNaissance = dateDeNaissance;

    etudiants[indice].departement = departement;
    
    puts("\nLes informations de l'etudiant sont modifie avec succes.");
}

int rechercheParId(int id){ // Retourner l'indice d'etudiant si trouver, si non retourner -1

    int g = 0;
    int d = nombreDesEtudiants - 1;

    // Recherche Binaire
    while (g <= d) {
        int mid = (d + g) / 2;

        if (etudiants[mid].id == id) { // Si trouver

            return mid; 
        }
        else if (id > etudiants[mid].id) {
            g = mid + 1;
        } else {
            d = mid - 1;
        }
    }

    return -1;
}



void printLesColonnes(){
    printUnligne();
    printf("\t| %-3s | %-20s | %-20s | %-13s | %-20s | %-14s |\n", "ID", "Nom", "Prenom", "Note Generale", "Departement", "Date De Naissance");
    printUnligne();
}
void printUnEtudiantLigne(Etudiant etudiant){
    printf("\t| %-3d | %-20s | %-20s | %8.2f      | %-20s |     %d/%02d/%4d     |\n",
        etudiant.id, etudiant.nom, etudiant.prenom, etudiant.noteGenerale, departements[etudiant.departement],
        etudiant.dateDeNaissance.jour, etudiant.dateDeNaissance.mois, etudiant.dateDeNaissance.annee 
    );
    printUnligne();
}  
void printUnEtudiant(Etudiant etudiant){
    printf("\tLe ID: %d\n", etudiant.id);
    printf("\tLe Nom: %s\n", etudiant.nom);
    printf("\tLe Prenom: %s\n", etudiant.prenom);
    printf("\tLa Note Generale: %f\n", etudiant.noteGenerale);
    printf("\tLa Departement: %s\n", departements[etudiant.departement]);

    Date date = etudiant.dateDeNaissance;
    printf("\tLa Date de naissance: %02d/%02d/%4d\n", date.jour, date.mois, date.annee);
}
void printNexistePas(){
    printf("\t|                                  ");
    printf("%-40s", "N'existe pas des etudiants pour afficher.");
    printf("                                   |\n");
    printUnligne();
}
void printUnligne(){
    printf("\t+-----+----------------------+----------------------+---------------+----------------------+-------------------+\n");
}



void scanString(char string[], int size){
    if (fgets(string, size, stdin) != NULL) {
        string[strcspn(string, "\n")] = '\0';
    }
}