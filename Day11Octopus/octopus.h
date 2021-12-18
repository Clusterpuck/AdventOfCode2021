#ifndef OCTOPUS_H
#define OCTOPUS_H

#define FALSE 0
#define TRUE !FALSE

#define ROWS 5
#define COLS 5
#define DAYS 100


void postFlash( int **octoArray, int i, int j );
int scanArray( int **octoArray, int flashCount, int *flashed );
int dayCycle( int **octoArray );
int readFile( FILE *octopusFilePtr );


#endif
