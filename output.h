/*setup() is called to populate the terminal object. It gets the dimensions of 
the terminal and uses this to set the size of the buffer of stdout. This buffer 
is dynamically allocated and must be deallocated using close()*/
/*
This header provides funtions to setup everything needed to draw ascii art to
a linux terminal. It provides functions for writing in the corner of the 
terminal, animate the writing of an instruction to the centre of the screen,
and draw an image object to the screen given a mask.*/

#ifndef OUTPUT_H
#define OUTPUT_H

#include <stdio.h>
#include <sys/ioctl.h>	//for getting terminal dimensions
#include <unistd.h>		//for STDOUT_FILENO
#include <stdlib.h>		//for malloc and free

struct output {
	char * buf;
	unsigned short rows;
	unsigned short cols;
};

struct xyOffset {
	int x,y;
};





#define _TOPLEFT 0
#define _TOPRIGHT 1
#define _BOTTOMLEFT 2
#define _BOTTOMRIGHT 3

void writeInCorner(
	char str[], 
	int corner, 
	struct output * terminal);

void writeInstruction(
	char str[], 
	struct output * terminal);

void draw(
	struct image * object, 
	struct xyOffset * pos, 
	struct mask * frame, 
	struct output * terminal); //implemented recursively

void setupOutput(struct output * terminal);

void closeOutput(struct output * terminal);


#endif