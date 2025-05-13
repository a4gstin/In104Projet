#ifndef __P1_H__
#define __P1_H__

#include <stdlib.h>

// Declaration of the functions we are coding in p1.c

int findUserIndex(const char* name) ;

void printPath(int* path, int length) ;

void initializeGraph() ;

void addUserWithFriendships(const char* name, int friendCount, const char** friendNames, const int* strengths) ;

void removeUser(const char* name) ;

void modifyFriendship(const char* name1, const char* name2, int strength) ;

int findShortestPath(int start, int end, int* path) ;

void removeUser(const char* name) ;

#endif