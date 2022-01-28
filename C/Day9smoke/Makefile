#********************************************************************
# File: Makefile                                                    *
# Author: Nicholas Wright 12880155                                  *
# Unit: Advent of Code                                              *
# Purpose: Coordinates compilation instructions                     *
# Date Written: 21/08/21                                            *
#********************************************************************

CC = gcc
CFLAGS = -Wall -pedantic -ansi -Werror
OBJ = main.o smoke.o utility.o
EXEC = smoke

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

main.o: main.c smoke.h
	$(CC) -c main.c $(CFLAGS)

smoke.o : smoke.c smoke.h utility.h
	$(CC) -c smoke.c $(CFLAGS)

utility.o : utility.c utility.h
	$(CC) -c utility.c $(CFLAGS)

clean:
	rm -f $(EXEC) $(OBJ)

