/******************************************************************************
 * Filename:                                                                  *
 * Author: Nicholas Wright 12880155                                           *
 * Purpose:                                                                   *
 * Assertions- PRE:                                                           *
 *            POST:                                                           *
 * Date Written:                                                              *
 * Edited By:       Date Edited:                                              *
 * ***************************************************************************/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "bingo.h"

void fileSize( FILE* bingoFilePtr, int* drawsPtr, int* cardNumPtr )
{
    int done = FALSE;
    int input1;
    char *readLine = (char*)malloc( sizeof(char) * 1064 );
    char *temp = (char*)malloc( sizeof(char)* 52 );
    char *endCheck;
    (*drawsPtr) = 1; /*Starts at one to factor first strtok read*/

    fgets( readLine, 1000, bingoFilePtr );
    input1 = atoi( strtok( readLine, "," ) );
    printf( "Input reads %d\n", input1 );
    while( !done )
    {
        temp = strtok( NULL, "," );
        if( temp != NULL )
        {
            ++(*drawsPtr);
            input1 = atoi( temp );
            printf( "Input reads %d\n", input1 );
        }
        else
        {
            done = TRUE;
        }
    }
    printf( "The final count is %d\n", *drawsPtr );

    done = FALSE;
    while( !done )
    {
        endCheck = fgets( readLine, 1000, bingoFilePtr );
        if( !strcmp( readLine, "\n" ) )
        {
            (*cardNumPtr)++;
            printf("Card number is %d\n", *cardNumPtr );
        }
        if( endCheck == NULL )
        {
            done = TRUE;
        }
    }
}

void extractData( FILE* bingoFilePtr, int draws, int cardNum )
{
    int i, j;
    int *drawValues = (int*)malloc( sizeof( int ) * draws );
    int ***bingoCards = (int***)malloc( sizeof(int**) * cardNum );

    for( i=0; i < cardNum; i++ )
    {
        bingoCards[i] = (int**)malloc( sizeof(int*) * BINGO_SIZE );
        for( j=0; j < BINGO_SIZE; j++ )
        {
            bingoCard[i][j] = (int*)malloc( sizeof(int) * BINGO_SIZE );
        }
    }

    rewind( bingoFilePtr );

    fillDrawValues( bingoFilePtr, 


void readFile( FILE* bingoFilePtr )
{
    int draws = 0;
    int cardNum = 0;

    fileSize( bingoFilePtr, &draws, &cardNum );
    extractData( bingoFilePtr, draws, cardNum );
}
