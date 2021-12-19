/******************************************************************************
 * Filename:  dive.c                                                          *
 * Author: Nicholas Wright 12880155                                           *
 * Purpose:                                                                   *
 * Assertions- PRE:                                                           *
 *            POST:                                                           *
 * Date Written:                                                              *
 * Edited By:       Date Edited:                                              *
 * ***************************************************************************/
#include <stdio.h>
#include "path.h"

int main(int argc, char * argv[])
{
    FILE *filePtr;
    int answer = 0;

    if( argc == 2 )
    {
        filePtr = fopen( argv[1], "r" );
        if( filePtr == NULL )
        {
            perror( "Error opening file\n" );
        }
        else
        {
            answer = readFile( filePtr );
            /*Insert the function to solve the problem here*/
            printf( "Answer is %d\n", answer );
        }
    }
    else
    {
        printf( "You must enter a filename to open\n" );
    }

    return 0;
}
