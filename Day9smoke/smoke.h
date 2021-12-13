#ifndef SMOKE_H
#define SMOKE_H

#define BORDER_VAL 10
#define MARK -1

#define UP arrayMap[i-1][j]
#define DOWN arrayMap[i+1][j]
#define LEFT arrayMap[i][j-1]
#define RIGHT arrayMap[i][j+1]
#define POS arrayMap[i][j]


void fillMap( FILE* smokeFilePtr, int **arrayMap, int rows, int cols );
int sumRisk( int **arrayMap, int rows, int cols );
void checkAround( int **arrayMap, int rows, int cols, int i, int j,
                 int *count, int checkVal );
void sizeBasins( int **basinData, int count,
                 int **arrayMap, int rows, int cols );
int readFile( FILE* smokeFilePtr );

#endif
