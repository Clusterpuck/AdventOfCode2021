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

void fillPairs( FILE* polyFilePtr, long ***pairs, int pairNum )
{
/*First data point in i j ref is tally of that pair. Next is to indicate
 *which pairs to add to after subtracting from current.*/
    int i;
    char tempA, tempB, tempC;
    /*Additional pairs therefore are tempA and tempC and tempC and tempB*/
    fscanf( polyFilePtr, "\n%c%c -> %c\n",
            &tempA, &tempB, &tempC );

    pairs[( (long)(tempA-65) )][( (long)(tempB-65) )][1] = (long)(tempC-65 );

    for( i=1; i < pairNum; i++ )
    {
        fscanf( polyFilePtr, "%c%c -> %c\n",
                &tempA, &tempB, &tempC );
        pairs[( (long)(tempA-65) )][ (long)(tempB-65)][1] = (long)(tempC-65);
    }
}

void copyThreeDLong( long ***oldArray, long ***newArray,
                     int rows, int cols, int blocks )
{
    int i, j, k;
    for( i=0; i < rows; i++ )
    {
        for( j=0; j < rows; j++ )
        {
            for( k=0; k < blocks; k++ )
            {
                newArray[i][j][k] = oldArray[i][j][k];
            }
        }
    }
    printf( "\n***New Array***\n" );
    printThreeDLongArray( newArray, rows, cols, blocks );
    printf( "\n***Old Array***\n" );
    printThreeDLongArray( oldArray, rows, cols, blocks );

}

void pairCycles( long*** pairs, int cycles, int firstLetter )
{
    int i, j;
    long tally, insert;
    long ***newPairs;
    printf("\n**** CYCLE %d****\n", cycles );
    tallyMonomer( pairs, firstLetter );
    if( cycles < NUM_CYCLES )
    {
        callocThreeDLong( &newPairs, ALPHA_NUM, ALPHA_NUM, 2 );
        copyThreeDLong( pairs, newPairs, ALPHA_NUM, ALPHA_NUM, 2 );
        for( i=0; i < ALPHA_NUM; i++ )
        {
            for( j=0; j < ALPHA_NUM; j++)
            {
                tally = pairs[i][j][0];
                if( tally != 0 )
                {
                    insert = pairs[i][j][1];
                    newPairs[i][j][0] = 0;
                    newPairs[insert][j][0] += tally;
                    newPairs[i][insert][0] += tally;
                    printf( "Started with %ld pairs of %c%c\t"
                        "From %ld pairs to %ld pairs of %c%c and \t"
                        "From %ld pairs to %ld pairs of %c%c\n",
                        tally, (char)(i+65), (char)(j+65),
                        pairs[i][insert][0], newPairs[i][insert][0],
                        (char)(i+65), (char)(insert+65),
                        pairs[insert][j][0], newPairs[insert][j][0],
                        (char)(insert+65), (char)(j+65) );
                }
            }
        }
        freeThreeDLong( pairs, ALPHA_NUM, ALPHA_NUM );
        ++cycles;
        pairCycles( newPairs, cycles, firstLetter );
    }
    else
    {
        tallyMonomer( pairs, firstLetter );
        freeThreeDLong( pairs, ALPHA_NUM, ALPHA_NUM );
    }
}

void tallyMonomer( long ***pairs, int firstLetter )
{
    int i, j;
    long *counts = (long*)calloc( ALPHA_NUM, sizeof( long ) );
    long max, min;
    ++counts[( firstLetter-65 )];

    for( i=0; i < ALPHA_NUM; i++ )
    {
        for( j=0; j < ALPHA_NUM; j++ )
        {
            if( pairs[i][j][0] != 0 )
            {
                printf( "Tallying pair %c%c occuring %ld times**\t",
                        (char)(i+65), (char)(j+65), pairs[i][j][0] );
                counts[j] += pairs[i][j][0];
                printf( "%c tally is now %ld\n",
                        (char)(j+65), counts[j] );
            }
        }
    }
    max = counts[0];
    min = 10000;
    for( i = 1; i < ALPHA_NUM; i++ )
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

void callocThreeDLong( long ****array, int rows, int cols, int blocks )
{
    int i, j;
    long ***newArray;
    newArray= (long***)calloc( rows, sizeof( long** ) );
    for( i=0; i < rows; i++ )
    {
        newArray[i] = (long**)calloc( cols, sizeof( long* ) );
        for( j=0; j< cols; j++ )
        {
            newArray[i][j] = (long*)calloc( blocks, sizeof( long ) );
        }
    }
    (*array) = newArray;
}

void freeThreeDLong( long*** array, int rows, int cols)
{
    int i, j;
    for( i=0; i < rows; i++ )
    {
        for( j=0; j <cols; j++ )
        {
            free( array[i][j] );
        }
        free( array[j] );
    }
    free( array );
}

int readFile( FILE* polyFilePtr )
{
    long monomerLength = 0;
    int pairNum = 0;
    char *monomer;
    int i;
    int cycles = 0;
    int firstLetter;
    long ***pairs; /*needs to be long for large tally*/

    callocThreeDLong( &pairs, ALPHA_NUM, ALPHA_NUM, 2 );
  /*Creates a 3D long array to hold the count of a pair in it's relevent
 *    row column reference (adjust by 65) i.e. AA in 0,0 AB in 0,1 etc*/
    /*This array stores the tally of the pair and the reference to the
 *    letter inserted between*/
    fileSize( polyFilePtr, &monomerLength, &pairNum );

    monomer = (char*)calloc( 64, sizeof( char ) );
    /*Monomer is 2D to hold the insertions in the second line*/

    fgets( monomer, monomerLength, polyFilePtr );
    firstLetter = monomer[0];
    /*fill starting pairs*/
    for( i=0; i < (strlen(monomer)-1); i++ )
    {
        ++( pairs[monomer[i]-65][monomer[i+1]-65][0] );
    }
    free( monomer );
    fillPairs( polyFilePtr, pairs, pairNum );
    fclose( polyFilePtr );

    pairCycles( pairs, cycles, firstLetter );

    return pairNum;
}
