#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <stdbool.h>

#include "p1.h"

#define MAX_USERS 100
#define NO_CONNECTION 0

typedef struct {
    char name[50];
    int index;
    char* bio;
    char* school ;
} User;

// Global variables defined HERE ONLY
User users[MAX_USERS];
int adjacencyMatrix[MAX_USERS][MAX_USERS];
int userCount = 0;



// General function and simple functions we needed

// A. Implement function who find the associate index (in the matrix) of a user
int findUserIndex(const char* name) {
    for (int i = 0; i < userCount; i++) {
        if (strcmp(users[i].name, name) == 0) {
            return i;
        }
    }
    return -1;
}

// B. Implement function that print a given path
void printPath(int* path, int length) {
    for (int i = 0; i < length; i++) {
        printf("%s", users[path[i]].name);
        if (i < length - 1) {
            printf(" -> ");
        }
    }
    printf("\n");
}

// C. Implement function to return the strength of a friendship between two users
int findFriendshipStrength (const char* name1, const char* name2) {
    int index1 = findUserIndex(name1);
    int index2 = findUserIndex(name2);

    if (index1 == -1 || index2 == -1) {
        printf("One or both users not found.\n");
        return ;
    }

    return adjacencyMatrix[index1][index2] ;
}

// D. Implement function to remove a friendship betwenn two users
void removeFriendship (const char* user, const char* friend) {
    int userIndex = findUserIndex(user);
    int friendIndex = findUserIndex(friend);

    if (userIndex == -1 || friendIndex == -1) {
        printf("One or both users not found.\n");
        return ;
    }

    adjacencyMatrix[userIndex][friendIndex] = NO_CONNECTION ;
    adjacencyMatrix[friendIndex][userIndex] = NO_CONNECTION ;
}

// E. Implement function to add a friendship with a user already existing
void addFriendship (const char* user, const char* friend, int strength) {
    int userIndex = findUserIndex(user);
    int friendIndex = findUserIndex(friend);

    if (userIndex == -1 || friendIndex == -1) {
        printf("One or both users not found.\n");
        return ;
    }

    adjacencyMatrix[userIndex][friendIndex] = strength ;
    adjacencyMatrix[friendIndex][userIndex] = strength ;
}

// F. Implement function to find the average strenght of the freindship of one people
float findAverageFriendshipStrenght(const char* name) {

    float res ;
    int friendCount = 0 ;
    int index = findUserIndex(name);

    for (int i=0; i<userCount; i++) { // the maximum is userCount and not Max_USERS to be more effective 
        res += adjacencyMatrix[i][index] ;
        ++ friendCount ;
    }

    if (friendCount == 0) {
        return 0 ;
        printf("triste, tu n'as pas d'ami") ;
    }
    return res/friendCount ;
}



// 1. Implement function to initialize the Adjacency Matrix for the Graph
void initializeGraph() {
    for (int i = 0; i < MAX_USERS; i++) {
        for (int j = 0; j < i; j++) {
            adjacencyMatrix[i][j] = NO_CONNECTION;
            adjacencyMatrix[j][i] = NO_CONNECTION;
        }
    }
}



// 2. Implement function to add a new user in the social network with his friendship data
void addUserWithFriendships(const char* name, int friendCount, const char** friendNames, const int* strengths) {
    if (userCount >= MAX_USERS) { return ; } // halting case
    
    // Add this user in the array "users"
    strcpy(users[userCount].name, name);
    users[userCount].index = userCount;
    int currentUserIndex = userCount++;
    
    // Add this user in the adjacencyMatrix with the informations on his friends
    for (int i = 0; i < friendCount; i++) {
        int friendIndex = findUserIndex(friendNames[i]);
        if (friendIndex != -1) {
            adjacencyMatrix[currentUserIndex][friendIndex] = strengths[i];
            adjacencyMatrix[friendIndex][currentUserIndex] = strengths[i];
        }
    }
}



//3. Implement function to remove users
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
    
    // Remove the user from the array and modify the rest of the array
    for (int i = index; i < userCount - 1; i++) {
        users[i] = users[i + 1]; 
        users[i].index = i;
    }
    
    // Modify the adjacency matrix (changing the size)
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



// 4. Implement function to modify the strength of a friendship
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



// 5. Implement function to find and give the shortest connection (in terms of numbers of friends betwenn name1 and name2) path between two users (BFS)
int findShortestPath(const char* name1, const char* name2, int* path) {

    int start = findUserIndex(name1);
    int end = findUserIndex(name2);

    if (start == end) { return -1; } // halting case : there is no path for just one person
    
    // initialize the different array we are using to search the path
    int visited[MAX_USERS] = {0};
    int parent[MAX_USERS];
    int queue[MAX_USERS];
    int front = 0, rear = 0;
    
    // initialize the array parent at -1
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
    
    return -1; // No path found
}



