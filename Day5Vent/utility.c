/******************************************************************************
 * Filename:  utility.c                                                       *
 * Author: Nicholas Wright 12880155                                           *
 * Purpose:                                                                   *
 * Assertions- PRE:                                                           *
 *            POST:                                                           *
 * Date Written:                                                              *
 * Edited By:       Date Edited:                                              *
 * ***************************************************************************/
#include <stdio.h>

void printIntArray( int *array, int length )
{
    int i;
    printf( "{" );
    for( i=0; i < length-1; i++ )
    {
        printf( "%d, ", array[i] );
    }
    i++;
    printf( "%d }\n", array[i] );
}


void printTwoDIntArray( int **array, int rows, int cols )
{
    int i,j;
    printf( "{" );
    for( i=0; i < rows; i++ )
    {
        for( j=0; j < cols; j++ )
        {
            printf("%d, ", array[i][j] );
        }
        printf("\n");
    }
    printf("}\n");
}

void printThreeDIntArray( int ***array, int rows, int cols, int blocks )
{
    int i, j, k;

    for( i = 0; i < blocks; i++ )
    {
        printf("{ ");

        for( j = 0; j < rows; j++ )
        {
            for( k=0; k< cols; k++ )
            {
                printf("%d, ", array[i][j][k] );
            }
            printf( "\n" );
        }

        printf( "}\n\n" );
    }
} 
