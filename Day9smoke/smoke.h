#ifndef SMOKE_H
#define SMOKE_H

#define BORDER_VAL 10

#define UP arrayMap[i-1][j]
#define DOWN arrayMap[i+1][j]
#define LEFT arrayMap[i][j-1]
#define RIGHT arrayMap[i][j+1]


void fillMap( FILE* smokeFilePtr, int **arrayMap, int rows, int cols );
int sumRisk( int **arrayMap, int rows, int cols );
int readFile( FILE* smokeFilePtr );

#endif
