#ifndef VENT_H
#define VENT_H

#define FALSE 0
#define TRUE !FALSE

#define DIMENSION 4
#define MAX_COORD 1000


void fileSize( FILE* ventFilePtr, int *lines );
void fillCoords( FILE* ventFilePtr, int **coords, int lines );
int countDanger( int **intersects );
void horizontalCount( int** intersects, int **hozVert, int count );
void diagCount( int** intersects, int **diag, int count );
int mapIntersect( int **hozVert, int hzCount, int** diag, int dCount, int lines );
int countIntersect( int **coords, int lines );
int readFile( FILE* ventFilePtr );

#endif
