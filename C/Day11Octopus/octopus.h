#ifndef OCTOPUS_H
#define OCTOPUS_H

#define FALSE 0
#define TRUE !FALSE

#define ROWS 10
#define COLS 10
#define DAYS 200
#define OCTO_NUM 100


void postFlash( int **octoArray, int i, int j );
int scanArray( int **octoArray, int flashCount, int *flashed );
int dayCycle( int **octoArray );
int readFile( FILE *octopusFilePtr );


#endif
