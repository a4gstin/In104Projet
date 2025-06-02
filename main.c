#include <stdio.h>      // Inclusion de la bibliothèque standard pour les entrées/sorties
#include <stdlib.h>     // Inclusion pour la gestion de la mémoire dynamique (malloc, free, etc.)
#include <string.h>     // Inclusion pour la manipulation des chaînes de caractères
#include <stdbool.h>    // Inclusion pour le type booléen (true/false)

// Importation du fichier d'en-tête où sont déclarées les fonctions du projet
#include "generalFunctions.h"
#include "searchFunctions.h"

// Définition des constantes utilisées dans le programme
#define MAX_USERS 100           // Nombre maximal d'utilisateurs dans le réseau
#define NO_CONNECTION 0         // Valeur représentant l'absence de connexion entre deux utilisateurs

// Définition de la structure représentant un utilisateur du réseau social
typedef struct {
    char name[50];      // Nom de l'utilisateur
    int index;          // Indice de l'utilisateur dans le tableau
    char* bio;          // Pointeur vers la biographie de l'utilisateur
    char* school;       // Pointeur vers l'école de l'utilisateur
} User;

// Déclaration des variables globales (définies ailleurs) pour gérer les utilisateurs et le graphe
extern User users[MAX_USERS];                       // Tableau des utilisateurs
extern int adjacencyMatrix[MAX_USERS][MAX_USERS];   // Matrice d'adjacence représentant les amitiés
extern int userCount;                               // Nombre actuel d'utilisateurs

// Fonction d'affichage du logo du réseau social
void make_logo(){
    // Affiche un logo ASCII pour l'application
    printf("            _________________________\n");
    printf("\n");
    printf("            (|__ /)   \n");
    printf("            (=’.’=)  \n");
    printf("            (\")_(\")  \n");
    printf("            (')_(')   TAEP SOCIAL \n");
    printf("            _________________________\n");
    printf("\n");
    printf("\n");
}

// Fonction qui lit les utilisateurs et les amitiés depuis un fichier texte
void readFromFile(const char *filename) {
    FILE *file = fopen(filename, "r"); // Ouvre le fichier en lecture
    if (!file) {
        printf("Error opening file!\n"); // Affiche une erreur si le fichier ne s'ouvre pas
        return;
    }
    printf("Reading users from file...\n");

    // Lecture du nombre d'utilisateurs
    int NB_USERS;
    fscanf(file, "%d", &NB_USERS);
    userCount = NB_USERS;
    // Lecture des informations de chaque utilisateur
    for (int i = 0; i < NB_USERS; i++) {
        char name[50];
        fscanf(file, "%s", name);
        User add_user = {0};
        strncpy(add_user.name, name, sizeof(add_user.name) - 1);
        add_user.name[sizeof(add_user.name) - 1] = '\0';
        add_user.index = i;

        // Si le fichier est "social_network_updated.txt", on lit aussi la bio et l'école
        if (strcmp(filename, "social_network_updated.txt") == 0) {
            char bio[200], school[50];
            fscanf(file, " %[^\n]", bio);
            fscanf(file, " %[^\n]", school);
            add_user.bio = malloc(strlen(bio) + 1);
            strcpy(add_user.bio, bio);
            add_user.school = malloc(strlen(school) + 1);
            strcpy(add_user.school, school);
        } else {
            // Sinon, on met bio et school à NULL
            add_user.bio = NULL;
            add_user.school = NULL;
        }
        users[i] = add_user;
    }

    // Lecture du nombre d'amitiés
    int NB_USERS_FRIENDSHIP;
    fscanf(file, "%d", &NB_USERS_FRIENDSHIP);
    // Lecture des amitiés et remplissage de la matrice d'adjacence
    for (int i = 0; i < NB_USERS_FRIENDSHIP; i++) {
        int friend1, friend2, friendship_strenght;
        fscanf(file, "%d %d %d", &friend1, &friend2, &friendship_strenght);
        adjacencyMatrix[friend1][friend2] = friendship_strenght;
        adjacencyMatrix[friend2][friend1] = friendship_strenght;
    }

    fclose(file); // Fermeture du fichier
}

