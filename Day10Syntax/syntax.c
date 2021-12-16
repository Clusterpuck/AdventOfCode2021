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
#include "linkedlist.h"

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

int closeChoice( char openBracket, char closeBracket )
{
    int corrupt = FALSE;
    switch( openBracket  )
    {
        case '(':
        {
            if( closeBracket != ')' )
                corrupt = TRUE;
            break;
        }
        case '[':
        {
            if( closeBracket != ']' )
                corrupt = TRUE;
            break;
        }
        case '{':
        {
            if( closeBracket != '}' )
                corrupt = TRUE;
            break;
        }
        case '<':
        {
            if( closeBracket != '>' )
                corrupt = TRUE;
            break;
        }
        default:
            printf( "Non standard char found %c\n", closeBracket);
    }
    return corrupt;
}

int scoreLine( char badBracket )
{
    int score = 0;

    switch ( badBracket )
    {
        case ')':
            score = 3;
            break;
        case ']':
            score = 57;
            break;
        case '}':
            score = 1197;
            break;
        case '>':
            score = 25137;
            break;
        default:
            printf( "Non-standard error found\n" );
    }

    return score;
}


int scoreCorrupt( char** fileData, int lines )
{
    int i, j, length;
    int corrupt;
    int sum = 0;
    char* testChar;
    LinkedList *braceList;
    /*( count at 0 [ count at 1 { count at 2 < count at 3 >
 *      4 is opens, 5 is closes*/
    for( i=0; i < lines; i++ )
    {
        j=0;
        corrupt = FALSE;
        braceList = createLinkedList();
        length = strcspn( fileData[i], "\n" );
        while( ( j < length ) && !corrupt )
        {
            if( fileData[i][j] == '[' || fileData[i][j] == '(' ||
                fileData[i][j] == '{' || fileData[i][j] == '<' )
            {
                insertLast( braceList, &fileData[i][j] );
            }
            else
            {
                testChar = (char*)( removeLast( braceList ) );
                corrupt = closeChoice( (*testChar), fileData[i][j] );
                /*Only open braces stored in list, close braces remove them*/
                if( corrupt )
                {
                    sum += scoreLine( fileData[i][j] );
                    printf( " sum is %d from %c on line %d\n", sum, fileData[i][j], i );
                }
            }
            j++;
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
