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

#define FALSE 0
#define TRUE !FALSE

void moveAction( int* depthPtr, int* lengthPtr, int *aimPtr,
                    char direction, int magnitude )
{
    switch( direction )
    {
        case 'f':
        {
            (*lengthPtr) = (*lengthPtr) + magnitude;
            (*depthPtr) = (*depthPtr) + ( (*aimPtr) * ( magnitude ) );
            break;
        }
        case 'u':
        {
            (*aimPtr) = (*aimPtr) - magnitude;
            break;
        }
        case 'd':
        {
            (*aimPtr) = (*aimPtr) + magnitude;
            break;
        }
    }
}


int diveAction( FILE *diveFilePtr )
{
    int depth = 0;
    int length = 0;
    int aim = 0;
    int nRead = 0;
    int done = FALSE;
    char direction[500];
    int magnitude = 0;

    while( !done )
    {
        nRead = fscanf( diveFilePtr, "%s %d", direction, &magnitude );
        if( nRead != 2 )
        {
            done = TRUE;
        }
        else
        {
            printf( "%s %d nRead=%d\n", direction, magnitude, nRead );
            moveAction( &depth, &length, &aim, direction[0], magnitude );
        }
    }

    return depth*length;
}


int main(int argc, char * argv[])
{
    char *diveFile = "input.txt";
    FILE *diveFilePtr;
    int area = 0;

    diveFilePtr = fopen( diveFile, "r" );

    if( diveFilePtr == NULL )
    {
        perror( "Error opening file\n" );
    }
    else
    {
        area = diveAction( diveFilePtr );
        printf( "Area is %d\n", area );
    }
    return 0;
}
