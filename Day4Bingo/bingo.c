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
/*    int nRead = 0;*/
    int done = FALSE;
    int input1;
    int count = 1; /*Starts at one to factor first strtok read*/
    char *readLine = (char*)malloc( sizeof(char) * 1064 );
    char *temp = (char*)malloc( sizeof(char)* 52 );

    fgets( readLine, 1000, bingoFilePtr );
    input1 = atoi( strtok( readLine, "," ) );
    printf( "Input reads %d\n", input1 );
    while( !done )
    {        
        temp = strtok( NULL, "," );
        if( temp != NULL )
        {
            ++count;
            input1 = atoi( temp );
            printf( "Input reads %d\n", input1 );
        }
        else
        {
            done = TRUE;
        }
    }
    printf( "The final count is %d\n", count );
}


void readFile( FILE* bingoFilePtr )
{
/*    int *drawnNums;
    int **bingoCard;*/
    int draws = 0;
    int cardNum = 0;

    fileSize( bingoFilePtr, &draws, &cardNum );
}
     
