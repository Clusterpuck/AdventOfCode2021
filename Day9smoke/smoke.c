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
#include "utility.h"

void fillMap( FILE* smokeFilePtr, int **arrayMap, int rows, int cols )
{
    int i, j;
    for( i=0; i < rows; i++ )
    {
        for( j=0; j < cols; j++ )
        {
            arrayMap[i][j] = fgetc( smokeFilePtr ) - 48;
        }
        fgetc( smokeFilePtr );
        /*consumes end of line character*/
    }
    printTwoDIntArray( arrayMap, rows, cols );
}

int sumRisk( int** arrayMap, int rows, int cols )
{
    int sum = 0;
    int i, j = 0;
    int left = 0, right = 0, up = 0, down = 0;
    for( i=0; i < rows; i++ )
    {
        if( i == (rows - 1 ) )
        {
            down = 0;
        }
        else if( i != 0 )
        {
            up = arrayMap[i+1][j];
            down = arrayMap[i-1][j];
        }
        for( j=0; j < cols; j++ )
        {
            if( j == 0 )
            {
                left = 0;
                right = arrayMap[i][j+1];
            }
            else if( j == (cols-1) )
            {
                right = 0;
                left = arrayMap[i][j-1];
            }
            else
            {
                left = arrayMap[i][j-1];
                right = arrayMap[i][j+1];
            }
            if( ( arrayMap[i][j] < left ) && ( arrayMap[i][j] < right ) &&
                ( arrayMap[i][j] < up ) && ( arrayMap[i][j] < down ) )
            {
                sum += arrayMap[i][j]+1;
                printf("Low point at %d,%d, or %d\n", i,j, arrayMap[i][j] );
            }
        }
    }
    return sum;
}


int readFile( FILE* smokeFilePtr )
{
    int i;
    int input = 0;
    int rows  = 0;
    int cols  = 0;
    int riskSum = 0;
    int** arrayMap;
    while( input != -49 )
    {
        input = fgetc( smokeFilePtr ) - 48;
        if( input == -38 )
        {
            ++rows;
        }
        else
        {
            ++cols;
        }
    }
    rewind( smokeFilePtr );
    cols = cols/rows;

    arrayMap = (int**)malloc( sizeof( int* ) * rows );
    for( i=0; i < rows; i++ )
    {
        arrayMap[i] = (int*)malloc( sizeof( int ) *cols );
    }

    fillMap( smokeFilePtr, arrayMap, rows, cols );
    riskSum = sumRisk( arrayMap, rows, cols );

    return riskSum;
}
