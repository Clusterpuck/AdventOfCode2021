/******************************************************************************
 * Filename:  fish.c                                                          *
 * Author: Nicholas Wright 12880155                                           *
 * Purpose:                                                                   *
 * Assertions- PRE:                                                           *
 *            POST:                                                           *
 * Date Written:                                                              *
 * Edited By:       Date Edited:                                              *
 * ***************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fish.h"
#include "utility.h"


void fillFishArray( FILE* fishFilePtr, unsigned long *fishArray )
{
    char *readLine = (char*)malloc( sizeof( char ) * 10000 );
    char *temp = (char*)malloc( sizeof( char ) * 64 );
    int age;

    fgets( readLine, 10000, fishFilePtr );
    temp = strtok( readLine, "," );
    while( temp != NULL )
    {
        age = atoi( temp );
        ( fishArray[age] )++; /*increases the count of fish of that cycle point*/
        temp = strtok( NULL, "," );
    }

    free( temp );
    fclose( fishFilePtr );
    free( readLine );

}

void cycleDays( unsigned long *fishArray )
{
    int i, j;
    unsigned long temp;
    for( i=0; i < DAYS; i++ )
    {
        temp = fishArray[0];
        for( j=0; j < ( LONGEST_CYCLE -1 ); j++ )
        {
            fishArray[j] = fishArray[j+1];
        }
        fishArray[LONGEST_CYCLE-1] = temp;
        fishArray[FERTILE_AGE] += temp;
    }
}

unsigned long sumArray( unsigned long *fishArray )
{
    int i;
    unsigned long sum = 0;
    for( i=0; i < LONGEST_CYCLE; i++ )
    {
        sum += fishArray[i];
    }
    free( fishArray );
    return sum;
}


unsigned long readFile( FILE* fishFilePtr )
{
    unsigned long *fishArray =
            (unsigned long*)calloc( LONGEST_CYCLE, sizeof(unsigned long) );

    fillFishArray( fishFilePtr, fishArray );
    cycleDays( fishArray );
    printULongArray( fishArray, LONGEST_CYCLE );

    return sumArray( fishArray );
}
