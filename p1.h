#ifndef __P1_H__
#define __P1_H__

#include <stdlib.h>

// Declaration of the functions we are coding in p1.c

int findUserIndex(const char* name) ; //A

void printPath(int* path, int length) ; //B

int findFriendshipStrength (const char* name1, const char* name2) ; //C

void removeFriendship (const char* user, const char* friend) ; //D

void addFriendship (const char* user, const char* friend, int strength) ; //E

float findAverageFriendshipStrenght(const char* name) ; //F

void initializeGraph() ; //1

void addUserWithFriendships(const char* name, int friendCount, const char** friendNames, const int* strengths) ; //2

void removeUser(const char* name) ; //3

void modifyFriendship(const char* name1, const char* name2, int strength) ; //4

int findShortestPath(const char* name1, const char* name2, int* path) ; //5

void findPotentialFriends(const char* name, int level, int* friends, int* count) ; //6

void exploreAllFriendships(const char* name, int* visited) ; //7

bool hasPath(const char* name1, const char* name2) ; //8

void dijkstraWeakestPath(const char* name1, const char* name2) ; //9

void aStarWeakestPath(const char* name1, const char* name2) ; //10

void dfsForComponents(const char* user, int* visited, int* component, int componentId) ; //11

void findConnectedComponents() ; //11

void orderUsersByFriendCount() ; //12

#endif