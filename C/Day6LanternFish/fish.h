#ifndef FISH_H
#define FISH_H

#define LONGEST_CYCLE 9
#define FERTILE_AGE 6
#define DAYS 256

void fillFishArray( FILE* fishFilePtr, unsigned long *fishArray );
void cycleDays( unsigned long *fishArray );
unsigned long sumArray( unsigned long *fishArray );
unsigned long readFile( FILE* fishFilePtr );

#endif
