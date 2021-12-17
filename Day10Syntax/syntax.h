#ifndef SYNTAX_H
#define SYNTAX_H

#include "linkedlist.h"

#define BIG_DATA 1064
#define SMALL_DATA 64

#define FALSE 0
#define TRUE !FALSE

int fileSize( FILE* syntaxFilePtr );
int closeChoice( char openBracket, char closeBracket );
int scoreLine( char badBracket );
void insertScore( LinkedList *braceList, LinkedList *inserScores );
int scoreCorrupt( char **fileData, int lines );
int readFile( FILE* syntaxFilePtr );

#endif
