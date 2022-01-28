#ifndef UTILITY_H
#define UTILITY_H


void printIntArray( int* array, int length );
void printULongArray( unsigned long* array, int length );
void printTwoDIntArray( int **array, int rows, int cols );
void printTwoDLongArray( long **array, int rows, int cols );
void printThreeDLongArray( long ***array, int rows, int cols, int blocks );
void printTwoDStringArray( char ***array, int rows, int cols );
void printThreeDIntArray( int ***array, int rows, int cols, int blocks );
void printTwoDCharArray( char **array, int rows, int cols );
void freeTwoDArray( int** array, int rows );
void printStringArray( char** array, int length );

#endif
