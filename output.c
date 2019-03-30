#include "output.h"

#include <stdio.h>
#include <sys/ioctl.h>	//for getting terminal dimensions
#include <unistd.h>		//for STDOUT_FILENO
#include "timing.h"		//for delay
#include <stdlib.h>		//for malloc and free

void writeInCorner(
	char str[], 
	int corner, 
	struct output * terminal) {

}

void writeInstruction(
	char str[], 
	struct output * terminal) {	//tested
	//animates printing to middle of screen
	//takes string, and terminal rows and columns

	size_t length = strlen(str);
	unsigned short numEmptyRows = terminal->rows / 2 ;
	unsigned short midCol = terminal->cols / 2;
	char * emptySpace = calloc(numEmptyRows + 1, sizeof(char));
	memset(emptySpace, '\n', numEmptyRows);
	char * displayLine = calloc(terminal->cols, sizeof(char));
	// memset(terminal->buf, '\n', numEmptyRows);
	for (int i = 0; i < length; i++) {
		memset(displayLine, ' ', terminal->cols - 1); //clear displayLine
		memcpy(displayLine + midCol - i / 2, str, i + 1);
		printf("%s%s%s", emptySpace, displayLine, emptySpace);
		fflush(stdout);
		delay(20);
	}
	free(emptySpace);
	free(displayLine);
}

void draw(
	struct image * object, 
	struct xyOffset * pos, 
	struct mask * frame, 
	struct output * terminal) {

}

void setupOutput(
	struct output * terminal) {
	//gets terminal size
	//sets stdout buffer length

	//get terminal dimensions
	struct winsize termDim;
	ioctl(STDOUT_FILENO, TIOCGWINSZ, &termDim);

	//set output buffsize, turn on full buffering
	size_t bufferSize = (termDim.ws_col + 1) * termDim.ws_row;
	terminal->buf = malloc(bufferSize);
	setvbuf(stdout, terminal->buf, _IOFBF, bufferSize);

	//save dims
	terminal->rows = termDim.ws_row;
	terminal->cols = termDim.ws_col;
	fflush(stdout);
}

void closeOutput(
	struct output * terminal) {
	//deallocation of buffer
	
	free(terminal->buf); 
}
