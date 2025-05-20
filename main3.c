#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Import the file p1.h where we declare the functions coded in p1.c
#include "p1.h"

// Forward declarations and constants
#define MAX_USERS 100
#define NO_CONNECTION 0
typedef struct {
    char name[50];
    int index;
} User;

// Declare global variables as extern
extern User users[MAX_USERS];
extern int adjacencyMatrix[MAX_USERS][MAX_USERS];
extern int userCount;

// Function which is filling the list users and the adjacencyMatrix with the .txt 
void readFromFile(const char *filename) {
    
    FILE *file = fopen(filename, "r");
    if (!file) {
        printf("Error opening file!\n");
        return;
    }
    printf("Reading users from file...\n");

    // Add users
    int NB_USERS ;
    fscanf(file, "%d", &NB_USERS) ;
    userCount = NB_USERS ;
    for (int i=0; i<NB_USERS; i++){
        char name[20];
        fscanf(file, "%s", name) ;
        User add_user ;
        
        int len = strlen(name) ;
        for (int j=0 ; j<len; j++){
            add_user.name[j] = name[j] ;
        }
        users[i] = add_user ;
    }

    // Add user's friendship in the matrix
    int NB_USERS_FRIENDSHIP ;
    fscanf(file, "%d", &NB_USERS_FRIENDSHIP) ;
    for (int i=0; i<NB_USERS_FRIENDSHIP; i++){
        int friend1 ;
        int friend2 ;
        int friendship_strenght ;
        fscanf(file, "%d %d %d", &friend1, &friend2, &friendship_strenght) ;
        adjacencyMatrix[friend1][friend2] = friendship_strenght ;
        adjacencyMatrix[friend2][friend1] = friendship_strenght ;
    }

    fclose(file);
}

