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

void sortList( LinkedList *scoreList )
{
    void *tempData = scoreList->head->data;
    LiLiNode *nodeOne = scoreList->head;
    LiLiNode *nodetwo = scoreList->head->next;
    int tempScoreOne, tempScoretwo;
    void* minPtr = NULL;
    int size = scoreList->size;
    
    while( tempNodeOne != NULL )
    {
        while( tempNodeTwo != NULL )
        minIndex = i;
        for( j= i+1; j < size; j++ )
        {
            

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

void insertScore( LinkedList *braceList, LinkedList *insertScores )
{
    int size = braceList->size;
    int* score = (int*)malloc( sizeof(int) );
    char* openChar;
    int i;

    for( i = 0; i < size; i++ )
    {
        openChar = (char*)removeLast( braceList );
        switch( *openChar )
        {
            case '(':
            {
                (*score) *= 5;
                (*score) += 1;
                break;
            }
            case ']':
            {
                (*score) *= 5;
                (*score) += 2;
                break;
            }
            case '}':
            {
                (*score) *= 5;
                (*score) += 3;
                break;
            }
            case '>':
            {
                (*score) *= 5;
                (*score) += 4;
                break;
            }
        }
    }
    insertFirst( insertScores, score );
}


int scoreCorrupt( char** fileData, int lines )
{
    int i, j, length, corrupt;
    int sum = 0;
    char* testChar;
    LinkedList *braceList;
    LinkedList *insertScores = createLinkedList();

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
            if( ( j==length ) && !corrupt )
            {/*braceList should be list of unclosed brackets
               so just need to identify correct closing bracket order*/
                if( braceList->size != 0 )
                {
                    insertScore( braceList, insertScores );
                }
            }

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
