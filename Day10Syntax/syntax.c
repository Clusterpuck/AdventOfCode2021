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
            }
                break;
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
        if( openCloseCount[i] < 0 )
        {
            sum += ( openCloseCount[i] * syntaxScore[i] );
        }
        openCloseCount[i] = 0;
    }
    printf("\n");

    return sum;
}


int scoreCorrupt( char** fileData, int lines )
{
    int i, j, length;
    int* openCloseCount = (int*)calloc( 6, sizeof(int) );
    int sum = 0;
    /*( count at 0 [ count at 1 { count at 2 < count at 3 >
 *      4 is opens, 5 is closes*/

    for( i=0; i < lines; i++ )
    {
        length = strcspn( fileData[i], "\n" );
        for( j=0; j < ( length ); j++ )
        {
            openCloseChoice( fileData[i][j], openCloseCount );
        }
        if( openCloseCount[4] != openCloseCount[5] )
        {
            sum += scoreLine( openCloseCount );
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
