#include <stdio.h>
#include <string.h>
#include <ctype.h>


// Définir les constants
#define MAX_NOM 30
#define MAX_PRENOM 30
#define MAX_ETUDIANTS 100

// Définir la structure de la date
typedef struct {
    int jour;
    int mois;
    int annee;
} Date;

// Définir la structure d'etudiante
typedef struct {
    int id;
    char nom[MAX_NOM];
    char prenom[MAX_PRENOM];
    Date dateDeNaissance;
    int departement;
    float noteGenerale;
} Etudiant;

// Définir les global variables
Etudiant etudiants[MAX_ETUDIANTS];
int nombreDesEtudiants = 0;
int id = 1;

char departements[][20] = {"Mathematiques", "Physique", "Chimie", "Economique", "Informatique"};
int nombreDesDepartements = sizeof(departements) / sizeof(departements[0]);

// Définier les fonctions
void afficherSousMenuDajout();
void ajouteDesEtudiants(int n);
int obtenirDepartementIndice();
int ajouteUnEtudiant(char nom[], char prenom[], Date dateDeNaissance, float noteGenerale);

void afficherSousMenuDeAffichageDesEtudiantes();
void afficherLesEtudiants(Etudiant triEtudiants[], int croissante, int len);
void triEtAfficherLesEtudiantsParNom(int croissante);
void triEtAfficherLesEtudiantsParNoteGenerale(int croissante);
void triEtAfficherLesEtudiantsReussite(int croissante);

void afficherSousMenuDeManipulation();
void modifierUnEtudiant();
void supprimerUnEtudiant();

void afficherSousMenuDeRecherche();
void afficherUnEtudiantParId();
void afficherUnEtudiantParNom();
void afficherLesEtudiantsDansUnDepratement();


void afficherSousMenuDesStatistiques();
void afficherLeNombreDesEtudiantsAyantUnNoteSuperieureAseuil();
void afficherLesTroisMeilleurEtudiants();
void afficherLeNombreDesEtudiantsDansChaqueDepartement();
void afficherLesEtudiantsReussiDansChaqueDepratement();
void afficherLeMoyenneGeneraleDeChaqueDepratement();


void printLesColonnes();
void printUnEtudiantLigne(Etudiant etudiant);
void printUnEtudiant(Etudiant etudiant);
void printNexistePas();
void printUnligne();

int rechercheParId(int id);
void obtenirLaMention(char mention[], int note);
void scanString(char string[], int size);
void capitaliseUnString(char string[], int size);

void seed(); // Ajouter pseudo informations

