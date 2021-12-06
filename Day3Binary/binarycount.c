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

void printTwoDArray( char** array, int row, int col )
{
    int i, j;
    for( i = 0; i < row; i++ )
    {
        for( j=0; j<col; j++ )
        {
            printf(" %c,", array[i][j] );
        }
        printf("\n");
    }
}

void fillLifeArray( char **lifeArray, int row, int col, FILE* binfilePtr )
{
    int i = 0;
    int j;
    int done = FALSE;
    char* input = (char*)malloc( sizeof( char ) * col );

    while( !done )
    {
        input = fgets( input, 20, binfilePtr );
        if( input == NULL )
        {
            done = TRUE;
        }
        else
        {
            for( j = 0; j < col; j++ )
            {
                lifeArray[i][j] = input[j];
            }
            ++i;
        }
    }
    printTwoDArray( lifeArray, row, col );

}

void fillMatches( char **lifeArray, char *filterArray, int colIndex, int row,
                    char match )
{
    int i;
    for( i = 0; i < row; i++ )
    {
        if( lifeArray[i][colIndex] != match )
        {
            filterArray[i] = 'N';
        }
    }
}

int binToInt( char *binArray, int length )
{
    int num  = 0;
    int i;
    for( i = length; i >= 0; i-- )
    {
        num += ( binArray[i] - 48 ) * pow( 2, length-i-1 );
    }
    return num;
}

void filterCOTwo( char **lifeArray, char* filterArray,
                int row, int colIndex, int length )
{
    int onesCount = 0;
    int i, j;
    int newRows;
    int currentMatches = 0;
    char match;
    char *coTwo = (char*)( malloc( sizeof( char ) * length )  );
    int coInt = 0;
    for( i = 0; i < row; i++ )
    {
        if( filterArray[i] == 'Y' )
        {
            ++currentMatches;
        }
        if( lifeArray[i][colIndex] == '1' && filterArray[i] == 'Y' )
        {
            ++onesCount;
        }
    }
    if( onesCount <= ( currentMatches/2 ) )
    {
        newRows = onesCount;
        match = '1';
    }
    else
    {
        newRows = currentMatches - onesCount;
        match = '0';
    }
    fillMatches( lifeArray, filterArray, colIndex, row, match );

    if( newRows != 1 )
    {
        ++colIndex;
        filterCOTwo( lifeArray, filterArray, row, colIndex, length );
    }
    else
    {
        for( i = 0; i < row; i++ )
        {
            if( filterArray[i] == 'Y' )
            {
                for( j=0; j < length; j++ )
                {
                    coTwo[j] = lifeArray[i][j];
                    printf( "%c, ", lifeArray[i][j] );
                }
            }
        }
        coInt = binToInt( coTwo, length );
        printf( "Decimal of oxygen is %d\n", coInt );
    }
}



void filterOx( char **lifeArray, char* filterArray,
                int row, int colIndex, int length )
{
    int onesCount = 0;
    int i, j;
    int newRows;
    int currentMatches = 0;
    char match;
    char *oxygen = (char*)( malloc( sizeof( char ) * length )  );
    int oxInt = 0;
    for( i = 0; i < row; i++ )
    {
        if( filterArray[i] == 'Y' )
        {
            ++currentMatches;
        }
        if( lifeArray[i][colIndex] == '1' && filterArray[i] == 'Y' )
        {
            ++onesCount;
        }
    }
    if( onesCount >= ( currentMatches/2 ) )
    {
        newRows = onesCount;
        match = '1';
    }
    else
    {
        newRows = currentMatches - onesCount;
        match = '0';
    }
    fillMatches( lifeArray, filterArray, colIndex, row, match );

    if( newRows != 1 )
    {
        ++colIndex;
        filterOx( lifeArray, filterArray, row, colIndex, length );
    }
    else
    {
        for( i = 0; i < row; i++ )
        {
            if( filterArray[i] == 'Y' )
            {
                for( j=0; j < length; j++ )
                {
                    oxygen[j] = lifeArray[i][j];
                    printf( "%c, ", lifeArray[i][j] );
                }
            }
        }
        oxInt = binToInt( oxygen, length );
        printf( "Decimal of oxygen is %d\n", oxInt );
    }
}

void myNotOperator( int *binArray, int length )
{
    int i;
    for( i=0; i < length; i++ )
    {
        if( binArray[i] == 0 )
        {
            binArray[i] = 1;
        }
        else
        {
            binArray[i] = 0;
        }
    }
}


int readPower( FILE* binfilePtr )
{
    int done = FALSE;
    int countAll = 0;
    int *oneCounts;
    int i;
    int length = 0;
    int gamma = 0;
    int epsilon = 0;
    char **lifeArray;
    char *filterArray;

    char *input = (char*)malloc( sizeof( char ) * 20 );
    oneCounts = (int*)calloc( 20, sizeof(int) );

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

    lifeArray = (char**)malloc( sizeof(char*)*countAll );
    for( i=0; i< countAll; ++i)
    {
        lifeArray[i] = (char*)malloc( sizeof(char)*length );
    }
    filterArray = (char*)malloc( sizeof(char)*countAll );
    for( i=0; i< countAll; i++ )
    {
        filterArray[i] = 'Y';
        /*Starts with all index in yes position,
 *          to be changed to all but one no*/
    }

    rewind( binfilePtr );

    fillLifeArray( lifeArray, countAll, length, binfilePtr );
    filterOx( lifeArray, filterArray, countAll, 0, length );
    filterCOTwo( lifeArray, filterArray, countAll, 0, length );

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
    }
    gamma = binToInt( oneCounts, length );
    myNotOperator( oneCounts, length );
    epsilon = binToInt( oneCounts, length );

    return gamma*epsilon;
}


int main(int argc, char * argv[])
{
    char *binfile = "input.txt";
    FILE *binfilePtr = NULL;
    int power = 0;

    binfilePtr = fopen( binfile, "r" );

    if( binfilePtr == NULL )
    {
        perror( "Error opening file" );
    }
    else
    {
        power = readPower( binfilePtr );
    }


    printf( "The power is %d\n", power );

    return 0;
}