int main() {
    initializeGraph();
    readFromFile("social_network.txt");

    printf("connecter vous à votre réseau social \n");
    printf("Entrez votre nom user:\n");
    char name[50];
    scanf("%s", name);
    int userIndex = findUserIndex(name);
    if (userIndex == -1) {
        printf("User not found.\n");
        return 1;
    }
    printf("Welcome %s!\n", users[userIndex].name);
    printf("\n");
    printf("\n");
    printf("what do you want to do?\n");
    printf("\n");
    printf("1. See your friends\n");
    printf("2. Add a friend\n");
    printf("3. Remove a friend\n");
    printf("4. Modify friendship strength\n");

    printf("Enter the right number:\n");
    int choice;
    scanf("%d", &choice);
    int exit1=0;
    while (exit1 !=1){
        if (choice == 1) {
            int exit2=0;
            while (exit2 !=1){
                for(int i=0; i<70; i++){
                    printf("*") ;
                }
                printf("\n");


                printf("Your friends are:\n");
                for (int i = 0; i < userCount; i++) {
                    if (adjacencyMatrix[userIndex][i] != NO_CONNECTION) {
                        printf("%s (Power: %d)\n", users[i].name, adjacencyMatrix[userIndex][i]);
                    }
                }


                printf("1. See Friends strength\n");
                printf("2. Remove Friend\n");
                printf("3. Modify friendship strength\n");
                printf("4. Exit\n");
                printf("\n");
                printf("Enter the right number:\n");

                for(int i=0; i<70; i++){
                    printf("*") ;
                }
                printf("\n");

                int choice2;
                scanf("%d", &choice2);

                if (choice2 == 1) {

                    for(int i=0; i<70; i++){
                    printf("=\n") ;
                    }

                    printf("Quel ami veux-tu voir la force de l'amitié ?\n");
                    char friendName[50];
                    scanf("%s", friendName);
                    int friendIndex = findUserIndex(friendName);
                    if (friendIndex != -1) {
                        printf("Friendship strength with %s: %d\n", friendName, adjacencyMatrix[userIndex][friendIndex]);
                    } else {
                        printf("Friend not found.\n");
                    }
                    printf("%d\n",findfriendshipStrength(users[userIndex].name, friendName));
                    printd("\n");
                    for(int i=0; i<70; i++){
                    printf("=\n") ;
                    }


                } else if (choice2 == 2) {
                    for(int i=0; i<70; i++){
                    printf("=\n") ;
                    }
                    char friendName[50];
                    printf("Enter the name of the friend you want to remove:\n");
                    scanf("%s", friendName);
                    removeFriendship(users[userIndex].name, friendName);
                    printf("Friendship with %s removed.\n", friendName);
                    for(int i=0; i<70; i++){
                    printf("=\n") ;
                    }

                } else if (choice2 == 3) {
                    for(int i=0; i<70; i++){
                    printf("=\n") ;
                    }
                    char friendName[50];
                    printf("Enter the name of the friend whose friendship strength you want to modify:\n");
                    scanf("%s", friendName);
                    int strength;
                    printf("%d\n",findfriendshipStrength(users[userIndex].name, friendName));
                    printf("Enter the new strength of the friendship:\n");
                    scanf("%d", &strength);
                    modifyFriendship(users[userIndex].name, friendName, strength);
                    printf("Friendship strength with %s modified to %d\n", friendName, strength);

                    for(int i=0; i<70; i++){
                    printf("=\n") ;
                    }

                } else if (choice2 == 4) {
                    printf("Exiting...\n");
                    exit2 = 1;
                } else {
                    printf("Invalid choice.\n");
                }
            }
        }

        else if (choice == 2) {
            int exit2=0;
            while(exit2 !=1){
                for(int i=0; i<70; i++){
                    printf("*") ;
                    }
                printf("\n");

                printf("Voici la liste des personnes du réseau social:\n");
                for (int i = 0; i < userCount; i++) {
                    printf("Nom : %s, distance de la relation %d\n", users[i].name, findShortestPath(userIndex, i, NULL));
                }

                printf("1. Filtre\n");
                printf("2. Add Friend\n");
                printf("3. Remove Friend\n");
                printf("4. Exit\n");
                printf("\n");

                for(int i=0; i<70; i++){
                    printf("*") ;
                    }
                printf("\n");

                int choice2;
                scanf("%d", &choice2);

                if (choice2 ==1){
                    for(int i=0; i<70; i++){
                    printf("=") ;
                    }
                    printf("\n");

                    printf("Filtres :\n");
                    printf("1. Friends with strength > 5\n");
                    printf("2. Friends with strength <= 5\n");
                    printf("3. Stranger with distance <3\n");
                    printf("4. Stranger with distance <5\n");
                    printf("5. By Name\n");
                    printf("\n");

                    for(int i=0; i<70; i++){
                    printf("=") ;
                    }
                    printf("\n");

                    int choice3;
                    scanf("%d", &choice3);

                    if(choice3 == 1) {
                        for(int i=0; i<70; i++){
                            printf("*") ;
                            }
                        printf("\n");
                        printf("Friends with strength > 5:\n");
                        for (int i = 0; i < userCount; i++) {
                            if (findFriendshipStrength(users[userIndex].name, users[i].name) > 5) {
                                printf("Name : %s, Strenght: %d;\n", users[i].name, findFriendshipStrength(users[userIndex].name, users[i].name));
                            }
                            for(int i=0; i<70; i++){
                                printf("*") ;
                                }
                            printf("\n");
                        }
                    }
                    if(choice3 == 2) {
                        for(int i=0; i<70; i++){
                            printf("*") ;
                            }
                        printf("\n");
                        printf("Friends with strength <= 5:\n");
                        for (int i = 0; i < userCount; i++) {
                            if (findFriendshipStrength(users[userIndex].name, users[i].name) <= 5) {
                                printf("Name : %s, Strenght: %d;\n", users[i].name, findFriendshipStrength(users[userIndex].name, users[i].name));
                            }
                            for(int i=0; i<70; i++){
                                printf("*") ;
                                }
                            printf("\n");
                        }
                    } else if (choice3 == 3) {
                        for(int i=0; i<70; i++){
                            printf("*") ;
                            }
                        printf("\n");
                        printf("Strangers with distance < 3:\n");
                        for (int i = 0; i < userCount; i++) {
                            if (dijkstraWeakestPath(users[userIndex].name, users[i].name) < 3) {
                                printf("%s\n", users[i].name);
                            }
                            for(int i=0; i<70; i++){
                                printf("*") ;
                                }
                            printf("\n");
                        }
                    } else if (choice3 == 4) {
                        for(int i=0; i<70; i++){
                            printf("*") ;
                            }
                        printf("\n");
                        printf("Strangers with distance < 5:\n");
                        for (int i = 0; i < userCount; i++) {
                            if (dijkstraWeakestPath(users[userIndex].name, users[i].name) < 5) {
                                printf("%s\n", users[i].name);
                            }
                            for(int i=0; i<70; i++){
                                printf("*") ;
                                }
                            printf("\n");
                        }
                    } else if (choice3 == 5) {
                        for(int i=0; i<70; i++){
                            printf("*") ;
                            }
                        printf("\n");
                        char name[50];
                        printf("Enter the name of the friend you want to find:\n");
                        scanf("%s", name);
                        int index = findUserIndex(name);
                        if (index != -1) {
                            printf("Friend found: %s\n", users[index].name);
                        } else {
                            printf("Friend not found.\n");
                        }
                        for(int i=0; i<70; i++){
                            printf("*") ;
                            }
                        printf("\n");
                    }else {
                        printf("Invalid choice.\n");
                    }
                } else if (choice2 == 2) {
                    for(int i=0; i<70; i++){
                    printf("=") ;
                    }
                    printf("\n");
                    printf("Enter the name of the friend you want to add:\n");
                    char friendName[50];
                    scanf("%s", friendName);
                    int friendIndex = findUserIndex(friendName);
                    int* friends = NULL;
                    int count = 0;
                    findPotentialFriends(users[userIndex].name, friendName, &friends, &count);
                    if ( &count == 1) {
                        printf("Friend already exists.\n");

                    } else {
                        printf("Enter the strength of the friendship:\n");
                        int strength;
                        scanf("%d", &strength);
                        addFriendship(users[userIndex].name, friendName, strength);
                        printf("Friendship with %s added.\n", friendName);
                    }
                    for(int i=0; i<70; i++){
                    printf("=") ;
                    }
                    printf("\n");

                } else if (choice2 == 3){
                    char friendName[50];
                    printf("Enter the name of the friend you want to remove:\n");
                    scanf("%s", friendName);
                    removeUser(friendName);
                }
                else if (choice2 == 4) {
                    printf("Exiting...\n");
                    exit2 = 1;
                } else {
                    printf("Invalid choice.\n");
                }




        } else if (choice == 3) {

        } else if (choice == 4) {
            char friendName[50];
            int strength;
            printf("Enter the name of the friend whose friendship strength you want to modify:\n");
            scanf("%s", friendName);
            printf("Enter the new strength of the friendship:\n");
            scanf("%d", &strength);
            modifyFriendship(users[userIndex].name, friendName, strength);
        } else {
            printf("Invalid choice.\n");
    }



    int path[MAX_USERS];

    int length = findShortestPath(0, 2, path);
    if (length > 0) {
        printf("Shortest path: ");
        printPath(path, length);
    } else {
        printf("No path found.\n");
    }

    int path_avant[MAX_USERS];
    int avant = findShortestPath(0, 5, path_avant);
    if (avant > 0) {
        printf("Shortest path (lenght = %d): ", avant);
        printPath(path_avant, avant);
    } else {
        printf("No path found.\n");
    }
    removeUser(users[2].name) ;
    int path_apres[MAX_USERS];
    int apres = findShortestPath(0, 5, path_apres);
    if (apres > 0) {
        printf("Shortest path (lenght = %d): ", apres);
        printPath(path_apres, apres);
    } else {
        printf("No path found.\n");
    }

    return 0;
}
