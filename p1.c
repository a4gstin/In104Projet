#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <stdbool.h>

#define MAX_USERS 100
#define NO_CONNECTION 0

typedef struct {
    char name[50];
    int index;
} User;

// Global variables defined HERE ONLY
User users[MAX_USERS];
int adjacencyMatrix[MAX_USERS][MAX_USERS];
int userCount = 0;

// Helper function implementations
int findUserIndex(const char* name) {
    for (int i = 0; i < userCount; i++) {
        if (strcmp(users[i].name, name) == 0) {
            return i;
        }
    }
    return -1;
}

void printPath(int* path, int length) {
    for (int i = 0; i < length; i++) {
        printf("%s", users[path[i]].name);
        if (i < length - 1) {
            printf(" -> ");
        }
    }
    printf("\n");
}

void initializeGraph() {
    for (int i = 0; i < MAX_USERS; i++) {
        for (int j = 0; j < i; j++) {
            adjacencyMatrix[i][j] = NO_CONNECTION;
            adjacencyMatrix[j][i] = NO_CONNECTION;
        }
    }
}

void addUserWithFriendships(const char* name, int friendCount, const char** friendNames, const int* strengths) {
    if (userCount >= MAX_USERS) return;
    
    strcpy(users[userCount].name, name);
    users[userCount].index = userCount;
    int currentUserIndex = userCount++;
    
    for (int i = 0; i < friendCount; i++) {
        int friendIndex = findUserIndex(friendNames[i]);
        if (friendIndex != -1) {
            adjacencyMatrix[currentUserIndex][friendIndex] = strengths[i];
            adjacencyMatrix[friendIndex][currentUserIndex] = strengths[i];
        }
    }
}

// 3. Implement function to remove users
void removeUser(const char* name) {
    int index = findUserIndex(name);
    if (index == -1) {
        printf("User not found.\n");
        return;
    }
    
    // Remove from adjacency matrix
    for (int i = 0; i < userCount; i++) {
        adjacencyMatrix[i][index] = NO_CONNECTION;
        adjacencyMatrix[index][i] = NO_CONNECTION;
    }
    
    // Shift users array
    for (int i = index; i < userCount - 1; i++) {
        users[i] = users[i + 1];
        users[i].index = i;
    }
    
    // Shift adjacency matrix
    for (int i = 0; i < userCount; i++) {
        for (int j = index; j < userCount - 1; j++) {
            adjacencyMatrix[i][j] = adjacencyMatrix[i][j + 1];
        }
    }
    
    for (int i = index; i < userCount - 1; i++) {
        for (int j = 0; j < userCount; j++) {
            adjacencyMatrix[i][j] = adjacencyMatrix[i + 1][j];
        }
    }
    
    userCount--;
}

// 4. Implement function to modify friendship strength
void modifyFriendship(const char* name1, const char* name2, int strength) {
    int index1 = findUserIndex(name1);
    int index2 = findUserIndex(name2);
    
    if (index1 == -1 || index2 == -1) {
        printf("One or both users not found.\n");
        return;
    }
    
    adjacencyMatrix[index1][index2] = strength;
    adjacencyMatrix[index2][index1] = strength;
}

// 5. Implement function to find the shortest connection path between two users (BFS)
int findShortestPath(int start, int end, int* path) {
    if (start == end) {
        path[0] = start;
        return 1;
    }
    
    int visited[MAX_USERS] = {0};
    int parent[MAX_USERS];
    int queue[MAX_USERS];
    int front = 0, rear = 0;
    
    for (int i = 0; i < userCount; i++) {
        parent[i] = -1;
    }
    
    visited[start] = 1;
    queue[rear++] = start;
    
    while (front < rear) {
        int current = queue[front++];
        
        for (int i = 0; i < userCount; i++) {
            if (adjacencyMatrix[current][i] != NO_CONNECTION && !visited[i]) {
                parent[i] = current;
                visited[i] = 1;
                queue[rear++] = i;
                
                if (i == end) {
                    
                    int pathLength = 0;
                    int temp = end;
                    while (temp != -1) {
                        pathLength++;
                        temp = parent[temp];
                    }
                    
                    temp = end;
                    for (int j = pathLength - 1; j >= 0; j--) {
                        path[j] = temp;
                        temp = parent[temp];
                    }
                    
                    return pathLength;
                }
            }
        }
    }
    
    return 0; // No path found
}
