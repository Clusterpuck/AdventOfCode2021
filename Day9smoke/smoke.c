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
#include "smoke.h"
#include "utility.h"

void fillMap( FILE* smokeFilePtr, int **arrayMap, int rows, int cols )
{
    int i, j;
    /*Starts at 1 to account for border*/
    for( i=0; i < (rows+2); i++ )
    {
        for( j=0; j < (cols +2); j++ )
        {
            if( ( j == 0 ) || ( j == ( cols+1 ) ) ||
                ( i == 0 ) || ( i == ( rows+1 ) ) )
            {/*Inserts a border value greater than all other array values*/
                arrayMap[i][j] = BORDER_VAL;
            }   
            else
            {
                arrayMap[i][j] = fgetc( smokeFilePtr ) - 48;
                printf
            }
        }
        fgetc( smokeFilePtr );
        /*consumes end of line character*/
    }
    printTwoDIntArray( arrayMap, rows+2, cols+2 );
}


int sumRisk( int** arrayMap, int rows, int cols )
{
    int sum = 0;
    int i, j;
        /*starts at 1 to account for inserted border*/
    for( i=1; i < rows; i++ )
    {
        for( j=1; j < cols; j++ )
        {
            if( ( arrayMap[i][j] < LEFT ) && ( arrayMap[i][j] < RIGHT ) &&
                ( arrayMap[i][j] < UP ) && ( arrayMap[i][j] < DOWN ) )
            {
                sum += ( arrayMap[i][j]+1 );
                printf("Low point at %d,%d, value %d\n", i,j, arrayMap[i][j] );
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

    arrayMap = (int**)malloc( sizeof( int* ) * ( rows + 2 ) );
    for( i=0; i < ( rows+2); i++ )
    {  /*Increased by 2 to add border value*/
        arrayMap[i] = (int*)malloc( sizeof( int ) *( cols + 2 ) );
    }

    fillMap( smokeFilePtr, arrayMap, rows, cols );
    riskSum = sumRisk( arrayMap, rows, cols );

    return riskSum;
}
