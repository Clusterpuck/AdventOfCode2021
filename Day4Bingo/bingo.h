#ifndef BINGO_H
#define BINGO_H

#define FALSE 0
#define TRUE !FALSE

#define BINGO_SIZE 6

void fillDrawValues( FILE *bingoFilePtr, int *drawValues, int draws );
void extractData( FILE *bingoFilePtr, int draws, int cardNum );
void fileSize( FILE* bingofFilePtr, int *drawsPtr, int *cardNumPtr );
void readFile( FILE *bingoFilePtr );

#endif
