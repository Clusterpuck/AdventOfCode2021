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
#include "vent.h"
#include "utility.h"

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
    free( temp );
    rewind( ventFilePtr );

}


void fillCoords( FILE* ventFilePtr, int **coords, int lines )
{
    int i;
    for( i=0; i < lines; i++ )
    {
        fscanf( ventFilePtr, "%d,%d -> %d,%d\n", 
                &(coords[i][0]), &(coords[i][1]), 
                &(coords[i][2]), &(coords[i][3] ) );
    }
}


void mapIntersect( int **hozVert, int count )
{
    int i, j;
    int start, end;
    int **intersects = (int**)malloc( sizeof( int* ) * count );
    /*need to change to calloc so all values start at 0*/
    for( i=0; i < count; i++ )
    {
        intersects[i] = (int*)malloc( sizeof( int ) * MAX_COORD );
    }

    for( i=0; i < count; i++ )
    {
        /*Only need to check coordinates after what your referencing*/
        for( j = i; j < count; j++ )
        {
            /*0 is x1, 1 is y1, 2 is x2, 3 is y2*/
            if( hozVert[i][0] == hozVert[i][2] )
            /*horizontal line*/
            {
                if( hozVert[i][1] < hozVert[i][3] )
                {
                    start = hozVert[i][1];
                    end = hozVert[i][3];
                }
                else
                {
                    start = hozVert[i][3];
                    end = hozVert[i][1];
                }
                while( start < end )
                {/*moves along the horizontal line and increases 
                        count on each point reached*/
                    ( intersects[hozVert[i][0]][start] )++;
                    ++start;
                }
            }
            else
            /*vertical line*/
            {
                if( hozVert[i][0] < hozVert[i][2] )
                {
                    start = hozVert[i][0];
                    end = hozVert[i][2];
                }
                else
                {
                    start = hozVert[i][2];
                    end = hozVert[i][0];
                }
                while( start < end )
                {/*moves along the horizontal line and increases 
                        count on each point reached*/
                    ( intersects[start][hozVert[i][1]] )++;
                    ++start;
                }
            }
        }
    }
}    


int countIntersect( int **coords, int lines )
{
    int i;
    int count = 0;
    int **hozVert = (int**)malloc( sizeof( int* ) * lines );
    for( i=0; i< lines; i++ )
    {
        hozVert[i] = (int*)malloc( sizeof( int ) * DIMENSION );
    }
    /*Fills hozVert with all horzintal or vertical lines*/
    for( i=0; i < lines; i++ )
    {
        if( ( coords[i][0] == coords[i][2] ) ||
            ( coords[i][1] == coords[i][3] ) )
        {
            hozVert[count][0] = coords[i][0];
            hozVert[count][1] = coords[i][1];
            hozVert[count][2] = coords[i][2];
            hozVert[count][3] = coords[i][3];
            ++count;
        }
    }

    mapIntersect( hozVert, count );

    return count;
}


    
    

void readFile( FILE* ventFilePtr )
{
    int lines = 0;
    int i;
    int ** coords;
    int intersections = 0;

    fileSize( ventFilePtr, &lines );
    printf( "Number of lines in file is %d\n", lines );
    coords = (int**)malloc( sizeof(int*) * lines );
    for( i=0; i < lines; i++ )
    {
        coords[i] = (int*)malloc( sizeof(int) * DIMENSION );
    }
    
    fillCoords( ventFilePtr, coords, lines );

    fclose( ventFilePtr );

    intersections = countIntersect( coords, lines );
    printf( "Intersections is %d\n", intersections );

}
    
