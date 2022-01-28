/******************************************************************************
 * Filename:  depthCount.c                                                    *
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

int counter( FILE *depthFilePtr )
{
    int count = 0;
    int numOne, numTwo, numThree, numFour;
    int sumA, sumB;
    int nRead = 0;
    int done = FALSE;

    nRead = fscanf( depthFilePtr, "%d\n%d\n%d\n",
                        &numOne, &numTwo, &numThree );
    sumA = numOne + numTwo + numThree;

    while( !done )
    {
        nRead = fscanf( depthFilePtr, "%d", &numFour );
        if( nRead == 1 )
        {
            sumB = sumA - numOne + numFour;
            if( sumB > sumA )
            {
                ++count;
                printf( "count is %d\n", count );
            }
            numOne = numTwo;
            numTwo = numThree;
            numThree = numFour;
            sumA = numOne + numTwo + numThree;
        }
        else if ( nRead != 1 || nRead == EOF )
        {
            done = TRUE;
        }
    }
    return count;
}


int main(int argc, char * argv[])
{
    char *depthFile =  "input.txt";
    FILE *depthFilePtr;
    int count = 0;

    depthFilePtr = fopen( depthFile, "r" );

    if( depthFilePtr == NULL )
    {
        perror( "Error opening file" );
    }
    else
    {
        count = counter( depthFilePtr );
    }

    printf( "The final count is %d\n", count );

    return 0;
}
