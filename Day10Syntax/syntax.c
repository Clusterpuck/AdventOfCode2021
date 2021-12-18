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


/*Determines number of lines in file*/
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


/*Determines if open close bracket matches expected close bracket
 * Returns boolean */
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



/*Sorts the linked list from smallest to largest data value*/
void sortList( LinkedList *scoreList )
{
    void *tempPtr;
    LiLiNode *nodeOne = scoreList->head;
    LiLiNode *nodeTwo = scoreList->head->next;
    int *dataOne, *dataTwo;

    while( nodeTwo != NULL )
    {

        while( nodeTwo != NULL )
        {
            dataOne = (int*)( nodeOne->data );
            dataTwo = (int*)( nodeTwo->data );
            if( ( *dataTwo ) < (*dataOne) )
            {
                tempPtr = nodeOne->data;
                nodeOne->data = nodeTwo->data;
                nodeTwo->data = tempPtr;
            }
            nodeTwo = nodeTwo->next;
        }
        nodeOne = nodeOne->next;
        nodeTwo = nodeOne->next;
    }
}



/*Determines score based on the bad bracket found*/
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



void printChar( void *data )
{
    char* temp = (char*)data;
    printf( "%c ", *temp );
}


void printScore( void *data )
{
    long* score = (long*)(data);
    printf( "%ld ", *score );
}

/*Totals the score for a line that was incomplete, saves into a linked list*/
void insertScore( LinkedList *braceList, LinkedList *insertScores )
{
    int size = braceList->size;
    long* score = (long*)calloc( 1, sizeof(long) );
    char* openChar;
    int i;

    for( i = 0; i < size; i++ )
    {
        (*score) *= 5;
        openChar = (char*)removeLast( braceList );
        switch( *openChar )
        {
            case '(':
            {
                (*score) += 1;
                break;
            }
            case '[':
            {
                (*score) += 2;
                break;
            }
            case '{':
            {
                (*score) += 3;
                break;
            }
            case '<':
            {
                (*score) += 4;
                break;
            }
        }
    }
    insertFirst( insertScores, score );
}


/*Moves to the mid point of a sorted linked list and prints the data value*/
void finalInsertScore( LinkedList *scores )
{
    int size = scores->size;
    int midSize = ( size/2 );
    int i;
    long *score;
    void* data;
    LiLiNode *scoreNode = scores->head;
    for( i=0; i < midSize; i++ )
    {
        scoreNode = scoreNode->next;
    }
    data = scoreNode->data;
    score = (long*)data;

    printf( "Mid score is %ld\n", *score );
    /* 184357871 is wrong  */
}



/*Creates a linked list for each line, filled only with open bracket
 * If the bracket is closed correctly it is removed from the list.
 * If it is not closed by the correct bracket, the list is no longer added
 * to and the corrupt score is calculated.
 * If the list still contains open brackets by the end of the read line
 * And is not corrupt, list is scored for incomplete.*/
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
       /* freeLinkedList( braceList, &free );*/
    }
    sortList( insertScores );
    finalInsertScore( insertScores );

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
