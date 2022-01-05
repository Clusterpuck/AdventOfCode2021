/******************************************************************************
 * Filename:  poly.c                                                          *
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

#include "poly.h"
#include "utility.h"

void fileSize( FILE *polyFilePtr, int *monomerLength, int *pairs )
{
    char *monoString = (char*)malloc( sizeof( char ) * 512 );
    char *endTest = (char*)malloc( sizeof( char ) * 512 );
    fgets( monoString, 512, polyFilePtr );
    (*monomerLength) = strlen( monoString );
    fgets( endTest, 512, polyFilePtr );

    while( endTest != NULL )
    {
        endTest = fgets( monoString, 512, polyFilePtr );
        ++(*pairs);
    }
    --(*pairs);
    rewind( polyFilePtr );
}

void fillPairs( FILE* polyFilePtr, char **pairs, int pairNum )
{
    int i;
        fscanf( polyFilePtr, "\n%c%c -> %c\n", 
                &(pairs[0][0]), &(pairs[0][1]), &(pairs[0][2]) );
    for( i=1; i < pairNum; i++ )
    {
        fscanf( polyFilePtr, "%c%c -> %c\n", 
                &(pairs[i][0]), &(pairs[i][1]), &(pairs[i][2]) );
    }
}

void makeNewMonomer( char **monomer, char **newMonomer, 
                     int monoLength, int matches )
{
    int i;
    int pos = 0;
    /*First letter always stays*/
    for( i=0; i < monoLength; i++ )
    {
        newMonomer[0][pos] = monomer[0][i];
        ++pos;
        if( monomer[1][i] != 0 )
        {
            newMonomer[0][pos] = monomer[1][i];
            ++pos;
        }
    }
}

void tallyMonomer( char *monomer, int monoLength )
{
    /*search 65 to 90 inclusive. */
    int i, j;
    long *counts = (long*)calloc( 26, sizeof( long ) );
    long max, min;
    for( i=0; i < monoLength; i++ )
    {
        for( j=0; j < 26; j++ )
        {
            if( monomer[i] == ( j + 65) )
            {
                ++(counts[j]);
            }
        }
    }
    max = counts[0];
    min = 2000;
    for( i = 1; i < 26; i++ )
    {
        if( counts[i] > max )
        {
            printf( "Found new max of %ld\n", counts[i] );
            max = counts[i];
        }
        if( ( counts[i] !=0 ) && ( counts[i] < min ) )
        {
            min = counts[i];
        }
    }
    printf( "Min is %ld, max is %ld\nDifference is %ld\n", min, max, max-min );
}

void pairCycles( char **monomer, int monoLength, char **pairs,
                 int pairNum, int cycles )
{
    int i, j;
    int matches = 0;
    char **newMonomer;

    for( i=0; i < monoLength-1; i++ )
    {
        for( j=0; j < pairNum; j++ )
        {
            if( ( monomer[0][i] == pairs[j][0] ) &&
                ( monomer[0][i+1] == pairs[j][1] ) )
            {
                ++matches;
                monomer[1][i] = pairs[j][2];
            }
        }
    }
    newMonomer = (char**)calloc( 2, sizeof( char* ) );
    newMonomer[0] = (char*)calloc( (monoLength + matches ), sizeof( char ) );
    newMonomer[1] = (char*)calloc( (monoLength + matches ), sizeof( char ) );
    makeNewMonomer( monomer, newMonomer, monoLength, matches );
    if( cycles < NUM_CYCLES )
    {
        free( monomer[0] );
        free( monomer[1] );
        free( monomer );
        ++cycles;
        pairCycles( newMonomer, monoLength+matches, pairs, pairNum, cycles );
    }
    else
    {
        printf( "Cycle number %d\n", cycles );
        tallyMonomer( monomer[0], monoLength );
    }
}


int readFile( FILE* polyFilePtr )
{
    int monomerLength = 0;
    int pairNum = 0;
    char **pairs;
    char **monomer;
    int i;
    int cycles = 0;
    fileSize( polyFilePtr, &monomerLength, &pairNum );

    monomer = (char**)calloc( 2, sizeof( char* ) );
    monomer[0] = (char*)calloc( monomerLength, sizeof( char ) );
    monomer[1] = (char*)calloc( monomerLength, sizeof( char ) );
    /*Monomer is 2D to hold the insertions in the second line*/

    fgets( monomer[0], monomerLength, polyFilePtr );

    pairs = (char**)malloc( sizeof( char* ) * pairNum );
    for( i=0; i < pairNum; i++ )
    {
        pairs[i] = (char*)malloc( sizeof( char ) * 3 );
    }
    /*Creates a 2D char array to hold the char pairs and then their outcome*/

    fillPairs( polyFilePtr, pairs, pairNum );

    pairCycles( monomer, monomerLength, pairs, pairNum, cycles );


    return pairNum;
}
