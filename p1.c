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

// 6. Implement function to find all potential friends at level n (BFS)
void findPotentialFriends(int userIndex, int level, int* friends, int* count) {
    if (level < 1) {
        *count = 0;
        return;
    }
    
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
void exploreAllFriendships(int userIndex, int* visited) {
    visited[userIndex] = 1;
    printf("%s ", users[userIndex].name);
    
    for (int i = 0; i < userCount; i++) {
        if (adjacencyMatrix[userIndex][i] != NO_CONNECTION && !visited[i]) {
            exploreAllFriendships(i, visited);
        }
    }
}

// 8. Implement function to explore whether there is a potential path between two users
bool hasPath(int start, int end) {
    if (start == end) return true;
    
    int visited[MAX_USERS] = {0};
    int queue[MAX_USERS];
    int front = 0, rear = 0;
    
    visited[start] = 1;
    queue[rear++] = start;
    
    while (front < rear) {
        int current = queue[front++];
        
        for (int i = 0; i < userCount; i++) {
            if (adjacencyMatrix[current][i] != NO_CONNECTION && !visited[i]) {
                if (i == end) return true;
                visited[i] = 1;
                queue[rear++] = i;
            }
        }
    }
    
    return false;
}

// 9. Use Dijkstra's Algorithm to find the weakest path of friendships
void dijkstraWeakestPath(int start, int end) {
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

// 10. Use A* Algorithm to find the weakest path
void aStarWeakestPath(int start, int end) {
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
void dfsForComponents(int userIndex, int* visited, int* component, int componentId) {
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

// 12. Get users ordered by number of friends (descending)
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

