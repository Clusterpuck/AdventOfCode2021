#********************************************************************
# File: Makefile                                                    *
# Author: Nicholas Wright 12880155                                  *
# Unit: Advent of Code                                              *
# Purpose: Coordinates compilation instructions                     *
# Date Written: 21/08/21                                            *
#********************************************************************

CC = gcc
CFLAGS = -Wall -pedantic -ansi -Werror
OBJ = main.o syntax.o utility.o linkedlist.o
EXEC = syntax

ifdef DEBUG
CFLAGS += -D DEBUG
DEBUG : clean $(EXEC)
endif

ifdef VALG
CFLAGS += -g
VALG : clean $(EXEC)
endif

$(EXEC) : $(OBJ)
	$(CC) $(OBJ) -o $(EXEC)

main.o: main.c syntax.h
	$(CC) -c main.c $(CFLAGS)

syntax.o : syntax.c syntax.h utility.h
	$(CC) -c syntax.c $(CFLAGS)

utility.o : utility.c utility.h
	$(CC) -c utility.c $(CFLAGS)

linkedlist.o : linkedlist.c linkedlist.h
	$(CC) -c linkedlist.c $(CFLAGS)

clean:
	rm -f $(EXEC) $(OBJ)