// Fonction pour sauvegarder les utilisateurs et les amitiés dans un fichier
void saveToFile(const char *filename) {
    FILE *file = fopen(filename, "w"); // Ouvre le fichier en écriture
    if (!file) {
        printf("Error opening file for writing!\n");
        return;
    }
    // Écriture du nombre d'utilisateurs
    fprintf(file, "%d\n", userCount);
    // Écriture des informations de chaque utilisateur
    for (int i = 0; i < userCount; i++) {
        fprintf(file, "%s\n", users[i].name);
        // Si on sauvegarde dans "social_network_updated.txt", on écrit aussi bio et school
        if (strcmp(filename, "social_network_updated.txt") == 0) {
            fprintf(file, "%s\n", users[i].bio ? users[i].bio : "No bio information available");
            fprintf(file, "%s\n", users[i].school ? users[i].school : "No school information available");
        }
    }
    // Comptage du nombre d'amitiés
    int friendshipCount = 0;
    for (int i = 0; i < userCount; i++) {
        for (int j = i + 1; j < userCount; j++) {
            if (adjacencyMatrix[i][j] != NO_CONNECTION) {
                friendshipCount++;
            }
        }
    }
    // Écriture du nombre d'amitiés
    fprintf(file, "%d\n", friendshipCount);
    // Écriture des amitiés (indices et force)
    for (int i = 0; i < userCount; i++) {
        for (int j = i + 1; j < userCount; j++) {
            if (adjacencyMatrix[i][j] != NO_CONNECTION) {
                fprintf(file, "%d %d %d\n", i, j, adjacencyMatrix[i][j]);
            }
        }
    }
    fclose(file); // Fermeture du fichier
}




