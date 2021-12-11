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
#include <string.h>
#include "crabsub.h"
#include "utility.h"

int fileSize( FILE* crabsubFilePtr )
{
    int count = 0;
    char *readLine = (char*)malloc( sizeof( char ) * BIG_DATA );
    char *temp = (char*)malloc( sizeof( char ) * SMALL_DATA );

    fgets( readLine, BIG_DATA, crabsubFilePtr );
    temp = strtok( readLine, "," );
    while( temp != NULL )
    {
        ++count;
        temp =  strtok( NULL, "," );
    }

    free( temp );
    free( readLine );
    rewind( crabsubFilePtr );
    return count;
}

void fillCrabs( FILE* crabsubFilePtr, int* crabArray, int crabs )
{
    int i = 0;
    char *readLine = (char*)malloc( sizeof( char ) * BIG_DATA );

    fgets( readLine, BIG_DATA, crabsubFilePtr );
    crabArray[i] = atoi( strtok( readLine, "," ) );
    for( i = 1; i < crabs; i++ )
    {
        crabArray[i] = atoi( strtok( NULL, "," ) );
    }
    free( readLine );
    fclose( crabsubFilePtr );
}

double averageCrab( int* crabArray, int crabs )
{
    double sum = 0.0;
    int i;

    for( i=0; i < crabs; i++ )
    {
        sum += crabArray[i];
    }

    return sum/crabs;
}

long fuelCost( int* crabArray, int crabs, int goal )
{
    /*Fuel cost now calculated with triangular number (n(n+1))/2*/
    long fuel = 0;
    int i, diff;
    for( i=0; i < crabs; i++ )
    {
        diff = abs( crabArray[i] - goal );

        fuel += ( ( diff*( diff+1 ) ) / 2 );
    }

    return fuel;
}

int findDistance( int* crabArray, int crabs, int average )
{
    long fuel, fuelNext;
    do
    {
        fuel = fuelCost( crabArray, crabs, average );
        ++average;
        fuelNext = fuelCost( crabArray, crabs, average );
    }while( fuel > fuelNext );
    do
    {
        fuel = fuelCost( crabArray, crabs, average );
        --average;
        fuelNext = fuelCost( crabArray, crabs, average );
    }while( fuel > fuelNext );
    printf( "The spot to move to is %d\n", average );
    return fuel;
}


int readFile( FILE* crabsubFilePtr )
{
    int crabs = 0;
    int *crabArray;
    double averageDist;
    long fuel;

    crabs = fileSize( crabsubFilePtr );

    crabArray = (int*)malloc( sizeof(int)*crabs );
    fillCrabs( crabsubFilePtr, crabArray, crabs );
    averageDist = averageCrab( crabArray, crabs );
    printf("The average distance is %f\n", averageDist );
    fuel = findDistance( crabArray, crabs, averageDist );
    free( crabArray );
    return fuel;
}
