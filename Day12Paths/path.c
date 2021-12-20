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
#include "utility.h"
#include "path.h"

/*read in 2d string array of connected nodes. get size to make array of node structs
 *create new node for each unique string, and/or add connection to the LL
  Assuming connections aren't given more than once i.e. no he-DX and DX-he
  store all nodes in array of node structs

  Path finding: At each node try every direction
                recursion?
                Unit all paths come to the END
                or no viable options left i.e. only small caves left that
                have been visited
                Count number of times node END reached*/

node* makeNode( char* nodeName, node* firstConnect )
{
    node* newNode  = (node*)malloc( sizeof( node ) );
    newNode->connections = createLinkedList();
    newNode->vertix = nodeName;
    newNode->visited = FALSE;
    if( nodeName[0] > 64 && nodeName[0] < 91 )
    {
        newNode->big = TRUE;
    }
    else
    {
        newNode->big = FALSE;
    }
    insertFirst( newNode->connections, firstConnect );

    return newNode;
}




void fileSize( FILE* pathsFilePtr, int* lines )
{
    char *tempString = (char*)malloc( sizeof(char) * BIG_DATA );
    char *endTest = (char*)malloc( sizeof(char) * SMALL_DATA );

    do
    {
        endTest = fgets( tempString, BIG_DATA, pathsFilePtr );
        ++(*lines);

    }while( endTest != NULL );

    rewind( pathsFilePtr );
    free( endTest );
    free( tempString );
}

node* searchList( char* nodeName, LinkedList* nodeList )
{
    LiLiNode* listNode = nodeList->head;
    node* tempNode = (node*)( listNode->data );
    char* tempName = tempNode->vertix;
    int match = FALSE;
    
    while( listNode != NULL && !match )
    {
        if( !(strcmp( tempName, nodeName ) ) )
        {/*strcmp returns 0 for match i.e. FALSE*/
        

    return tempNode;

void createNodeList( int** nodeData, int lines )
{
    LinkedList *nodeList = createLinkedList();
    int i;
    for( i=0; i < lines; i++ )
    {
        



int readFile( FILE* pathsFilePtr )
{
    int pathNum = 0;
    int lines = -1;

    char*** nodeData;
    char* readLine;
    int i;

    fileSize( pathsFilePtr, &lines );

    nodeData = (char***)malloc( sizeof( char** ) * lines );

    for( i=0; i < lines; i++ )
    {
        nodeData[i] = (char**)malloc( sizeof( char* ) * 2 );
        readLine = (char*)malloc( sizeof( char ) * SMALL_DATA );
        fgets( readLine, SMALL_DATA, pathsFilePtr );
        nodeData[i][0] = strtok( readLine, "-" );
        nodeData[i][1] = strtok( NULL , "\n" );
    }

    printTwoDStringArray( nodeData, lines, 2 );

    return pathNum;
}