int main() {
    initializeGraph(); // Initialisation de la matrice d'adjacence (graphe)

    // Affichage du menu de sélection du fichier à charger
    printf("Welcome to the social network!\n");
    printf("Enter the name of the file containing the most recent history of the social network.\n");
    printf("The file should be : \n");
    printf("\n");
    printf("1. social_network.txt\n");
    printf("2. social_network_updated.txt\n");
    printf("\n");
    printf("Please enter the number corresponding to the file you want to use:\n");

    // Lecture du choix de l'utilisateur pour le fichier à charger
    int choice0=0;
    while (choice0 != 1 && choice0 != 2) {
        printf("Enter your choice (1 or 2): ");
        scanf("%d", &choice0);
        if (choice0 == 1) {
            printf("You chose social_network.txt\n");
            readFromFile("social_network.txt"); // Chargement du fichier de base
        } else if (choice0 == 2) {
            printf("You chose social_network_updated.txt\n");
            readFromFile("social_network_updated.txt"); // Chargement du fichier avec bio/école
        } else {
            printf("Invalid choice. Please try again.\n");
        }
    }
    // Séparation visuelle
    printf("\n\n\n\n");
    for(int i=0; i<70; i++){
        printf("-") ;
    }
    printf("\n");

    // Connexion de l'utilisateur
    printf("connecter vous à votre réseau social \n");
    printf("\n\n");
    printf("Entrez votre nom user:\n");
    char name[50];
    scanf("%s", name);
    int userIndex = findUserIndex(name);

    // Si l'utilisateur n'existe pas, proposer de le créer
    if (userIndex == -1) {
        printf("\n\n\n\n");
        for(int i=0; i<70; i++){
            printf("-") ;
        }
        printf("\n\n");
        printf("User not found.");
        printf(" Do you want to create a new user? (y/n)\n");
        printf("\n\n\n\n");
        char createUserChoice;
        scanf(" %c", &createUserChoice);
        if (createUserChoice != 'y' && createUserChoice != 'Y') {
            // Si l'utilisateur refuse, quitter le programme
            printf("Exiting...\n");
            for(int i=0; i<70; i++){
                printf("-") ;
            }
            printf("\n");
            printf("Press Enter to continue...");
            getchar();
            getchar(); // Attente de l'utilisateur
            printf("\n");
            return 1;
        }
        else if (createUserChoice == 'y' || createUserChoice == 'Y') {
            // Création d'un nouvel utilisateur
            printf("\n\n\n\n\n\n");
            for(int i=0; i<70; i++){
                printf("-") ;
            }
            printf("\n");
            printf("Creating a new user...\n");
            if (userCount >= MAX_USERS) {
                // Si le nombre max d'utilisateurs est atteint
                printf("User limit reached. Cannot create a new user.\n");
                for(int i=0; i<70; i++){
                    printf("-") ;
                }
                printf("\n");
                printf("Press Enter to continue...");
                getchar(); 
                getchar();
                return 1;
            }
            printf("\n");
            printf("Creating a new user...\n");
            User newUser;
            strncpy(newUser.name, name, sizeof(newUser.name) - 1);
            newUser.name[sizeof(newUser.name) - 1] = '\0';
            newUser.index = userCount;
            newUser.bio = NULL;
            newUser.school = NULL;
            users[userCount] = newUser;
            userIndex = userCount++;
            printf("New user created: %s\n", users[userIndex].name);
            printf("\n");
            for(int i=0; i<70; i++){
                printf("-") ;
            }
            printf("\n");
            // Demander une bio à l'utilisateur
            printf("Do you want to add a bio? (y/n)\n");
            char addBioChoice;
            scanf(" %c", &addBioChoice);
            if (addBioChoice == 'y' || addBioChoice == 'Y') {
                printf("Enter your bio:\n");
                int c;
                while ((c = getchar()) != '\n' && c != EOF) {} // Vide le buffer
                char bio[200];
                scanf(" %[^\n]", bio); // Lire la bio (avec espaces)
                users[userIndex].bio = malloc((strlen(bio) + 1) * sizeof(char));
                strcpy(users[userIndex].bio, bio);
                printf("Press Enter to continue...");
                printf("\n");
                getchar(); 
                getchar();
            } else {
                users[userIndex].bio = NULL;
            }
            printf("\n");
            for(int i=0; i<70; i++){
                printf("-") ;
            }
            printf("\n");
            // Demander l'école à l'utilisateur
            printf("Do you want to add your school? (y/n)\n");
            char addSchoolChoice;
            scanf(" %c", &addSchoolChoice);
            if (addSchoolChoice == 'y' || addSchoolChoice == 'Y') {
                printf("Enter your school:\n");
                char school[50];
                scanf(" %[^\n]", school); // Lire l'école (avec espaces)
                users[userIndex].school = malloc((strlen(school) + 1) * sizeof(char));
                strcpy(users[userIndex].school, school);
            } else {
                users[userIndex].school = NULL;
            }
            printf("\n");
            for(int i=0; i<70; i++){
                printf("-") ;
            }
            printf("\n\n\n");
        }
    }
    // Nettoyage du buffer avant le message de bienvenue
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {} // Vide le buffer
    printf("Welcome %s!\n", users[userIndex].name);
    printf("\n\n");
    printf("Press Enter to continue...");
    getchar(); 
    printf("\n");

    int exit1=0; // Variable de contrôle pour la boucle principale du menu
    while (exit1 != 1) { // Boucle principale du menu tant que l'utilisateur ne choisit pas de quitter

        // Efface l'écran (en affichant 30 lignes vides)
        for(int i = 0; i < 30; i++) {
            printf("\n");
        }

        make_logo(); // Affiche le logo du réseau social
        printf("                      HOME\n");
        printf("\n");

        // Affiche une ligne de séparation
        for(int i = 0; i < 70; i++) {
            printf("*");
        }
        for(int i = 0; i < 3; i++) {
            printf("\n");
        }
        printf("\n");

        // Affiche le menu principal
        printf("what do you want to do?\n");
        printf("\n");
        printf("1. See your friends\n");
        printf("2. Search a Friend\n");
        printf("3. My page\n");
        printf("4. Exit\n");

        for(int i = 0; i < 3; i++) {
            printf("\n");
        }

        for(int i = 0; i < 70; i++) {
            printf("*");
        }
        printf("\n");

        // Demande à l'utilisateur de choisir une option du menu
        printf("Enter the right number:");
        int choice;
        scanf("%d", &choice);
        printf("\n");

        // Si l'utilisateur choisit "1. See your friends"
        if (choice == 1) {
            int exit2 = 0;
            while (exit2 != 1) { // Boucle du sous-menu "My Friends"
                for(int i = 0; i < 30; i++) {
                    printf("\n");
                }
                make_logo();
                printf("                    My Friends\n");
                printf("\n");
                for(int i = 0; i < 70; i++) {
                    printf("*");
                }
                printf("\n");

                // Affiche la liste des amis de l'utilisateur
                printf("Your friends are:\n");
                for (int i = 0; i < userCount; i++) {
                    if (adjacencyMatrix[userIndex][i] != NO_CONNECTION) {
                        printf("%s (Power: %d)\n", users[i].name, adjacencyMatrix[userIndex][i]);
                    }
                }

                printf("\n");
                printf("What do you want to do?\n");
                printf("\n");
                printf("1. See Friends strength\n");
                printf("2. Remove Friend\n");
                printf("3. Modify friendship strength\n");
                printf("4. Exit\n");
                printf("\n");
                printf("\n");

                for(int i = 0; i < 70; i++) {
                    printf("*");
                }
                printf("\n");
                for(int i = 0; i < 3; i++) {
                    printf("\n");
                }
                printf("Enter the right number:");
                int choice2;
                scanf("%d", &choice2);
                printf("\n");

                // Sous-menu : voir la force d'une amitié
                if (choice2 == 1) {
                    for(int i = 0; i < 70; i++) {
                        printf("=");
                    }
                    printf("\n");

                    printf("Quel ami veux-tu voir la force de l'amitié ?\n");
                    char friendName[50];
                    scanf("%s", friendName);
                    int friendIndex = findUserIndex(friendName);
                    if (friendIndex != -1) {
                        printf("Friendship strength with %s: %d\n", friendName, adjacencyMatrix[userIndex][friendIndex]);
                    } else {
                        printf("Friend not found.\n");
                    }
                    printf("%d\n", findFriendshipStrength(users[userIndex].name, friendName));
                    printf("\n");
                    for(int i = 0; i < 70; i++) {
                        printf("=");
                    }
                    printf("\n");

                    printf("Press Enter to continue...");
                    getchar();
                    getchar();

                // Sous-menu : supprimer un ami
                } else if (choice2 == 2) {
                    for(int i = 0; i < 70; i++) {
                        printf("=");
                    }
                    printf("\n");

                    char friendName[50];
                    printf("Enter the name of the friend you want to remove:\n");
                    scanf("%s", friendName);
                    removeFriendship(users[userIndex].name, friendName);
                    printf("Friendship with %s removed.\n", friendName);
                    for(int i = 0; i < 70; i++) {
                        printf("=");
                    }
                    printf("\n");

                    printf("Press Enter to continue...");
                    getchar();
                    getchar();

                // Sous-menu : modifier la force d'une amitié
                } else if (choice2 == 3) {
                    for(int i = 0; i < 70; i++) {
                        printf("=");
                    }
                    printf("\n");
                    char friendName[50];
                    printf("Enter the name of the friend whose friendship strength you want to modify:\n");
                    scanf("%s", friendName);
                    int strength;
                    printf("%d\n", findFriendshipStrength(users[userIndex].name, friendName));
                    printf("Enter the new strength of the friendship:\n");
                    scanf("%d", &strength);
                    modifyFriendship(users[userIndex].name, friendName, strength);
                    printf("Friendship strength with %s modified to %d\n", friendName, strength);

                    for(int i = 0; i < 70; i++) {
                        printf("=");
                    }
                    printf("\n");
                    printf("Press Enter to continue...");
                    getchar();
                    getchar();

                // Sous-menu : quitter le sous-menu "My Friends"
                } else if (choice2 == 4) {
                    printf("Exiting...\n");
                    exit2 = 1;
                } else {
                    printf("Invalid choice.\n");
                }
            }
        }

        else if (choice == 2) {
            int exit2 = 0;
            while (exit2 != 1) { // Boucle du sous-menu "Search a Friend"
                // Efface l'écran
                for(int i = 0; i < 30; i++){
                    printf("\n");
                }
                make_logo();
                printf("                 SEARCH A FRIEND\n");
                printf("\n");
                for(int i = 0; i < 70; i++){
                    printf("*");
                }
                printf("\n");

                // Affiche la liste de tous les utilisateurs et la distance de relation
                printf("Voici la liste des personnes du réseau social:\n");
                for (int i = 0; i < userCount; i++) {
                    int paths[MAX_USERS];
                    printf("Nom : %s, Distance de la relation, %d\n", users[i].name, findShortestPath(name, users[i].name, paths));
                }

                printf("\n");
                printf("Que voulez-vous faire ?\n");
                printf("1. Filtre\n");
                printf("2. Add Friend\n");
                printf("3. Remove Friend\n");
                printf("4. Trouver des amis potentiels\n");
                printf("5. Exit\n");

                for(int i = 0; i < 70; i++){
                    printf("*");
                }
                printf("\n");
                for(int i = 0; i < 3; i++){
                    printf("\n");
                }
                printf("Enter the right number: ");
                int choice2;
                scanf("%d", &choice2);
                printf("\n");

                // Sous-menu : Filtres de recherche
                if (choice2 == 1) {
                    for(int i = 0; i < 70; i++){
                        printf("=");
                    }
                    printf("\n");

                    printf("Filtres :\n");
                    printf("1. Friends with strength > 5\n");
                    printf("2. Friends with strength <= 5\n");
                    printf("3. Stranger with distance <3\n");
                    printf("4. Stranger with distance <5\n");
                    printf("5. By Name\n");
                    printf("\n");

                    for(int i = 0; i < 70; i++){
                        printf("=");
                    }
                    printf("\n");
                    for(int i = 0; i < 3; i++){
                        printf("\n");
                    }
                    printf("Enter the right number: ");
                    int choice3;
                    scanf("%d", &choice3);
                    printf("\n");

                    // Filtre : amis avec force > 5
                    if(choice3 == 1) {
                        for(int i = 0; i < 70; i++){
                            printf("=");
                        }
                        printf("\n");
                        printf("Friends with strength > 5:\n");
                        for (int i = 0; i < userCount; i++) {
                            if (findFriendshipStrength(users[userIndex].name, users[i].name) > 5) {
                                printf("Name : %s, Strenght: %d;\n", users[i].name, findFriendshipStrength(users[userIndex].name, users[i].name));
                            }
                        }
                        for(int i = 0; i < 70; i++){
                            printf("=");
                        }
                        printf("\n");
                        printf("Press Enter to continue...");
                        getchar();
                        getchar();

                    // Filtre : amis avec force <= 5
                    } else if(choice3 == 2) {
                        for(int i = 0; i < 70; i++){
                            printf("=");
                        }
                        printf("\n");
                        printf("Friends with strength <= 5:\n");
                        for (int i = 0; i < userCount; i++) {
                            if (findFriendshipStrength(users[userIndex].name, users[i].name) <= 5) {
                                printf("Name : %s, Strenght: %d;\n", users[i].name, findFriendshipStrength(users[userIndex].name, users[i].name));
                            }
                        }
                        for(int i = 0; i < 70; i++){
                            printf("=");
                        }
                        printf("\n");
                        printf("Press Enter to continue...");
                        getchar();
                        getchar();

                    // Filtre : inconnus avec distance < 3
                    } else if (choice3 == 3) {
                        for(int i = 0; i < 70; i++){
                            printf("=");
                        }
                        printf("\n");
                        printf("Strangers with distance < 3:\n");
                        for (int i = 0; i < userCount; i++) {
                            int paths2[MAX_USERS];
                            if (findShortestPath(users[userIndex].name, users[i].name, paths2) < 3) {
                                printf("%s\n", users[i].name);
                            }
                        }
                        for(int i = 0; i < 70; i++){
                            printf("=");
                        }
                        printf("\n");
                        printf("Press Enter to continue...");
                        getchar();
                        getchar();

                    // Filtre : inconnus avec distance < 5
                    } else if (choice3 == 4) {
                        for(int i = 0; i < 70; i++){
                            printf("=");
                        }
                        printf("\n");
                        printf("Strangers with distance < 5:\n");
                        for (int i = 0; i < userCount; i++) {
                            int paths2[MAX_USERS];
                            if (findShortestPath(users[userIndex].name, users[i].name, paths2) < 5) {
                                printf("%s\n", users[i].name);
                            }
                        }
                        for(int i = 0; i < 70; i++){
                            printf("=");
                        }
                        printf("\n");
                        printf("Press Enter to continue...");
                        getchar();
                        getchar();

                    // Filtre : recherche par nom
                    } else if (choice3 == 5) {
                        for(int i = 0; i < 70; i++){
                            printf("=");
                        }
                        printf("\n");
                        char name[50];
                        printf("Enter the name of the friend you want to find:\n");
                        scanf("%s", name);
                        int index2 = findUserIndex(name);
                        if (index2 != -1) {
                            printf("Name : %s, Strenght: %d;\n", users[index2].name, findFriendshipStrength(users[userIndex].name, users[index2].name));
                        } else {
                            printf("Friend not found.\n");
                        }
                        for(int i = 0; i < 70; i++){
                            printf("=");
                        }
                        printf("\n");
                        printf("Press Enter to continue...");
                        getchar();
                        getchar();
                    } else {
                        printf("Invalid choice.\n");
                    }

                // Sous-menu : Ajouter un ami
                } else if (choice2 == 2) {
                    for(int i = 0; i < 70; i++){
                        printf("=");
                    }
                    printf("\n");
                    printf("Enter the name of the friend you want to add: \n");
                    char friendName[50];
                    scanf("%s", friendName);
                    int friendIndex = findUserIndex(friendName);

                    if (adjacencyMatrix[userIndex][friendIndex] != NO_CONNECTION) {
                        printf("Friend already exists.\n");
                    } else {
                        printf("Enter the strength of the friendship:\n");
                        int strength;
                        scanf("%d", &strength);
                        addFriendship(users[userIndex].name, friendName, strength);
                        printf("Friendship with %s added.\n", friendName);
                    }
                    for(int i = 0; i < 70; i++){
                        printf("=");
                    }
                    printf("\n");
                    printf("Press Enter to continue...");
                    getchar();
                    getchar();

                // Sous-menu : Supprimer un utilisateur
                } else if (choice2 == 3) {
                    for(int i = 0; i < 70; i++){
                        printf("=");
                    }
                    printf("\n");
                    char friendName[50];
                    printf("Enter the name of the friend you want to remove:\n");
                    scanf("%s", friendName);
                    removeUser(friendName);
                    printf("Friendship with %s removed.\n", friendName);
                    for(int i = 0; i < 70; i++){
                        printf("=");
                    }
                    printf("\n");
                    printf("Press Enter to continue...");
                    getchar();
                    getchar();

                // Sous-menu : Trouver des amis potentiels
                } else if (choice2 == 4) {
                    for(int i = 0; i < 70; i++){
                        printf("=");
                    }
                    printf("\n");
                    int friends[MAX_USERS];
                    int count = 0;
                    findPotentialFriends(users[userIndex].name, 2, friends, &count);
                    if (count > 0) {
                        printf("Potential friends:\n");
                        for (int i = 0; i < count; i++) {
                            printf("%s, Bio: %s\n", users[friends[i]].name, users[friends[i]].bio ? users[friends[i]].bio : "No bio available");
                        }
                    } else {
                        printf("No potential friends found.\n");
                    }
                    for(int i = 0; i < 70; i++){
                        printf("=");
                    }
                    printf("\n");
                    printf("Press Enter to continue...");
                    getchar();
                    getchar();

                // Sous-menu : Quitter le sous-menu "Search a Friend"
                } else if (choice2 == 5) {
                    printf("Exiting...\n");
                    exit2 = 1;
                } else {
                    printf("Invalid choice.\n");
                }
            }
        }

        else if (choice == 3) {
            int exit2 = 0;
            while (exit2 != 1) { // Boucle du sous-menu "MY PAGE"
                // Efface l'écran (affiche 30 lignes vides)
                for(int i = 0; i < 30; i++){
                    printf("\n") ;
                }
                make_logo(); // Affiche le logo
                printf("                     MY PAGE\n");
                printf("\n");
                for(int i = 0; i < 70; i++){
                    printf("*") ;
                }
                printf("\n");

                // Affiche les informations de l'utilisateur connecté
                int friends1[MAX_USERS];
                int count1 = 0;
                findPotentialFriends(users[userIndex].name, 1, friends1, &count1); // Compte les amis directs
                printf("Name: %s               Friends: %d          Strength: %f\n", users[userIndex].name, count1, findAverageFriendshipStrenght(users[userIndex].name));
                printf("School: %s\n", users[userIndex].school ? users[userIndex].school : "No school information available");
                printf("Bio: %s\n", users[userIndex].bio ? users[userIndex].bio : "No bio information available");
                printf("\n");
                printf("\n");

                // Affiche le menu de modification du profil
                printf("1.Modifier mon Pseudo\n");
                printf("2.Modifier la BIO:\n");
                printf("3.Modifier l'école:\n");
                printf("4.Exit\n");
                
                for(int i = 0; i < 70; i++){
                    printf("*") ;
                }
                printf("\n");
                for(int i = 0; i < 3; i++){
                    printf("\n") ;
                }

                // Demande à l'utilisateur de choisir une action sur son profil
                printf("Enter the right number:");
                int choice2;
                scanf("%d", &choice2);
                printf("\n");

                // Modifier le pseudo
                if (choice2 == 1) {
                    for(int i = 0; i < 70; i++){
                        printf("=") ;
                    }
                    printf("\n");
                    char newName[50];
                    printf("Enter your new name:\n");
                    scanf("%s", newName);
                    strcpy(users[userIndex].name, newName); // Met à jour le nom
                    printf("Name changed to %s\n", users[userIndex].name);
                    for(int i = 0; i < 70; i++){
                        printf("=") ;
                    }
                    printf("\n");
                    printf("Press Enter to continue...");
                    getchar();
                    getchar(); 

                // Modifier la bio
                } else if (choice2 == 2) {
                    for(int i = 0; i < 70; i++){
                        printf("=") ;
                    }
                    printf("\n");
                    int c;
                    while ((c = getchar()) != '\n' && c != EOF) {} // Vide le buffer
                    char newBio[200];
                    printf("Enter your new bio:\n");
                    scanf(" %[^\n]", newBio); // Lecture de la nouvelle bio (avec espaces)
                    if (users[userIndex].bio) {
                        free(users[userIndex].bio); // Libère l'ancienne bio si elle existe
                    }
                    users[userIndex].bio = malloc((strlen(newBio) + 1)*sizeof(char));
                    strcpy(users[userIndex].bio, newBio); // Met à jour la bio
                    printf("Bio updated.\n");
                    for(int i = 0; i < 70; i++){
                        printf("=") ;
                    }
                    printf("\n");
                    printf("Press Enter to continue...");
                    getchar();
                    getchar();

                // Modifier l'école
                } else if (choice2 == 3) {
                    for(int i = 0; i < 70; i++){
                        printf("=") ;
                    }
                    printf("\n");
                    int c;
                    while ((c = getchar()) != '\n' && c != EOF) {} // Vide le buffer
                    char newSchool[50];
                    printf("Enter your new school:\n");
                    scanf(" %[^\n]", newSchool); // Lecture de la nouvelle école (avec espaces)
                    if (users[userIndex].school) {
                        free(users[userIndex].school); // Libère l'ancienne école si elle existe
                    }
                    users[userIndex].school = malloc((strlen(newSchool) + 1)*sizeof(char));
                    strcpy(users[userIndex].school, newSchool); // Met à jour l'école
                    printf("School updated.\n");
                    for(int i = 0; i < 70; i++){
                        printf("=") ;
                    }
                    printf("\n");
                    printf("Press Enter to continue...");
                    getchar();
                    getchar();

                // Quitter le sous-menu "MY PAGE"
                } else if (choice2 == 4) {
                    printf("Exiting...\n");
                    exit2 = 1;
                } else {
                    printf("Invalid choice.\n");
                }
            }
        }

        else if (choice == 4) {
            // Affiche quelques lignes vides pour espacer l'affichage
            for(int i=0; i<10; i++){
                printf("\n") ;
            }
            make_logo(); // Affiche le logo du réseau social
            printf(" Are you sure you want to exit? :( (y/n)\n"); // Demande confirmation pour quitter
            char confirm;
            scanf(" %c", &confirm);
            if (confirm == 'y' || confirm == 'Y') {
                // Si l'utilisateur confirme, on quitte la boucle principale
                printf("Goodbye!\n");
                exit1 = 1;
            } else {
                // Sinon, on continue le programme
                printf("Continuing...\n");
            }

        } else {
            // Si l'utilisateur entre un choix invalide
            printf("Invalid choice.\n");
        }
        // Save updates to a new file
    }
    // Sauvegarde les modifications dans le fichier à la fin du programme
    saveToFile("social_network_updated.txt"); // Sauvegarde tous les utilisateurs et amitiés dans le fichier
    printf("Saving updates into file : social_network_updated.txt\n"); // Message de confirmation de sauvegarde
    printf("Exiting the social network...\n"); // Message de sortie du programme
    printf("\n");
    return 0 ; // Fin du programme
}
