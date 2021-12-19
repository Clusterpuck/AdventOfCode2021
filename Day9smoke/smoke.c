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
            }
        }
        if( ( i != 0 ) && ( i != ( rows+1 ) ) )
        {
            fgetc( smokeFilePtr );
        }
        /*consumes end of line character*/
    }
    printTwoDIntArray( arrayMap, rows+2, cols+2 );
}

void sizeBasins( int** basinData, int count, int** arrayMap )
{
    int i;
    for( i = 0; i < count; i++ )
    {
        printf( "Starting search for %d\n",
                arrayMap[basinData[i][0]][basinData[i][1]] );
        checkAround( arrayMap, basinData[i][0], basinData[i][1],
                     &( basinData[i][2] ),
                     arrayMap[basinData[i][0]][basinData[i][1]] );
    }

    printTwoDIntArray( basinData, count, 3 );
}


int sumRisk( int** arrayMap, int rows, int cols )
{
    int sum = 0;
    int i, j;
    int count = 0;
    int **basinData = (int**)malloc( sizeof(int*) * 1000 );
    for( i=0; i < 1000; i++ )
    {
        basinData[i] = (int*)malloc( sizeof( int ) * 3 );
        /*To contain i and j values of start of basin in 0 and 1
 *        and then 2 will contain the size of the basin*/
    }

        /*starts at 1 to account for inserted border*/
    for( i=1; i < ( rows+1) ; i++ )
    {
        for( j=1; j < ( cols+1 ); j++ )
        {
            if( ( arrayMap[i][j] < LEFT ) && ( arrayMap[i][j] < RIGHT ) &&
                ( arrayMap[i][j] < UP ) && ( arrayMap[i][j] < DOWN ) )
            {
                sum += ( arrayMap[i][j]+1 );
                printf("Low point at %d,%d, value %d\n", i,j, arrayMap[i][j] );

                basinData[count][0] = i;
                basinData[count][1] = j;
                basinData[count][2] = 1;
                ++count;
            }
        }
    }

    sizeBasins( basinData, count, arrayMap );
    return sum;
}

void checkAround( int** arrayMap, int i, int j, int* count, int checkVal )
{
    int newCheck;
    printf( "checking around %d\n", checkVal );

    if( ( i > 0 ) && ( UP >= checkVal ) && ( UP < 9 ) )
    {
        (*count)++;
        --i;
        newCheck = POS;
        POS = -1;
        checkAround( arrayMap, i, j, count, newCheck );
    }
    if( ( DOWN >= checkVal ) &&  ( DOWN < 9 ) )
    { /*Will the recursive remember the i's and j's from the first call*/
        (*count)++;
        ++i;
        newCheck = POS;
        POS = -1;
        checkAround( arrayMap, i, j, count, newCheck );
    }
    if( ( j > 0 ) && ( LEFT >= checkVal ) && ( LEFT < 9 ) )
    {
        (*count)++;
        --j;
        newCheck = POS;
        POS = -1;
        checkAround( arrayMap, i, j, count, newCheck );
    }
    if( ( RIGHT >= checkVal ) && ( RIGHT < 9 ) )
    {
        (*count)++;
        ++j;
        newCheck = POS;
        POS = -1;
        checkAround( arrayMap, i, j, count, newCheck );
    }
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
