/******************************************************************************
 * Filename:                                                                  *
 * Author: Nicholas Wright 12880155                                           *
 * Purpose:                                                                   *
 * Assertions- PRE:                                                           *
 *            POST:                                                           *
 * Date Written:                                                              *
 * Edited By:       Date Edited:                                              *
 * ***************************************************************************/

#ifndef WIRES_H
#define WIRES_H

#define BIG_DATA 1000
#define SMALL_DATA 64
#define NUMBERS 10
#define IN_LENGTH 10
#define OUT_LENGTH 4

void fiveLengthDecode( char** decoderString, char* inSeg, int length );
void sixLengthDecode( char** decoderString, char* inSeg, int length );
void deepDecode( char** inArray, char **decoderString );
int translate( char **decodeString, char *output );
int decode( char *input, char *output );
int getDigits( FILE* wireFilePtr );
int readFile( FILE* wireFilePtr );

#endif
