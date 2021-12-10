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
#include "vent.h"

void fileSize( FILE* ventFilePtr, int *lines )
{
    int done = FALSE;
    char *endCheck;
    char *temp = (char*)malloc( sizeof( char ) * 1000 );
    
    while( !done )
    {
        endCheck = fgets( temp, 1000, ventFilePtr );
        if( endCheck == NULL )
        {
            done = TRUE;
        }
        else
        {
            (*lines)++;
        }
    }
}
        


void readFile( FILE* ventFilePtr )
{
    int lines = 0;
    fileSize( ventFilePtr, &lines );
    
