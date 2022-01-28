#********************************************************************
# File: Makefile                                                    *
# Author: Nicholas Wright 12880155                                  *
# Unit: Advent of Code                                              *
# Purpose: Coordinates compilation instructions                     *
# Date Written: 21/08/21                                            *
#********************************************************************

CC = gcc
CFLAGS = -Wall -pedantic -ansi -Werror
OBJ = main.o octopus.o utility.o
EXEC = octopus

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

main.o: main.c octopus.h
	$(CC) -c main.c $(CFLAGS)

octopus.o : octopus.c octopus.h utility.h
	$(CC) -c octopus.c $(CFLAGS)

utility.o : utility.c utility.h
	$(CC) -c utility.c $(CFLAGS)

clean:
	rm -f $(EXEC) $(OBJ)

