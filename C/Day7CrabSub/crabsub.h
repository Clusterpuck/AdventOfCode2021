/******************************************************************************
 * Filename:                                                                  *
 * Author: Nicholas Wright 12880155                                           *
 * Purpose:                                                                   *
 * Assertions- PRE:                                                           *
 *            POST:                                                           *
 * Date Written:                                                              *
 * Edited By:       Date Edited:                                              *
 * ***************************************************************************/

#ifndef CRABSUB_H
#define CRABSUB_h

#define BIG_DATA 10000
#define SMALL_DATA 64

int fileSize( FILE* crabsubFilePtr );
void fillCrabs( FILE* crabsubFIlePtr, int *crabArray, int crabs );
double averageCrab( int* crabArray, int crabs );
long fuelCost( int *crabArray, int crabs, int goal );
int findDistance( int *crabArray, int crabs, int goal );
int readFile( FILE* crabsubFilePtr );

#endif
