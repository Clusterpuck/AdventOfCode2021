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
#include "utility.h"

void fileSize( FILE* bingoFilePtr, int* drawsPtr, int* cardNumPtr )
{
    int input1;
    int done = FALSE;
    char *readLine = (char*)malloc( sizeof(char) * 1064 );
    char *temp = (char*)malloc( sizeof(char)* 52 );
    char *endCheck;
    (*drawsPtr) = 1; /*Starts at one to factor first strtok read*/

    fgets( readLine, 1000, bingoFilePtr );
    input1 = atoi( strtok( readLine, "," ) );
    while( !done )
    {
        temp = strtok( NULL, "," );
        if( temp != NULL )
        {
            ++(*drawsPtr);
            printf("%d", input1 );
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
        }
        if( endCheck == NULL )
        {
            done = TRUE;
        }
    }
}

void fillDrawValues( FILE* bingoFilePtr, int* drawValues, int draws )
{
    int i = 0;
    char *readLine = (char*)malloc( sizeof( char ) * 1064);
    char *temp;

    fgets( readLine, 1000, bingoFilePtr );
    drawValues[i] = atoi( strtok( readLine, "," ) );

    for( i = 1; i < draws; i++ )
    {
        temp = strtok( NULL, "," );
        drawValues[i] = atoi( temp );
    }
    printIntArray( drawValues, draws );
}

void fillBingoCards( FILE* bingoFilePtr, int*** bingoCards, int cardNum )
{
    int i = 0;/*This will represent the card number to fill*/
    int j = 0;
    int k = 0;/*j and k are the two dimensions of the bingo card 6*6*/
    char *readLine = (char*)malloc( sizeof( char )* 1000 );

    while( i < cardNum )
    {
        fgets( readLine, 1000, bingoFilePtr );
        /*Consumes the blank line between cards*/
        for( j = 0; j < BINGO_SIZE; j++ )
        {
            k=0;
            fgets( readLine, 1000, bingoFilePtr );
            /*Reads in one row of a bingo card*/
            bingoCards[i][j][k] = atoi( strtok( readLine, " " ) );
            /*First element read outside loop to activate strtok*/

            for( k = 1; k < BINGO_SIZE; k++ )
            {
               bingoCards[i][j][k] = atoi( strtok( NULL, " " ) );
            }
            bingoCards[i][j][BINGO_SIZE] = 0;
        }
        bingoCards[i][BINGO_SIZE][k] = 0;
        i++;
    }
    free( readLine );
}

int playbingo( int ***bingoCards, int *drawValues, int cardNum, int draws, 
                int *winNumPtr )
{
/*To check which wins last I need to stop checking a won board*/

    int i=0, j=0, k=0, d=0, winCard = 0;
    int bingo = FALSE;
    int winCount = 0;
    int wonCard[100];

    for( i=0; i < 100; i++ )
    {
        wonCard[i] = FALSE;
    }
    printf( "drawValues array inside playBingo is\n " );
    printIntArray( drawValues, draws );

    while( ( d < draws ) && !bingo )
    {
        i=0;
        while( ( i < cardNum ) && !bingo )
        {
            j=0;
            while( ( j < BINGO_SIZE ) && !bingo )
            {
                k=0;
                while( ( k < BINGO_SIZE ) && !bingo )
                {
                    printf(" Looking for %d, to match card value %d\n",
                            drawValues[d], bingoCards[i][j][k] );
                    if( drawValues[d] == bingoCards[i][j][k] )
                    {
                        printf( "match found\n" );
                        bingoCards[i][j][k] = bingoCards[i][j][k]*(-1);
                        /*Tags bingo number as match*/
                        ( bingoCards[i][BINGO_SIZE][k] )++;
                        ( bingoCards[i][j][BINGO_SIZE] )++;
                        /*Increases count of row and column counters*/
                        if( !wonCard[i] && ( 
                            ( bingoCards[i][BINGO_SIZE][k] == 5 ) ||
                            ( bingoCards[i][j][BINGO_SIZE] == 5 ) ) )
                        {
                            wonCard[i] = TRUE;
                            winCount++;
                            if( winCount > 99 )
                            {
                                printf( "BINGO!!\n");
                                bingo = TRUE;
                                winCard = i;
                                (*winNumPtr) = drawValues[d];
                            }
                        }
                    }
                    ++k;
                }
                ++j;
            }
            ++i;
        }
        ++d;
    }
    return winCard;
}

int calculateWin( int **winCard, int winNum )
{
    int sum = 0;
    int i, j;
    for( i=0; i < BINGO_SIZE; i++ )
    {
        for( j=0; j < BINGO_SIZE; j++ )
        {
            if( winCard[i][j] >= 0 )
            {
                sum += winCard[i][j];
            }
        }
    }
    sum *= winNum;
    return sum;
}

void extractData( FILE* bingoFilePtr, int draws, int cardNum )
{
    int i, j, winCard, winNum, winScore;
    int *drawValues = (int*)malloc( sizeof( int ) * draws );
    int ***bingoCards = (int***)malloc( sizeof(int**) * cardNum );

    for( i=0; i < cardNum; i++ )
    {
        bingoCards[i] = (int**)malloc( sizeof(int*) * ( BINGO_SIZE + 1 ) );

        for( j=0; j < ( BINGO_SIZE+1); j++ )
        {
            bingoCards[i][j] = (int*)malloc( sizeof(int) * ( BINGO_SIZE + 1 ) );
        }
    }

    rewind( bingoFilePtr );

    fillDrawValues( bingoFilePtr, drawValues, draws );
    fillBingoCards( bingoFilePtr, bingoCards, cardNum );

    winCard = playbingo( bingoCards, drawValues, cardNum, draws, &winNum );
    printf( "Winning card is %d\n", winCard );
    winScore = calculateWin( bingoCards[winCard], winNum );
    printf( "The winning result is %d\n", winScore );
}


void readFile( FILE* bingoFilePtr )
{
    int draws = 0;
    int cardNum = 0;

    fileSize( bingoFilePtr, &draws, &cardNum );
    extractData( bingoFilePtr, draws, cardNum );
}
