/******************************************************************************
 * Filename:  binarycount.c                                                   *
 * Author: Nicholas Wright 12880155                                           *
 * Purpose:                                                                   *
 * Assertions- PRE:                                                           *
 *            POST:                                                           *
 * Date Written:                                                              *
 * Edited By:       Date Edited:                                              *
 * ***************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>


#define FALSE 0
#define TRUE !FALSE

int binToInt( int *binArray, int length )
{
    int num  = 0;
    int i;
    for( i = length; i >= 0; i-- )
    {
        num += ( binArray[i] ) * pow( 2, length-i );
    }
    return num;
}

int readPower( FILE* binfilePtr )
{
    int done = FALSE;
    unsigned int power = 0;
    int countAll = 0;
    int oneCounts[20];
    int i;
    int length = 0;

    char *input = (char*)malloc( sizeof( char ) * 20 );

    while( !done )
    {
        input = fgets( input, 20, binfilePtr );
        if( input == NULL )
        {
            done = TRUE;
        }
        else
        {
            length = strlen( input )-1; /*Adjust for new line character*/
            ++countAll;
            for( i=0; i < length; i++ )
            {
                if( input[i] == '1' )
                {
                    ++( oneCounts[i] );
                }
            }
        }
    }
    free( input );
    for( i=0; i<length; i++ )
    {
        if( ( countAll/2 ) > oneCounts[i] )
        {
            oneCounts[i] = 0;
        }
        else
        {
            oneCounts[i] = 1;
        }
        printf( " %d, ", oneCounts[i] );
    }
    power = binToInt( oneCounts, length );

    return power;
}


int main(int argc, char * argv[])
{
    char *binfile = "input.txt";
    FILE *binfilePtr = NULL;
    int power = 0;
    int notPower = 0;

    binfilePtr = fopen( binfile, "r" );

    if( binfilePtr == NULL )
    {
        perror( "Error opening file" );
    }
    else
    {
        power = readPower( binfilePtr );
    }

    fclose( binfilePtr );

    printf( "The power is %d\n", power );
    notPower = (~power);
    printf( "The not power is %d\n", notPower );

    return 0;
}
