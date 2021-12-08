#ifndef BINGO_H
#define BINGO_H

#define FALSE 0
#define TRUE !FALSE

void fileSize( FILE* bingofFilePtr, int *drawsPtr, int *cardNumPtr );
void readFile( FILE *bingoFilePtr );

#endif
