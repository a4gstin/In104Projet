#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Import the file p1.h where we declare the functions coded in p1.c
#include "p1.h"

// Forward declarations and constants
#define MAX_USERS 100
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

    // Example usage
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
