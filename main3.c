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

    int NB_USERS;
    fscanf(file, "%d", &NB_USERS);
    for (int i = 0; i < NB_USERS && i < MAX_USERS; i++) {
        fscanf(file, "%49s", users[i].name);  // Limit input to prevent buffer overflow
        users[i].index = i;
        userCount++;
    }

    char name1[50], name2[50];
    int strength;
    while (fscanf(file, "%49s %49s %d", name1, name2, &strength) == 3) {
        int idx1 = findUserIndex(name1);
        int idx2 = findUserIndex(name2);
        if (idx1 != -1 && idx2 != -1) {
            adjacencyMatrix[idx1][idx2] = strength;
            adjacencyMatrix[idx2][idx1] = strength;
        }
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