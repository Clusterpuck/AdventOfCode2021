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

void fileSize( FILE *polyFilePtr, long *monomerLength, int *pairs )
{
    char *monoString = (char*)malloc( sizeof( char ) * 512 );
    char *endTest = (char*)malloc( sizeof(char) *512 );
    fgets( monoString, 512, polyFilePtr );
    (*monomerLength) = strlen( monoString );
    fgets( endTest, 512, polyFilePtr );

    while( endTest != NULL )
    {
        endTest = fgets( monoString, 512, polyFilePtr );
        ++(*pairs);
    }
    --(*pairs);
    free( endTest );
    free( monoString );
    rewind( polyFilePtr );
}

void fillPairs( FILE* polyFilePtr, char **pairs, int pairNum )
{/*Now each insertion letter is saved at the apropiate array location for it's
   pairs int value*/
    int i;
    char tempA, tempB, tempC;

    fscanf( polyFilePtr, "\n%c%c -> %c\n",
            &tempA, &tempB, &tempC );
    pairs[( tempA-65 )][( tempB-65 )] = tempC;

    for( i=1; i < pairNum; i++ )
    {
        fscanf( polyFilePtr, "%c%c -> %c\n",
                &tempA, &tempB, &tempC );
        pairs[( tempA-65 )][( tempB-65 )] = tempC;
    }
}

void makeNewMonomer( char **monomer, char **newMonomer,
                     long monoLength, long matches )
{
    int i;
    int pos = 0;
    /*First letter always stays*/
    printf( "New monomer length is %ld\n", monoLength );
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

void tallyMonomer( char *monomer, long monoLength )
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
                min = counts[j];
            }
        }
    }
    max = counts[0];
    for( i = 1; i < 26; i++ )
    {
        if( counts[i] > max )
        {
            max = counts[i];
        }
        if( ( counts[i] !=0 ) && ( counts[i] < min ) )
        {
            min = counts[i];
        }
    }
    printf( "Min is %ld, max is %ld\nDifference is %ld\n", min, max, max-min );
    free( counts );
}

void pairCycles( char **monomer, long monoLength, char **pairs,
                 int pairNum, int cycles )
{
    int i, row, col;
    long matches = 0;
    char **newMonomer;
    for( i=0; i < monoLength-2; i++ )
    { /*Reduced by 2, 1 for looking one ahead, the other for the terminator
        character that doesn't need to be considered*/
        row = (int)( monomer[0][i] ) - 65;
        col = (int)( monomer[0][i+1] ) - 65;
        if( pairs[row][col] != 0 )
        {/*If pairs array value is zero, no pair exists*/
            ++matches;
            monomer[1][i] = pairs[row][col];
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
/*        tallyMonomer( monomer[0], monoLength );*/
        free( newMonomer[0] );
        free( newMonomer[1] );
        free( newMonomer );
        free( monomer[0] );
        free( monomer[1] );
        free( monomer );
    }
}


int readFile( FILE* polyFilePtr )
{
    long monomerLength = 0;
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

    pairs = (char**)calloc( 26, sizeof( char* ) );
    for( i=0; i < 26; i++ )
    {
        pairs[i] = (char*)calloc( 26, sizeof( char ) );
    }
    /*Creates a 2D char array to hold the char pairs and then their outcome*/

    fillPairs( polyFilePtr, pairs, pairNum );

    fclose( polyFilePtr );

    pairCycles( monomer, monomerLength, pairs, pairNum, cycles );

    for( i=0; i<26; i++ )
    {
        free( pairs[i] );
    }
    free( pairs );

    return pairNum;
}
