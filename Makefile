#Makefile for Assignment 4

CC = g++
OBJS = test1.o test2.o DynPipe.o TwoPipesTwoChildren.o TwoPipesThreeChildren.o
TEST1C = TwoPipesTwoChildren.cpp
TEST2C = TwoPipesThreeChildren.cpp


dynpipe:	DynPipe.o
	$(CC) -g -o dynpipe DynPipe.o

DynPipe.o:
	$(CC) -c DynPipe.cpp

TwoPipesTwoChildren:		TwoPipesTwoChildren.o
	$(CC) -o TwoPipesTwoChildren TwoPipesTwoChildren.o

TwoPipesThreeChildren:		TwoPipesThreeChildren.o
	$(CC) -o  TwoPipesThreeChildren TwoPipesThreeChildren.o

TwoPipesTwoChildren.o :
	$(CC) -c $(TEST1C)

TwoPipesThreeChildren.o :
	$(CC) -c $(TEST2C)

clean:
	rm -f core $(OBJS)
