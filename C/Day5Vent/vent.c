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



int countDanger( int** intersects )
{
    int i, j;
    int count = 0;
    for( i=0; i < MAX_COORD; i++ )
    {
        for( j=0; j < MAX_COORD; j++ )
        {
            if( intersects[i][j] > 1 )
            {
                ++count;
            }
        }
    }
    freeTwoDArray( intersects, MAX_COORD );
    return count;
}

void horizontalCount( int** intersects, int **hozVert, int count )
{
    int i, start, end;
    for( i=0; i < count; i++ )
    {
        /*0 is x1, 1 is y1, 2 is x2, 3 is y2*/
        if( hozVert[i][0] == hozVert[i][2] )
        /*vertical line*/
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
            while( start <= end )
            {/*moves along the vertical line and increases
                    count on each point reached*/
                ( intersects[hozVert[i][0]][start] )++;
                ++start;
            }
        }
        else
        /*horizontal line*/
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
            while( start <= end )
            {/*moves along the horizontal line and increases
                    count on each point reached*/
                ( intersects[start][hozVert[i][1]] )++;
                ++start;
            }
        }
    }
}

void diagCount( int** intersects, int** diag, int count )
{
    int i, xStart, yStart, xEnd;
    for( i = 0; i < count; i++ )
    {
        xStart = diag[i][0];
        yStart = diag[i][1];
        xEnd = diag[i][2];
        /*0 is x1, 1 is y1, 2 is x2, 3 is y2*/
        /*Only need to consider 45 degree lines,
 *        therefore x and y coords both invrease by 1*/
        if( diag[i][0] < diag[i][2] )
        {

            if( diag[i][1] < diag[i][3] )
            { /*both x1 and y1 are less than x2 and y2*/
                while( xStart <= xEnd )
                {
                    ( intersects[xStart][yStart] )++;
                    ++xStart;
                    ++yStart;
                }
            }
            else
            { /*x1 less than x2 but y1 is greater than y2*/
                while( xStart <= xEnd )
                {
                    ( intersects[xStart][yStart] ) ++;
                    ++xStart;
                    --yStart;
                }
            }
        }
        else
        { /*x1 is greater than x2*/
            if( diag[i][1] > diag[i][3] )
            { /*x1 and y1 greater than x2, y2 respectively*/
                while( xStart >= xEnd )
                {
                    ( intersects[xStart][yStart] )++;
                    --xStart;
                    --yStart;
                }
            }
            else
            { /* x1 is greater than x2 but y1 is less than y2*/
                while( xStart >= xEnd )
                {
                    ( intersects[xStart][yStart] )++;
                    --xStart;
                    ++yStart;
                }
            }
        }
    }
}



int mapIntersect( int **hozVert, int hzCount, int **diag, int dCount, int lines )
{
    int i;
    int **intersects = (int**)calloc( MAX_COORD, sizeof( int* ) );
    for( i=0; i < MAX_COORD; i++ )
    {
        intersects[i] = (int*)calloc( MAX_COORD, sizeof( int ) );
    }
    /*Intersects is map of all points horizontal and vertical lines cross
 *    intercests[x][y]*/


    horizontalCount( intersects, hozVert, hzCount );
    freeTwoDArray( hozVert, lines );

    diagCount( intersects, diag, dCount );
    freeTwoDArray( diag, lines );

    return countDanger( intersects );
}


int countIntersect( int **coords, int lines )
{
    int i, j;
    int hzCount = 0;
    int dCount = 0;
    int **hozVert = (int**)malloc( sizeof( int* ) * lines );
    int **diag = (int**)malloc( sizeof( int* ) * lines );
    for( i=0; i< lines; i++ )
    {
        hozVert[i] = (int*)malloc( sizeof( int ) * DIMENSION );
    }
    for( i=0; i<lines; i++ )
    {
        diag[i] = (int*)malloc( sizeof( int ) * DIMENSION );
    }

    /*Fills hozVert with all horzintal or vertical lines*/
    for( i=0; i < lines; i++ )
    {
        if( ( coords[i][0] == coords[i][2] ) ||
            ( coords[i][1] == coords[i][3] ) )
        {
            for( j=0; j < DIMENSION; j++ )
            {
                hozVert[hzCount][j] = coords[i][j];
            }
            ++hzCount;
        }
        else
        {
            /*if not horizontal or vertical, then diagonal, fills here*/
            for( j=0; j < DIMENSION; j++ )
            {
                diag[dCount][j] = coords[i][j];
            }
            ++dCount;
        }
    }
    freeTwoDArray( coords, lines );
    return mapIntersect( hozVert, hzCount, diag, dCount, lines );

}



int readFile( FILE* ventFilePtr )
{
    int lines = 0;
    int i;
    int ** coords;
    int answer = 0;

    fileSize( ventFilePtr, &lines );
    printf( "Number of lines in file is %d\n", lines );
    coords = (int**)malloc( sizeof(int*) * lines );
    for( i=0; i < lines; i++ )
    {
        coords[i] = (int*)malloc( sizeof(int) * DIMENSION );
    }

    fillCoords( ventFilePtr, coords, lines );

    fclose( ventFilePtr );

    answer = countIntersect( coords, lines );

    return answer;

}
