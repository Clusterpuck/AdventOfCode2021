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
    }

    for( i=0; i < lines; i++ )
    {
        readLine = (char*)malloc( sizeof( char) * SMALL_DATA );
        fgets( readLine, SMALL_DATA, pathsFilePtr );
        nodeData[i][0] = strtok( readLine, "-" );
        nodeData[i][1] = strtok( NULL , "\n" );
    }

    return pathNum;
}


