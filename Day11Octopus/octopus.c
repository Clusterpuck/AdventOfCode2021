/******************************************************************************
 * Filename:                                                                  *
 * Author: Nicholas Wright 12880155                                           *
 * Purpose:                                                                   *
 * Assertions- PRE:                                                           *
 *            POST:                                                           *
 * Date Written:                                                              *
 * Edited By:       Date Edited:                                              *
 * ***************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include "octopus.h"
#include "utility.h"

/*Each step increases all octopi energy by 1*/
/**/
/*If between steps, don't got past zero as can only flash once*/
void postFlash( int **octoArray, int i, int j )
{
    int minI = i-1, minJ = j-1, maxI=( i+1 ), maxJ=( j+1 );
    if( i == 0 )
        minI = 0;
    if( j == 0 )
        minJ = 0;
    if( i == ( ROWS-1 ) )
    {
        printf( "i is %d\n" , i );
        maxI = ROWS;
    }
    if( j == (COLS-1 ) )
        maxJ = COLS;
    for( i = minI; i < maxI; i++ )
    {
        for( j = minJ; j < maxJ; j++ )
        {
            if( octoArray[i][j] != 0 )
            {
                ++( octoArray[i][j] );
            }
        }
    }
}

int scanArray( int** octoArray, int flashCount, int *flashed )
{
    int i, j;
    (*flashed) = FALSE;
    for( i=0; i < ROWS; i++ )
    {
        for( j=0; j < COLS; j++ )
        {
            if( octoArray[i][j] > 9 )
            {
                (*flashed) = TRUE;
                ++flashCount;
                octoArray[i][j] = 0;
                postFlash( octoArray, i, j );
            }
        }
    }
    return flashCount;
}


int dayCycle( int** octoArray )
{
    int flashCount = 0;
    int i, j, k;
    int flashed;
    for( k=0; k < DAYS; k++ )
    {
        for( i = 0; i < ROWS; i++ )
        {
            for( j=0; j < COLS; j++ )
            {
                ++( octoArray[i][j] );
            }
        }
        do
        {
            flashCount = scanArray( octoArray, flashCount, &flashed );
        }while( flashed );

        if( k <=10 )
        {
            printf( "Step %d\n", k+1 );
            printTwoDIntArray( octoArray, ROWS, COLS );
        }
    }

    return flashCount;
}

int readFile( FILE *octopusFilePtr )
{
    int i, j, flashes;
    int** octoArray = (int**)malloc( sizeof( int* ) * ROWS );
    for( i=0; i < ROWS; i++ )
    {
        octoArray[i] = (int*)malloc( sizeof( int )* COLS );
        for( j = 0; j < COLS; j++ )
        {
            octoArray[i][j] = ( fgetc( octopusFilePtr ) - 48 );
        }
        fgetc( octopusFilePtr );
        /*consumes end of line character*/
    }

    printTwoDIntArray( octoArray, ROWS, COLS );

    flashes = dayCycle( octoArray );

    return flashes;

}
