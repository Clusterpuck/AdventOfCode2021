#ifndef UTILITY_H
#define UTILITY_H


void printIntArray( int* array, int length );
void printTwoDIntArray( int **array, int rows, int cols );
void printThreeDIntArray( int ***array, int rows, int cols, int blocks );
void freeTwoDArray( int** array, int rows );

#endif