// --------- Le Main Fonction ---------
int main(){

    seed();

    // La menu principale
    while (1)
    {
        puts("\n#### Gestion des etudiants d'universite ####");
        puts("\n\t1. Ajouter Des Etudiants");
        puts("\t2. Afficher Les Etudiants");
        puts("\t3. Manipulation D'un Etudiant");
        puts("\t4. Rechercher Des Etudiants");
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
            afficherSousMenuDeRecherche();
            continue;
        case 5:
            afficherSousMenuDesStatistiques();
            continue;
        case 6:
            return 0;
        
        default:
            puts("Choix invalide.");
        }

        // Pour retour au menu principal
        choix = 0;
        while (choix != 1) {
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
    int n;
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
                ajouteDesEtudiants(1); // Ajoute 1 etudiant
                break;
            case 2:
                printf("Combien des etudiants vous voulez entrer: ");
                scanf("%d", &n);
                while (getchar() != '\n'); // Nettoyer le buffer

                ajouteDesEtudiants(n); // Ajoute n des etudiant
                break;
            case 3:
                return; // Retourne au menu principal
            default:
                puts("Choix invalide.");
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

    printf("\n");
    
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

int ajouteUnEtudiant(char nom[], char prenom[], Date dateDeNaissance, float noteGenerale) { // Retourner 1 si l'ajout est succes, si non -1
    
    Etudiant etudiant;

    int indice = nombreDesEtudiants;

    int departement = obtenirDepartementIndice();
    if (departement == -1) return -1;

    capitaliseUnString(nom, MAX_NOM);
    capitaliseUnString(prenom, MAX_PRENOM);

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

int obtenirDepartementIndice(){ // Retourner l'indice de departement si exister, si non retourner -1
    int choix;

    // Afficher les departements
    for (int i = 0; i < nombreDesDepartements; i++)
    {
        printf("\t%d. %s\n", i + 1, departements[i]);
    }
    
    printf("\n\tChoisi le departement: ");
    scanf("%d", &choix);
    while (getchar() != '\n'); // Nettoyer le buffer

    // Validatiton de choix
    if (choix < 1 || choix > nombreDesDepartements)
    {
        return -1;
    }

    
    return choix - 1; // Pour obtenu l'indice
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
                puts("Choix invalide.");
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

void triEtAfficherLesEtudiantsParNom(int croissante){ // 1 si pour l'affichage croissante, 0 pour decroissante
    Etudiant cpy[MAX_ETUDIANTS];
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

void triEtAfficherLesEtudiantsParNoteGenerale(int croissante){ // 1 si pour l'affichage croissante, 0 pour decroissante
    Etudiant cpy[MAX_ETUDIANTS];
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

void triEtAfficherLesEtudiantsReussite(int croissante){ // 1 si pour l'affichage croissante, 0 pour decroissante

    Etudiant cpy[MAX_ETUDIANTS];

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
    for (int i = 0; i < count; i++)
    {
        for (int j = 0; j < count - 1 - i; j++)
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
                supprimerUnEtudiant();
                break;
            case 3:
                return; // Retourne au menu principal
            default:
                puts("Choix invalide.");
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

    if (indice == -1) // Si n'existe pas
    {
        puts("\nCette etudiant n'existe pas.");
        return;
    }

    puts("\n\t1. Modifier le nom");
    puts("\t2. Modifier le prenom");
    puts("\t3. Modifier la departement");
    puts("\t4. Modifier la note generale");
    puts("\t5. Modifier la date de naissance");
    
    int champ;
    printf("\n\tChoisi le champ tu veux modifier: ");
    scanf("%d", &champ);
    while (getchar() != '\n');  // Nettoyer le buffer

    char nom[MAX_NOM];
    char prenom[MAX_PRENOM];
    int departement;
    float noteGenerale;
    Date dateDeNaissance;

    printf("\n");
    switch (champ)
    {
    case 1:
        printf("\tEntrer le nouvelle nom: ");
        scanString(nom, sizeof(nom));
        capitaliseUnString(nom, MAX_NOM);
        strcpy(etudiants[indice].nom, nom);
        break;
    case 2:
        printf("\tEntrer le nouvelle prenom: ");
        scanString(prenom, sizeof(prenom));
        capitaliseUnString(nom, MAX_PRENOM);
        strcpy(etudiants[indice].prenom, prenom);
        break;
    case 3:
        departement = obtenirDepartementIndice();
        if (departement == -1){
            puts("Choix Invalide.");
            return;
        }
        etudiants[indice].departement = departement;
        break;
    case 4:
        printf("\tEntrer la nouvelle note generale: ");
        scanf("%f", &noteGenerale);
        while (getchar() != '\n');  // Nettoyer le buffer

        etudiants[indice].noteGenerale = noteGenerale;
        break;
    case 5:
        printf("\tEntrer l'annee de naissance: ");
        scanf("%d", &dateDeNaissance.annee);

        printf("\tEntrer le mois de naissance: ");
        scanf("%d", &dateDeNaissance.mois);

        printf("\tEntrer le jour de naissance: ");
        scanf("%d", &dateDeNaissance.jour);
        while (getchar() != '\n');  // Nettoyer le buffer

        etudiants[indice].dateDeNaissance = dateDeNaissance;
        break;
    
    default:
        puts("Choix Invalide.");
        return;
    }

    puts("\nLes informations de l'etudiant sont modifie avec succes.");
}

void supprimerUnEtudiant(){
    int id;
    char confirmation[4];

    puts("Supprimer Un Etudiant: \n");

    printf("\tEntrer le ID d'etudiant: ");
    scanf("%d", &id);
    while (getchar() != '\n');  // Nettoyer le buffer

    int indice = rechercheParId(id);

    if (indice == -1)
    {
        puts("\nCette etudiant n'existe pas.");
        return;
    }
    
    // Confirmation de l'operation
    printf("\tVoulez-vous vraiment supprimer l'etudiant ? (oui/non): ");
    scanString(confirmation, sizeof(confirmation));

    printf("\n");

    if (strcmp(confirmation, "oui") != 0) {
        puts("Suppression annulee.");
        return;
    }

    for (int i = indice; i < nombreDesEtudiants - 1; i++)
    {
        etudiants[i] = etudiants[i + 1];
    }

    nombreDesEtudiants--;

    puts("Etudiant supprime avec succes.");
}


// --------- Les Fonction De Recherche ---------
void afficherSousMenuDeRecherche(){
    int choix;

    while (1) {
        
        puts("\n\t1. Rechercher par ID");
        puts("\t2. Recherche par Nom");
        puts("\t3. Recherche par departement");
        puts("\t4. Retour au menu principal");
        
        printf("\nEntrer votre choix: ");
        scanf("%d", &choix);
        while (getchar() != '\n');

        switch (choix) {
            case 1:
                afficherUnEtudiantParId();
                break;
            case 2:
                afficherUnEtudiantParNom();
                break;
            case 3:
                afficherLesEtudiantsDansUnDepratement();
                break;
            case 4:
                return; // Retourne au menu principal
            default:
                puts("Choix invalide.");
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

void afficherUnEtudiantParId(){
    int id;

    printf("\n\tEntrer le ID d'etudiant: ");
    scanf("%d", &id);
    while (getchar() != '\n');  // Nettoyer le buffer

    int indice = rechercheParId(id);

    if (indice == -1)
    {
        puts("\nCette etudiant n'existe pas.");
        return;
    }

    printUnEtudiant(etudiants[indice]);
}

void afficherUnEtudiantParNom(){
    char nom[MAX_NOM];

    printf("\n\tEntrer le nom: ");
    scanString(nom, sizeof(nom));

    int trouver = 0;

    for (int i = 0; i < nombreDesEtudiants; i++)
    {
        if (strcmp(nom, etudiants[i].nom) == 0)
        {
            printUnEtudiant(etudiants[i]);
            trouver = 1;
        }
        
    }
    

    if (trouver == 0)
    {
        puts("\nCette etudiant n'existe pas.");
        return;
    }
}

void afficherLesEtudiantsDansUnDepratement(){
    
    printf("\n");
    int departement = obtenirDepartementIndice();
    if (departement == -1)
    {
        puts("Choix Invalide.");
        return;
    }
    
    printf("\nLes Etudiants Dans La Departement ( %s ): \n\n", departements[departement]);

    // Afficher les colonnes
    printLesColonnes();


    int count = 0;

    // Afficher les lignes
    for (int i = 0; i < nombreDesEtudiants; i++)
    {
        if (etudiants[i].departement == departement) // Si la meme departement
        {
            printUnEtudiantLigne(etudiants[i]);
            count++;
        }

    }

    
    if (count == 0)
    {
        printNexistePas();
    }
}


// --------- Les Fonction De Statistiques ---------
void afficherSousMenuDesStatistiques(){
    int choix;

    while (1) {
        
        puts("\n\t1. Le nombre total des etudiants inscrits");
        puts("\t2. Le nombre des etudiants ayant une note superieure a une seuil");
        puts("\t3. Le trois meilleure etudiants");
        puts("\t4. Le nombre des etudiants dans chaque departement");
        puts("\t5. Le nombre des etudiants reussir dans chaque departement");
        puts("\t6. Le Moyenne generale de chaque departement");
        puts("\t7. Retour au menu principal");
        
        printf("\nEntrer votre choix: ");
        scanf("%d", &choix);
        while (getchar() != '\n');

        switch (choix) {
            case 1:
                printf("\nLe nombre total des etudiants inscrits: %d\n", nombreDesEtudiants);
                break;
            case 2:
                afficherLeNombreDesEtudiantsAyantUnNoteSuperieureAseuil();
                break;
            case 3:
                afficherLesTroisMeilleurEtudiants();
                break;
            case 4:
                afficherLeNombreDesEtudiantsDansChaqueDepartement();
                break;
            case 5:
                afficherLesEtudiantsReussiDansChaqueDepratement();
                break;
            case 6:
                afficherLeMoyenneGeneraleDeChaqueDepratement();
                break;
            case 7:
                return; // Retourne au menu principal
            default:
                puts("Choix invalide.");
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

void afficherLeNombreDesEtudiantsAyantUnNoteSuperieureAseuil(){
    float seuil;
    printf("\n\tEntrer le seuil: ");
    scanf("%f", &seuil);
    while (getchar() != '\n');

    printf("\n");

    int count = 0;

    if (seuil < 0 || seuil > 20)
    {
        puts("Invalide seuil.");
        return;
    }

    for (int i = 0; i < nombreDesEtudiants; i++)
    {
        if (etudiants[i].noteGenerale >= seuil)
        {
            count++;
        }
        
    }
    
    printf("\tLe Nombre des etudiants ayant un note superieure a %.2f est: %d\n", seuil, count);
}

void afficherLesTroisMeilleurEtudiants(){

    printf("\n");
    if (nombreDesEtudiants < 3)
    {
        puts("Le nombre des etudiantes est inferieure a 3.");
        return;
    }
    puts("Les meilleurs trois etudiants: ");
    

    Etudiant etudiant1, etudiant2, etudiant3;

    for (int i = 0; i < nombreDesEtudiants; i++)
    {
        if (etudiants[i].noteGenerale > etudiant1.noteGenerale) {
            Etudiant temp1 = etudiant1;
            Etudiant temp2 = etudiant2;
            etudiant1 = etudiants[i];
            etudiant2 = temp1;
            etudiant3 = temp2;
        } else if (etudiants[i].noteGenerale > etudiant2.noteGenerale) {
            Etudiant temp2 = etudiant2;
            etudiant2 = etudiants[i];
            etudiant3 = temp2;
        } else if (etudiants[i].noteGenerale > etudiant3.noteGenerale) {
            etudiant3 = etudiants[i];
        }
    }

    printLesColonnes();
    printUnEtudiantLigne(etudiant1);
    printUnEtudiantLigne(etudiant2);
    printUnEtudiantLigne(etudiant3);
}

void afficherLeNombreDesEtudiantsDansChaqueDepartement(){
    puts("\nLe nombre des etudiants dans chaque departement:\n");

    for (int i = 0; i < nombreDesDepartements; i++)
    {
        int count = 0;
        for (int j = 0; j < nombreDesEtudiants; j++)
        {
            if (etudiants[j].departement == i)
            {
                count++;
            }
        }

        printf("\t%d. %-15s => %d\n", i + 1, departements[i], count);
    }
}

void afficherLesEtudiantsReussiDansChaqueDepratement(){
    puts("\nLe nombre des etudiants reussi dans chaque departement:\n");

    for (int i = 0; i < nombreDesDepartements; i++)
    {
        int count = 0;
        for (int j = 0; j < nombreDesEtudiants; j++)
        {
            if (etudiants[j].departement == i && etudiants[j].noteGenerale >= 10)
            {
                count++;
            }
        }

        printf("\t%d. %-15s => %d\n", i + 1, departements[i], count);
    }
}

void afficherLeMoyenneGeneraleDeChaqueDepratement(){
    puts("\nLe moyenne generale de chaque departement:\n");

    int count = 0;
    float sommeDepartement = 0;
    float somme = 0;

    for (int i = 0; i < nombreDesDepartements; i++)
    {
        count = 0;
        sommeDepartement = 0;
        for (int j = 0; j < nombreDesEtudiants; j++)
        {
            if (etudiants[j].departement == i)
            {
                sommeDepartement += etudiants[j].noteGenerale;
                count++;
            }
        }
        somme += sommeDepartement;

        printf("\t%d. %-15s => %.2f\n", i + 1, departements[i], count != 0 ? sommeDepartement / count : 0);
    }

    printf("\t%d. %-15s => %.2f\n", nombreDesDepartements + 1, "Universite" ,nombreDesEtudiants != 0 ? somme / nombreDesEtudiants: 0);
}


void printLesColonnes(){
    printUnligne();
    printf("\t| %-3s | %-20s | %-20s | %-13s | %-12s | %-20s | %-14s |\n", "ID", "Nom", "Prenom", "Note Generale", "Mention", "Departement", "Date De Naissance");
    printUnligne();
}
void printUnEtudiantLigne(Etudiant etudiant){
    char mention[10];

    obtenirLaMention(mention, etudiant.noteGenerale);
    
    printf("\t| %-3d | %-20s | %-20s | %8.2f      | %-12s | %-20s |     %02d/%02d/%4d    |\n",
        etudiant.id, etudiant.nom, etudiant.prenom, etudiant.noteGenerale, mention, departements[etudiant.departement],
        etudiant.dateDeNaissance.jour, etudiant.dateDeNaissance.mois, etudiant.dateDeNaissance.annee 
    );
    printUnligne();
}  
void printUnEtudiant(Etudiant etudiant){
    char mention[10];

    obtenirLaMention(mention, etudiant.noteGenerale);

    printf("\n\t-------------------------\n");
    printf("\tLe ID: %d\n", etudiant.id);
    printf("\tLe Nom: %s\n", etudiant.nom);
    printf("\tLe Prenom: %s\n", etudiant.prenom);
    printf("\tLa Note Generale: %.2f\n", etudiant.noteGenerale);
    printf("\tLa Mention: %s\n", mention);
    printf("\tLa Departement: %s\n", departements[etudiant.departement]);

    Date date = etudiant.dateDeNaissance;
    printf("\tLa Date de naissance: %02d/%02d/%4d\n", date.jour, date.mois, date.annee);
}
void printNexistePas(){
    printf("\t|%-42s", " ");
    printf("%-40s", "N'existe pas des etudiants pour afficher.");
    printf("%-42s|\n", " ");
    printUnligne();
}
void printUnligne(){
    printf("\t+-----+----------------------+----------------------+---------------+--------------+----------------------+-------------------+\n");
}

// --------- Des Fonction Auxiliares ---------
void obtenirLaMention(char mention[], int note){
    if (note < 10)
    {
        strcpy(mention, "Insuffisant");
    }
    else if (note < 14)
    {
        strcpy(mention, "Passage");
    }
    else if (note < 17)
    {
        strcpy(mention, "Bien");
    }
    else
    {
        strcpy(mention, "Tres Bien");
    }
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

void scanString(char string[], int size){
    if (fgets(string, size, stdin) != NULL) {
        string[strcspn(string, "\n")] = '\0'; // Replacer le \n avec \0
    }
}

void capitaliseUnString(char string[], int size){ // capitaliser un string, "iLyasS" => "Ilyass"
    string[0] = toupper(string[0]);

    for (int i = 1; i < size; i++)
    {
        string[i] = tolower(string[i]);
    }
}



void seed() { // Seed les information
    Etudiant etudiant;
    Date dateDeNaissance;

    // Les informations
    const char noms[][MAX_NOM] = {"Ilyass", "Ahmed", "Oussama", "Saad", "Leila", "Nadia", "Youssef", "Mariam", "Karim"};
    const char prenoms[][MAX_PRENOM] = {"Anida", "Chanaoui", "Amou", "Mared", "Benaissa", "Haddad", "Tariq", "Khalil", "Said"};
    const float notes[] = {17.5, 9, 10.5, 14, 12, 15, 11, 19, 8.25};
    const int annees[] = {2007, 2003, 2001, 2005, 2006, 2004, 2002, 2004, 2004};
    const int mois[] = {2, 5, 9, 4, 11, 7, 8, 1, 3};
    const int jours[] = {5, 6, 11, 2, 17, 21, 30, 12, 22};
    const int departements[] = {3, 3, 1, 4, 0, 2, 4, 1, 2};

    // Ajouter les infromations
    for (int i = 0; i < 9; ++i) {
        etudiant.id = id++;
        strcpy(etudiant.nom, noms[i]);
        strcpy(etudiant.prenom, prenoms[i]);
        etudiant.noteGenerale = notes[i];
        dateDeNaissance.annee = annees[i];
        dateDeNaissance.mois = mois[i];
        dateDeNaissance.jour = jours[i];
        etudiant.dateDeNaissance = dateDeNaissance;
        etudiant.departement = departements[i];
        etudiants[nombreDesEtudiants++] = etudiant;
    }
}
