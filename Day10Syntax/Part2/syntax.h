#ifndef SYNTAX_H
#define SYNTAX_H

#define BIG_DATA 1064
#define SMALL_DATA 64

#define FALSE 0
#define TRUE !FALSE

int fileSize( FILE* syntaxFilePtr );
int readFile( FILE* syntaxFilePtr );

#endif
