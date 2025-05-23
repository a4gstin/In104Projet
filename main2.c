#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_USERS 100
//#define NB_USERS

// Structure to hold user data
typedef struct {
    char name[50];
} User;

// Global variables
User users[MAX_USERS];
int adjacencyMatrix[MAX_USERS][MAX_USERS]; // Friendship strength
int numUsers = 0;

// Function to initialize adjacency matrix
void initializeAdjacencyMatrix() {
    for (int i = 0; i < MAX_USERS; i++) {
        for (int j = 0; j < MAX_USERS; j++) {
            adjacencyMatrix[i][j] = 0;
        }
    }
}

// Function to read users and their friendships from a file
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

// TODO: Continue the implementation...

int main() {
    initializeAdjacencyMatrix();
    readFromFile("social_network.txt");
	
    // TODO: Continue the implementation...


    return 0;
}