// 6. Implement function to find all potential friends at a given level (BFS)
void findPotentialFriends(const char* name, int level, int* friends, int* count) {
    if (level < 1) {
        *count = 0;
        return;
    }

    int userIndex = findUserIndex(name);

    int visited[MAX_USERS] = {0};
    int distance[MAX_USERS] = {0};
    int queue[MAX_USERS];
    int front = 0, rear = 0;
    
    visited[userIndex] = 1;
    queue[rear++] = userIndex;
    
    *count = 0;
    
    while (front < rear) {
        int current = queue[front++];
        
        for (int i = 0; i < userCount; i++) {
            if (adjacencyMatrix[current][i] != NO_CONNECTION && !visited[i]) {
                distance[i] = distance[current] + 1;
                visited[i] = 1;
                queue[rear++] = i;
                
                if (distance[i] == level) {
                    friends[(*count)++] = i;
                }
            }
        }
    }
}



// 7. Implement function to explore all possible friendships from a given user (DFS)
void exploreAllFriendships(const char* name, int* visited) {
    int userIndex = findUserIndex(name);
    visited[userIndex] = 1;
    printf("%s ", users[userIndex].name);
    
    for (int i = 0; i < userCount; i++) {
        if (adjacencyMatrix[userIndex][i] != NO_CONNECTION && !visited[i]) {
            exploreAllFriendships(i, visited);
        }
    }
}



// 8. Implement function to explore if there is a potential path between two users
bool hasPath(const char* name1, const char* name2) {

    int start = findUserIndex(name1);
    int end = findUserIndex(name2);
    
    if (start == end) { return true; }
    
    int visited[MAX_USERS] = {0};
    int queue[MAX_USERS];
    int front = 0, rear = 0;
    
    visited[start] = 1;
    queue[rear++] = start;
    
    while (front < rear) {
        int current = queue[front++];
        
        for (int i = 0; i < userCount; i++) {
            if (adjacencyMatrix[current][i] != NO_CONNECTION && !visited[i]) {
                if (i == end) { return true; }
                visited[i] = 1;
                queue[rear++] = i;
            }
        }
    }
    
    return false;
}



// 9. Implement Dijkstra's algorithm to find the weakest path of friendships between two users
void dijkstraWeakestPath(const char* name1, const char* name2) {
    int start = findUserIndex(name1);
    int end = findUserIndex(name2);

    int dist[MAX_USERS];
    int prev[MAX_USERS];
    bool visited[MAX_USERS] = {false};
    
    for (int i = 0; i < userCount; i++) {
        dist[i] = INT_MAX;
        prev[i] = -1;
    }
    dist[start] = 0;
    
    for (int count = 0; count < userCount - 1; count++) {
        int minDist = INT_MAX;
        int u = -1;
        
        for (int v = 0; v < userCount; v++) {
            if (!visited[v] && dist[v] < minDist) {
                minDist = dist[v];
                u = v;
            }
        }
        
        if (u == -1) break;
        visited[u] = true;
        
        for (int v = 0; v < userCount; v++) {
            if (!visited[v] && adjacencyMatrix[u][v] != NO_CONNECTION) {
                int alt = dist[u] + adjacencyMatrix[u][v];
                if (alt < dist[v]) {
                    dist[v] = alt;
                    prev[v] = u;
                }
            }
        }
    }
    
    if (dist[end] == INT_MAX) {
        printf("No path exists between %s and %s\n", users[start].name, users[end].name);
        return;
    }
    
    // Reconstruct path
    int path[MAX_USERS];
    int pathLength = 0;
    int current = end;
    
    while (current != -1) {
        path[pathLength++] = current;
        current = prev[current];
    }
    
    printf("Weakest path (Dijkstra): ");
    for (int i = pathLength - 1; i >= 0; i--) {
        printf("%s", users[path[i]].name);
        if (i > 0) {
            printf(" -> ");
        }
    }
    printf("\nTotal weakness: %d\n", dist[end]);
}



