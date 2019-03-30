//TODO  
//deal with overflow bug in delay()

//need intro
//2 player game
//need function that saves the scene in square blocks, blocks will be the size of a single players screen 
//need function that prints 2 players split screen to terminal
//need a fill function
//need to implement logic for calling fill function
//need to implement logic for cutting off opponent
//function that prints string centred at certain pixel
//deal with input each frame

#include <stdio.h>		//for i/o
#include <stdlib.h>		//for malloc and free
#include <termios.h>	//for controlling terminal settings, echo, buffered
#include <time.h>		//for delay
#include <sys/ioctl.h>	//for getting terminal dimensions
#include <unistd.h>		//for STDOUT_FILENO
#include <string.h>		//for passing strings to functions
#include <stdio_ext.h>	//for __fbufsize


void delay(size_t ms) { //need to deal with overflow bug TODO
	//delay function works
	size_t deltaClock = ms * CLOCKS_PER_SEC / 1000;
	size_t timeStamp = clock();
	while (clock() - timeStamp < deltaClock) {} //blocking wait
	return;
}

#define _TOPLEFT 0
#define _TOPRIGHT 1
#define _BOTTOMLEFT 2
#define _BOTTOMRIGHT 3

struct output {
	char * buf;
	unsigned short rows;
	unsigned short cols;
};

char * draw(char * buf, int corner, struct winsize termDim, char str[]) {
	return;
}

void printInstruction(char str[], struct output * terminal) { //tested
	//animates printing to middle of screen
	//takes string, and terminal rows and columns
	size_t length = strlen(str);
	unsigned short numEmptyRows = terminal->rows / 2 ;
	unsigned short midCol = terminal->cols / 2;

	char * emptySpace = calloc(numEmptyRows + 1, sizeof(char)); //filled with \0
	memset(emptySpace, '\n', numEmptyRows);
	char * displayLine = calloc(terminal->cols, sizeof(char));
	// memset(terminal->buf, '\n', numEmptyRows);

	for (int i = 0; i < length; i++) {
		// memset(terminal->buf + numEmptyRows, ' ', terminal->cols - 1);
		// memcpy(terminal->buf + numEmptyRows + midCol - i / 2, str, i + 1);
		// memset(terminal->buf + numEmptyRows + terminal->cols - 1, '\n', numEmptyRows);
		memset(displayLine, ' ', terminal->cols - 1); //clear displayLine
		memcpy(displayLine + midCol - i / 2, str, i + 1);
		printf("%s%s%s", emptySpace, displayLine, emptySpace);
		fflush(stdout);
		delay(20);
	}
	//free(emptySpace);
	//free(displayLine);
}






int main() { //arena should be 180, 420 = 75600

	//get terminal dimensions
	struct winsize termDim;
	ioctl(STDOUT_FILENO, TIOCGWINSZ, &termDim);

	//set output buffsize, turn on full buffering
	size_t bufferSize = (termDim.ws_col + 1) * termDim.ws_row;
	char * buf = malloc(bufferSize);
	setvbuf(stdout, buf, _IOFBF, bufferSize);

	//create output variable
	struct output terminal;
	terminal.buf = buf;
	terminal.rows = termDim.ws_row;
	terminal.cols = termDim.ws_col;
	//printf("bufferSize: %ld\n", __fbufsize(stdout));
	char str[] = "yo";
	fflush(stdout);
	strcpy(terminal.buf,str);
	memset(terminal.buf, 'X', 5);
	int err = fflush(stdout);
	printf("errno: %d\n", err);
	fflush(stdout);
	//set terminal settings

	static struct termios oldt, newt;
	tcgetattr(STDOUT_FILENO, &oldt); //copy old settings
	newt = oldt;
	newt.c_lflag &= ~(ECHO | ICANON); //turns off echo and buffered input
	tcsetattr(STDOUT_FILENO, TCSANOW, &newt);

	delay(2000);

	printInstruction("Welcome to my game!", &terminal);	
	//fflush(stdout);	
	delay(1000);
	printInstruction("Do you like this pretty text?", &terminal);
	//fflush(stdout);	
	delay(1000);
	printInstruction("It's nice right?! But the question is, is this text centralised?", &terminal);
	//fflush(stdout);	
	delay(1000);


	//begin writing to stdout
	//sets the output buffer to be used

	tcsetattr(STDOUT_FILENO, TCSANOW, &oldt);

	free(buf); //deallocation of buffer
	return 0;
}