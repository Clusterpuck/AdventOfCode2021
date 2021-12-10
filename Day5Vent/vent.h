#ifndef VENT_H
#define VENT_H

#define FALSE 0
#define TRUE !FALSE

#define DIMENSION 4
#define MAX_COORD 1000

int countIntersect( int **coords, int lines );
void fileSize( FILE* ventFilePtr, int *lines );
void readFile( FILE* ventFilePtr );

#endif
