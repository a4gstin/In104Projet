#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

// Declare functions from p1.c that we'll use
int findUserIndex(const char* name);
void initializeGraph();
int findShortestPath(int start, int end, int* path);
void printPath(int* path, int length);

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

    return 0;
}