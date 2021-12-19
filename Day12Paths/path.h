#ifndef PATH_H
#define PATH_H

#include "linkedlist.h"

#define FALSE 0
#define TRUE !FALSE

#define BIG_DATA 1064
#define SMALL_DATA 512

typedef struct
{
    /*linked list will be pointers to all connected nodes*/
    LinkedList *connections;
    /*vertix is the name of the vertix provided in input*/
    char* vertix;
    int big; /*treat as boolean to apply to visited boolean test. union?*/
    int visited;

} node;

void fileSize( FILE* pathsFilePtr, int *lines );
int readFile( FILE* pathsFilePtr );

#endif


