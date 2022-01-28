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
    newNode->visited = -1;
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
    {
        tempNode = NULL;
    }

    return tempNode;
}



LinkedList* createNodeList( char*** nodeData, int lines )
{
    node *nodeOne, *nodeTwo;
    int i;
    LinkedList *nodeList = createLinkedList();
    for( i=0; i < lines; i++ )
    {
        nodeOne = searchList( nodeData[i][0], nodeList );
        nodeTwo = searchList( nodeData[i][1], nodeList );
        if( nodeOne == NULL )
        {
            nodeOne = makeNode( nodeData[i][0] );
            insertFirst( nodeList, nodeOne );
        }
        if( nodeTwo == NULL )
        {
            nodeTwo = makeNode( nodeData[i][1] );
            insertFirst( nodeList, nodeTwo );
        }
        /*Adding relevent connections to new nodes*/
        if( ( !strcmp( nodeOne->vertix, "start" ) ) )
        {
            /*for a start, the connection for the start is not added
 *            to the other node as you cannot move to a start, just from*/
            insertFirst( nodeOne->connections, nodeTwo );
        }
        else if( !strcmp( nodeTwo->vertix, "start" ) )
        {
            insertFirst( nodeTwo->connections, nodeOne );
        }
        else if( ( !strcmp( nodeOne->vertix, "end" ) ) )
        {/*For an end connections cannot go from the end so other node
           isn't added to the end nodes list*/
            insertFirst( nodeTwo->connections, nodeOne );
        }
        else if( !strcmp( nodeTwo->vertix, "end" ) )
        {
            insertFirst( nodeOne->connections, nodeTwo );
        }
        else
        {/*If neither is start or end, connections both ways can be made*/
            insertFirst( nodeOne->connections, nodeTwo );
            insertFirst( nodeTwo->connections, nodeOne );
        }
    }

    return nodeList;
}

/*At this point all nodes are connected to other nodes, the connections
 *stored in a linked list.
  At each node, activate traverse nodes while the linked list node isn't null
  If end reached, add to counter then continue to next node*/
void resetVisited( LinkedList *nodeList )
{
    LiLiNode *listNode = nodeList->head;
    node* tempNode;
    LiLiNode *connectNode;
    while( listNode != NULL )
    {
        tempNode = (node*)( listNode->data );
        tempNode->visited = FALSE;
        connectNode = tempNode->connections->head;
        while( connectNode != NULL )
        {
            tempNode = (node*)( connectNode->data );
            tempNode->visited = FALSE;
            printf( "Setting %s to not visited\n", tempNode->vertix );
            connectNode = connectNode->next;
        }
        listNode = listNode->next;
    }
}


void traverseNodes( node *currentNode, int *endCount, int *path, 
                    LinkedList *nodeList )
{
    LiLiNode *nextNodeLink = ( currentNode->connections->head );
    node* nextNode;
    while( nextNodeLink != NULL )
    {
        printf( "Path number %d\n", (*path) );
        nextNode = (node*)(nextNodeLink->data);
        printf( "Connecting from %s to %s with visited number %d\n", 
                currentNode->vertix, nextNode->vertix, nextNode->visited );
        if( !strcmp( nextNode->vertix, "end" ) )
        {
            ++(*endCount);
        }
        if( ( nextNode->visited ) != (*path) )
        { /*If the node is small and has been visited on the same path number, 
            then cannot go further*/
            if( !( nextNode->big ) && ( strcmp( nextNode->vertix, "end" ) ) )
            {
                nextNode->visited = TRUE;
            }
            traverseNodes( nextNode, endCount, path, nodeList ); 
            currentNode->visited = FALSE;
        }

        nextNodeLink = nextNodeLink->next;
            
    }
    ++(*path);
/*    resetVisited( nodeList );*/
}




int readFile( FILE* pathsFilePtr )
{
    int lines = -1;
    int endCount = 0;
    int path = 0;
    node *startNode = NULL;
    LinkedList *nodeList;

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

    nodeList = createNodeList( nodeData, lines );
    startNode = searchList( "start", nodeList );
    traverseNodes( startNode, &endCount, &path, nodeList );

    return endCount;
}


