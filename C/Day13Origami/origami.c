/******************************************************************************
 * Filename:  origami.c                                                       *
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

#include "origami.h"
#include "utility.h"

void fileSize( FILE* origamiFilePtr, int *dots, int *folds )
{
    char *tempString = (char*)malloc( sizeof( char ) * 64 );
    char *endTest = (char*)malloc( sizeof( char ) * 64 );
    while( strcmp( tempString, "\n" ) )
    {
        ++(*dots);
        fgets( tempString, 64, origamiFilePtr );
    }    
    while( endTest != NULL )
    {
        ++(*folds);
        endTest = fgets( tempString, 64, origamiFilePtr );
    }
    rewind( origamiFilePtr );
}

void fillCoords( FILE* origamiFilePtr, int **dotCoords, int lines )
{
    int i;
    dotCoords[lines][0] = 0;
    dotCoords[lines][1] = 0;
    for( i = 0; i < lines; i++ )
    {
        fscanf( origamiFilePtr, "%d,%d\n", 
                &( dotCoords[i][1] ), &( dotCoords[i][0] ) );
        if( dotCoords[i][0] > dotCoords[lines][0] )
        {
            dotCoords[lines][0] = dotCoords[i][0];
        }
        if( dotCoords[i][1] > dotCoords[lines][1] )
        {
            dotCoords[lines][1] = dotCoords[i][1];
        }
    }
}

void fillFolds( FILE* origamiFilePtr, int **foldDetails, int folds )
{
    int i;
    char xOrY;
    for( i = 0; i < folds; i++ )
    {
        fscanf( origamiFilePtr, "fold along %c=%d\n", 
                &xOrY, &foldDetails[i][0] );
        if( xOrY == 'x' )
        {
            foldDetails[i][1] = 1;
        }
        if( xOrY == 'y' )
        {
            foldDetails[i][1] = 0;
        }
    }
}


void hozFold( char **array, int rows, int cols, int hzLine )
{/*Fold up along line y = hzLine, where hzLine counts from top down*/
    int i, j;
    for( i=hzLine; i >=0; i-- )
    {
        for( j=0; j < cols; j++ )
        {
            if( ( hzLine+i < rows ) && ( array[hzLine+i][j] == '#' ) )
            {
                if( ( hzLine-i ) >= 0 ) 
                {
                    array[hzLine-i][j] = '#';
                }
            }
        }
    }
}

void vertFold( char **array, int rows, int cols, int vLine )
{/*fold left*/
    int i, j;
    for( i=0; i < rows; i++ )
    {
        for( j=vLine; j >=0; j-- )
        {
            if( ( vLine+j < cols ) && ( array[i][vLine+j] == '#' ) )
            {
                if( ( vLine - j ) >= 0 )
                {
                    array[i][vLine-j] = '#';
                }
            }
        }
    }
}
    
void buildArray( int **dotCoords, char ***array, int lines )
{
    int i, j;
    int rows = ( dotCoords[lines][0] ) + 1;
    int cols = ( dotCoords[lines][1] ) + 1;
    char **transArray = (char**)malloc( sizeof( char* ) * rows );
    for( i=0; i < rows; i++ )
    {
        transArray[i] = (char*)malloc( sizeof( char ) * cols );
    }
    for( i=0; i< rows; i++ )
    {
        for( j=0; j< cols; j++ )
        {
            transArray[i][j] = '.';
        }
    } 
    for( i=0; i < lines; i++ )
    {
        transArray[dotCoords[i][0]][dotCoords[i][1]] = '#';
    }


    (*array) = transArray;
    
}

int dotCount( char **array, int rows, int cols )
{
    int i, j;
    int count = 0;
    for( i=0; i<rows; i++ )
    {
        for( j=0; j<cols; j++ )
        {
            if( array[i][j] == '#' )
                ++count;
        }
    }
    return count;
}

void performFolds( char **transArray, int rows, int cols, 
                   int **foldDetails, int folds )
{/*0 is horizontal fold 1 is vertical fold*/
    int i, dots;
    for( i=0; i < folds; i++ )
    {
        if( foldDetails[i][1] == 0 )
        {
            hozFold( transArray, rows, cols, foldDetails[i][0] );
            rows = foldDetails[i][0];
        }
        else
        {
            vertFold( transArray, rows, cols, foldDetails[i][0] );
            cols = foldDetails[i][0];
        }
        dots = dotCount( transArray, rows, cols );
        printf( "%d dots at fold %d\n", dots, i+1 );
    }
    printTwoDCharArray( transArray, rows, cols );
}



int readFile( FILE* origamiFilePtr )
{
    int lines = -1;
    int folds = -1;
    int i;
    int **dotCoords, **foldDetails;
    char **transArray;
    int rows, cols;

    fileSize( origamiFilePtr, &lines, &folds );

    dotCoords = (int**)malloc( sizeof( int* ) * (lines+1) );
    for( i = 0; i < (lines + 1); i++ )
    {
        dotCoords[i] = (int*)malloc( sizeof( int ) * 2 );
    }

    foldDetails = (int**)malloc( sizeof( int* ) * folds );
    for( i=0; i < folds; i++ )
    {
        foldDetails[i] = (int*)malloc( sizeof( int ) * 2 );
    }

    fillCoords( origamiFilePtr, dotCoords, lines );
    fillFolds( origamiFilePtr, foldDetails, folds );
    /*maximum for each column stored in "lines" row*/
    rows = dotCoords[lines][0]+1;
    cols = dotCoords[lines][1]+1;

    buildArray( dotCoords, &transArray, lines );

    performFolds( transArray, rows, cols, foldDetails, folds );

    return rows;
}
