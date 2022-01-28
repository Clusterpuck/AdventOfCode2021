#ifndef ORIGAMI_H
#define ORIGAMI_H

void fileSize( FILE* origamiFilePtr, int *lines, int *folds );
int readFile( FILE* origamiFilePtr );
void fillCoords( FILE *origamiFilePtr, int **dotCoords, int lines );
void fillFolds( FILE *origamiFilePtr, int **foldDetails, int folds );
void buildArray( int **dotCoords, char ***transArray, int lines );
int getHozLine( FILE* origamiFilePtr );

#endif
