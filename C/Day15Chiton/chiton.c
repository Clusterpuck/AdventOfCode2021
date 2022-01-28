/******************************************************************************
 * Filename:  chiton.c                                                        *
 * Author: Nicholas Wright 12880155                                           *
 * Purpose:                                                                   *
 * Assertions- PRE:                                                           *
 *            POST:                                                           *
 * Date Written:                                                              *
 * Edited By:       Date Edited:                                              *
 * ***************************************************************************/
#include <stdio.h>
#include <stdlib.h>

#include "utility.h"
#include "chiton.h"

void fillMap( FILE* chitonFilePtr, int **arrayMap, int rows, int cols )
{
    int i, j;
    for( i=0; i < rows; i++ )
    {
        for( j=0; j < cols; j++ )
        {
            arrayMap[i][j] = fgetc( chitonFilePtr ) - 48;
        }
        if( i != rows )
        {
            fgetc( chitonFilePtr );
        }
    }
    printTwoDIntArray( arrayMap, rows, cols );
}


int readFile( FILE* chitonFilePtr )
{
    int i;
    int input = 0;
    int rows = 0;
    int cols = 0;
    int **arrayMap;

    while( input != -49 )
    {
        input = fgetc( chitonFilePtr ) - 48;
        if( input == -38 )
        {
            ++rows;
        }
        else
        {
            ++cols;
        }
    }
    rewind( chitonFilePtr );
    cols = cols/rows;

    arrayMap = (int**)malloc( sizeof( int* ) * rows );
    for( i=0; i < rows; i++ )
    {
        arrayMap[i] = (int*)malloc( sizeof( int ) *cols );
    }

    fillMap( chitonFilePtr, arrayMap, rows, cols );

    printf( "Number of columns is %d\n", cols );

    return rows;
}
