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

        if( ( !strcmp( nodeOne->vertix, "start" ) ) )
        {/*Ensures start is the first node, for easy access*/
            printf( "Inserting a start\n");
            insertFirst( nodeOne->connections, nodeTwo );
        }
        else if( !strcmp( nodeTwo->vertix, "end" ) )
        {
            insertLast( nodeOne->connections, nodeTwo );
        }
        else if( ( !strcmp( nodeTwo->vertix, "start" ) ) )
        {
            printf( "Inserting a start\n");
            insertFirst( nodeTwo->connections, nodeOne );
        }
        else if( !strcmp( nodeOne->vertix, "end" ) )
        {
            insertLast( nodeTwo->connections, nodeOne );
        }
        else
        {/*If neither is start or end, connections both ways can be made*/
            insertLast( nodeOne->connections, nodeTwo );
            insertLast( nodeTwo->connections, nodeOne );
        }
    }
    if( nodeList->head == NULL )
    {
        printf( "THe head is null\n");
    }
    return nodeList;
}

/*At this point all nodes are connected to other nodes, the connections
 *stored in a linked list.
  At each node, activate traverse nodes while the linked list node isn't null
  If end reached, add to counter then continue to next node*/
void traverseNodes( LiLiNode *currentNode, int *endCount )
{
    node *currentHub = (node*)( currentNode->data );
    LiLiNode *nextNodeLink = ( currentHub->connections->head );
    while( nextNodeLink != NULL )
    {
        if( !strcmp( currentHub->vertix, "end" ) )
        {
            ++(*endCount);
        }
        traverseNodes( nextNodeLink, endCount );
        nextNodeLink = nextNodeLink->next;
    }
}


int readFile( FILE* pathsFilePtr )
{
    int lines = -1;
    int endCount = 0;
    LiLiNode *startNode;
    node *testNode;

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

    startNode = nodeList->head;
    testNode = (node*)( startNode->data );
    printf( "Start node is called %s\n", testNode->vertix );
    traverseNodes( startNode, &endCount );

    return endCount;
}