// 10. Implement A* algorithm to find the weakest path
void aStarWeakestPath(const char* name1, const char* name2) {
    int start = findUserIndex(name1);
    int end = findUserIndex(name2);

    int gScore[MAX_USERS];
    int fScore[MAX_USERS];
    int cameFrom[MAX_USERS];
    bool openSet[MAX_USERS] = {false};
    
    for (int i = 0; i < userCount; i++) {
        gScore[i] = INT_MAX;
        fScore[i] = INT_MAX;
        cameFrom[i] = -1;
    }
    
    gScore[start] = 0;
    fScore[start] = (userCount - 1) - 0; // Heuristic: (num_users - 1) - num_friends
    
    openSet[start] = true;
    
    while (true) {
        // Find node in openSet with lowest fScore
        int current = -1;
        int minFScore = INT_MAX;
        
        for (int i = 0; i < userCount; i++) {
            if (openSet[i] && fScore[i] < minFScore) {
                minFScore = fScore[i];
                current = i;
            }
        }
        
        if (current == -1) break; // No path found
        if (current == end) break; // Path found
        
        openSet[current] = false;
        
        for (int neighbor = 0; neighbor < userCount; neighbor++) {
            if (adjacencyMatrix[current][neighbor] != NO_CONNECTION) {
                int tentativeGScore = gScore[current] + adjacencyMatrix[current][neighbor];
                
                if (tentativeGScore < gScore[neighbor]) {
                    cameFrom[neighbor] = current;
                    gScore[neighbor] = tentativeGScore;
                    
                    // Calculate heuristic: (num_users - 1) - num_friends
                    int numFriends = 0;
                    for (int i = 0; i < userCount; i++) {
                        if (adjacencyMatrix[neighbor][i] != NO_CONNECTION) numFriends++;
                    }
                    fScore[neighbor] = gScore[neighbor] + ((userCount - 1) - numFriends);
                    
                    openSet[neighbor] = true;
                }
            }
        }
    }
    
    if (gScore[end] == INT_MAX) {
        printf("No path exists between %s and %s\n", users[start].name, users[end].name);
        return;
    }
    
    // Reconstruct path
    int path[MAX_USERS];
    int pathLength = 0;
    int current = end;
    
    while (current != -1) {
        path[pathLength++] = current;
        current = cameFrom[current];
    }
    
    printf("Weakest path (A*): ");
    for (int i = pathLength - 1; i >= 0; i--) {
        printf("%s", users[path[i]].name);
        if (i > 0) {
            printf(" -> ");
        }
    }
    printf("\nTotal weakness: %d\n", gScore[end]);
}



// 11. Find connected components (groups) 
void dfsForComponents(const char* user, int* visited, int* component, int componentId) {
    int userIndex = findUserName(user) ;
    visited[userIndex] = 1;
    component[userIndex] = componentId;
    
    for (int i = 0; i < userCount; i++) {
        if (adjacencyMatrix[userIndex][i] != NO_CONNECTION && !visited[i]) {
            dfsForComponents(i, visited, component, componentId);
        }
    }
}

void findConnectedComponents() {
    int visited[MAX_USERS] = {0};
    int component[MAX_USERS];
    int componentId = 0;
    
    for (int i = 0; i < userCount; i++) {
        if (!visited[i]) {
            dfsForComponents(i, visited, component, componentId);
            componentId++;
        }
    }
    
    // Print components
    printf("\nConnected Components:\n");
    for (int c = 0; c < componentId; c++) {
        printf("Group %d: ", c + 1);
        for (int i = 0; i < userCount; i++) {
            if (component[i] == c) {
                printf("%s ", users[i].name);
            }
        }
        printf("\n");
    }
}



// 12. Implement function to get users ordered by number of friends (descending)
void orderUsersByFriendCount() {
    struct UserFriendCount {
        int index;
        int count;
    } friendCounts[MAX_USERS];
    
    for (int i = 0; i < userCount; i++) {
        friendCounts[i].index = i;
        friendCounts[i].count = 0;
        for (int j = 0; j < userCount; j++) {
            if (adjacencyMatrix[i][j] != NO_CONNECTION) {
                friendCounts[i].count++;
            }
        }
    }
    
    // Bubble sort (simple for small datasets)
    for (int i = 0; i < userCount - 1; i++) {
        for (int j = 0; j < userCount - i - 1; j++) {
            if (friendCounts[j].count < friendCounts[j + 1].count) {
                struct UserFriendCount temp = friendCounts[j];
                friendCounts[j] = friendCounts[j + 1];
                friendCounts[j + 1] = temp;
            }
        }
    }
    
    printf("\nUsers ordered by friend count (descending):\n");
    for (int i = 0; i < userCount; i++) {
        printf("%s: %d friends\n", users[friendCounts[i].index].name, friendCounts[i].count);
    }
}