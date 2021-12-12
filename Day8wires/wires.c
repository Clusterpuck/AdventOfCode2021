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
#include "wires.h"
#include "utility.h"



void fiveLengthDecode( char** decoderString, char* inSeg, int length )
{
    int i, j;
    int match = 0;

    /*If a 5 length includes both characters from 1, then it is 3*/
    for( i = 0; i < length; i++)
    {
        if( decoderString[1][0] == inSeg[i] )
        {
            ++match;
        }
        if( decoderString[1][1] == inSeg[i] )
        {
            ++match;
        }
    }
    if( match == 2)
    {
        strcpy( decoderString[3], inSeg );
    }
    if( match == 1 )
    { /*If a 5 length contains only 1 character from 1,
        it is either 2 or 5, can use 4 to distinguish
        if contains exactly 2 characters from 4 it is 2
        if contains exactly 3 characters from 4 it is 5*/
        match = 0;
        for( i = 0; i < length; i++ )
        {
            for( j=0; j < 4; j++ )
            {
                if( decoderString[4][j] == inSeg[i] )
                {
                    ++match;
                }
            }
        }
        if( match == 2 )
        {
            strcpy( decoderString[2], inSeg );
        }
        if( match == 3 )
        {
            strcpy( decoderString[5], inSeg );
        }
    }
}


void sixLengthDecode( char** decoderString, char* inSeg, int length )
{
    int match = 0;
    int i, j;

    /*If a 6 length includes only 1 character from 1, then it is a 6 */
    for( i=0; i < length; i++ )
    {
        if( decoderString[1][0] == inSeg[i] ||
            decoderString[1][1] == inSeg[i] )
        {
            ++match;
        }
    }
    if( match == 1 )
    {
        strcpy( decoderString[6], inSeg );
    }
    if( match == 2 )
    {/*If a 6 length has 2 matches it is either 9 or 0
        can use 4 to distinguish*/
        match = 0;
        for( i=0; i < length; i++ )
        {
            for( j=0; j < 4; j++ )
            {
                if( decoderString[4][j] == inSeg[i] )
                {   /*Need to match all 4 values of 4 to confirm 9*/
                    ++match;
                }
            }
        }
        if( match == 4 )
        {
            strcpy( decoderString[9], inSeg );
        }
        else
        {
            strcpy( decoderString[0], inSeg );
        }
    }
}


void deepDecode( char** inArray, char** decoderString )
{
    int length, i;
    for( i = 0; i < NUMBERS; i++ )
    {
        length = strlen( inArray[i] );
        if( length == 5 )
        {
            fiveLengthDecode( decoderString, inArray[i], length );
        }
        if( length == 6 )
        {
            sixLengthDecode( decoderString, inArray[i], length );
        }
    }
}

int translate( char **decoderString, char* output )
{
    int dec = 1000;
    int match = 0;
    int sum = 0;
    int length, i, j, k;
    char *outSeg = (char*)malloc( sizeof(char) * SMALL_DATA );
    outSeg = strtok( output, " \n" );
    while( outSeg != NULL )
    {
        length = strlen( outSeg );
        for( i=0; i < NUMBERS; i++ )
        {
            match = 0;
            if( length == strlen( decoderString[i] ) )
            {   /*Only checks string if length matches*/
                for( j=0; j < length; j++ )
                {
                    for( k=0; k < length; k++ )
                    {
                        if( outSeg[j] == decoderString[i][k] )
                        {
                            ++match;
                        }
                    }
                }
                if( match == length )
                { /*all letters from decoderString have been found*/
                    sum += ( i * dec );
                    dec = dec/10;
                }
            }
        }
        outSeg = strtok( NULL, " \n" );
    }

    free( outSeg );
    return sum;
}



int decode( char *input, char *output )
{
    int length, i, digit;
    char *inSeg = (char*)malloc( sizeof(char) * SMALL_DATA );
    char **decoderString = (char**)malloc( sizeof(char*) * NUMBERS );
    char **inArray = (char**)malloc( sizeof(char*) * NUMBERS );
    for( i = 0; i < NUMBERS; i++ )
    { /*Holds associated string for number element 0 for 0 etc*/
        decoderString[i] = (char*)malloc( sizeof(char) * SMALL_DATA );
    }

    inSeg = strtok( input, " \n" );
    i = 0;
    while( inSeg != NULL )
    {
        inArray[i] = inSeg;
        i++;
        length = strlen( inSeg );
        switch( length )
        {
            case 2:
            {
                strcpy( decoderString[1], inSeg );
                break;
            }
            case 4:
            {
                strcpy( decoderString[4], inSeg );
                break;
            }
            case 3:
            {
                strcpy( decoderString[7], inSeg );
                break;
            }
            case 7:
            {
                strcpy( decoderString[8], inSeg );
                break;
            }
            default:
            {
                break;
            }
        }
        inSeg = strtok( NULL, " \n" );
    }

    deepDecode( inArray, decoderString );

    digit = translate( decoderString, output );

    free( inArray );
    for( i = 0; i < NUMBERS; i++ )
    {
        free( decoderString[i] );
    }
    free( decoderString );
    free( inSeg );

    return digit;

}


int getDigits( FILE* wireFilePtr )
{
    int digits = 0;
    int sumdigits = 0;
    int count = 0;
    char* readLine = (char*)malloc( sizeof(char) * BIG_DATA );
    char* output = (char*)malloc( sizeof(char) * BIG_DATA );
    char* input = (char*)malloc( sizeof(char) * BIG_DATA );
    char* stringSeg = (char*)malloc( sizeof(char) * SMALL_DATA );
    char* endCheck;

    endCheck = fgets( readLine, BIG_DATA, wireFilePtr );

    while( endCheck != NULL )
    {

        input = strtok( readLine, "|" );
        output = strtok( NULL, "|" );
        sumdigits += decode( input, output );
        stringSeg = strtok( output, " \n" );

        while( stringSeg != NULL )
        {
            digits = strlen( stringSeg );
            if( ( digits == 2 ) || ( digits == 4 ) ||
                ( digits == 3 ) || ( digits == 7 ) )
            {
                ++count;
            }
            stringSeg = strtok( NULL, " \n" );
        }
        endCheck = fgets( readLine, BIG_DATA, wireFilePtr );
    }

    free( readLine );
    free( stringSeg );
    fclose( wireFilePtr );

    return sumdigits;
}

int readFile( FILE* wireFilePtr )
{
    int digits = 0;
    digits = getDigits( wireFilePtr );
    return digits;
}
