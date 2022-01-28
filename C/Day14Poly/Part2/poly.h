#ifndef POLY_H
#define POLY_H

#define NUM_CYCLES 4
#define ALPHA_NUM 26

void fileSize( FILE* polyFilePtr, long *monomerLength, int *pairs );
void fillPairs( FILE* polyFilePtr, long ***pairs, int pairNum );
void pairCycles( long ***pairs, int cycles, int firstLetter );
void tallyMonomer( long ***pairs, int firstLetter );
void callocThreeDLong( long ****array, int rows, int cols, int blocks );
void copyThreeDLong( long ***oldArray, long ***newArray,
                     int rows, int cols, int blocks );
void freeThreeDLong( long ***array, int rows, int cols );
int readFile( FILE* polyFilePtr );

#endif
