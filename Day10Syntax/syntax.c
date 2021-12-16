/******************************************************************************
 * Filename: syntax.c                                                         *
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
#include "syntax.h"
#include "utility.h"

int fileSize( FILE* syntaxFilePtr )
{
    int count = 0;
    char *tempString = (char*)malloc( sizeof(char) * BIG_DATA );
    char *endTest = (char*)malloc( sizeof(char) * SMALL_DATA );
    
    endTest = fgets( tempString, BIG_DATA, syntaxFilePtr );

    while( endTest != NULL )
    {
        endTest = fgets( tempString, BIG_DATA, syntaxFilePtr );
        ++count;
    }
    free(endTest);
    free(tempString);

    rewind( syntaxFilePtr );
    return count;

}

void openCloseChoice( char bracket, int* openCloseCount )
{
    switch( bracket )
    {
            case '(':
            {
                ++( openCloseCount[0] );
                ++( openCloseCount[4] );
                break;
            }
            case ')':
            {
                --( openCloseCount[0] );
                ++( openCloseCount[5] );
                break;
            }
            case '[':
            {
                ++( openCloseCount[1] );
                ++( openCloseCount[4] );
                break;
            }
            case ']':
            {
                --( openCloseCount[1] );
                ++( openCloseCount[5] );
                break;
            }
            case '{':       
            {
                ++( openCloseCount[2] );
                ++( openCloseCount[4] );
                break;
            }
            case '}':
            {
                --( openCloseCount[2] );
                ++( openCloseCount[5] );
                break;
            }
            case '<':
            {
                ++( openCloseCount[3] );
                ++( openCloseCount[4] );
                break;
            }
            case '>':
            {
                --( openCloseCount[3] );
                ++( openCloseCount[5] );
                break;
            }
            default:
                printf( "Non standard char found %c\n", bracket);
    }
}

int scoreLine( int* openCloseCount )
{
    int i;
    int sum = 0;
    int syntaxScore[] = { 3, 57, 1197, 25137 };

    for( i=0; i < 4; i++ )
    {
        printf( "%d ", openCloseCount[i] );
        sum += ( openCloseCount[i] * syntaxScore[i] );
        openCloseCount[i] = 0;
    }
    printf("\n");


    return sum;
}


int scoreCorrupt( char** fileData, int lines )
{
    int i, length, j;
    int opens = 0;
    int* openCloseCount = (int*)calloc( 6, sizeof(int) );
    int sum = 0;
    /*( count at 0 [ count at 1 { count at 2 < count at 3 >
 *      4 is opens, 5 is closes*/

    for( i=0; i < lines; i++ )
    {
        j=0;
        opens = 0;
        length = strcspn( fileData[i], "\n" );
        while( ( opens >= 0 ) && ( j < length ) )
        {
            if( fileData[i][j] == '(' || fileData[i][j] == '[' ||
                fileData[i][j] == '{' || fileData[i][j] == '<' )
            {
                /*Need to test if any unique bracket closes more than it opens*/
                ++opens;
            }
            else
            {
                --opens;
            }
            ++j;
            /*
            openCloseChoice( fileData[i][j], openCloseCount );*/
        }
        printf( "Line %d of length %d has %d opens\n", 
                i, length, opens );
                    
/*
        if( openCloseCount[4] != openCloseCount[5] )
        {
            sum += scoreLine( openCloseCount );
        }*/
        for( j=0; j < 6; j++ )
        {
            openCloseCount[j] = 0;
        }
    }

    return sum;
}

int readFile( FILE* syntaxFilePtr )
{
    int lines, corrupt;
    int i;
    char **fileData;  
  
    lines = fileSize( syntaxFilePtr ); 
    fileData = (char**)malloc( sizeof( char* ) * lines );
    for( i=0; i < lines; i++ )
    {
        fileData[i] = (char*)malloc( sizeof( char ) * BIG_DATA );
        fgets( fileData[i], BIG_DATA, syntaxFilePtr );
    }

    corrupt = scoreCorrupt( fileData, lines ); 
    

    return corrupt;
}   
