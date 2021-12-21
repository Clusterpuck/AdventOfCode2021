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
                Until all paths come to the END
                or no viable options left i.e. only small caves left that
                have been visited
                Count number of times node END reached*/

node* makeNode( char* nodeName )
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
    node* tempNode;
    char* tempName;
    int match = FALSE;

    while( listNode != NULL && !match )
    {
        tempNode = (node*)( listNode->data );
        tempName = tempNode->vertix;
        if( !(strcmp( tempName, nodeName ) ) )
        {/*strcmp returns 0 for match i.e. FALSE*/
            match = TRUE;
        }
        else
        {
            listNode = listNode->next;
        }
    }
    if( listNode == NULL )
        tempNode = NULL;

    return tempNode;
}



LinkedList* createNodeList( char*** nodeData, int lines )
{
    node *nodeOne, *nodeTwo;
    LinkedList *nodeList = createLinkedList();
    int i;
    for( i=0; i < lines; i++ )
    {
        nodeOne = searchList( nodeData[i][0], nodeList );
        nodeTwo = searchList( nodeData[i][1], nodeList );
        if( nodeOne == NULL )
        {
            nodeOne = makeNode( nodeData[i][0] );
        }
        if( nodeTwo == NULL )
        {
            nodeTwo = makeNode( nodeData[i][1] );
        }

        if( ( !strcmp( nodeOne->vertix, "start" ) ) ||
            ( !strcmp( nodeTwo->vertix, "end" ) ) )
        {/*Need slight change so head is at start*/
            insertFirst( nodeOne->connections, nodeTwo );
        }
        else if( ( !strcmp( nodeTwo->vertix, "start" ) ) ||
               ( !strcmp( nodeOne->vertix, "end" ) ) )
        {
            insertFirst( nodeTwo->connections, nodeOne );
        }
        else
        {
            insertFirst( nodeOne->connections, nodeTwo );
            insertFirst( nodeTwo->connections, nodeOne );
        }
    }
}


void traverseNodes( node *currentNode )
{
    if( 
    
    


int readFile( FILE* pathsFilePtr )
{
    int pathNum = 0;
    int lines = -1;

    char*** nodeData;
    char* readLine;
    int i;
    LinkedList* nodeList;

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

    nodeList = createNodeList( nodeData, lines );

    traverseNodes( nodeList );
    
    return pathNum;
}


