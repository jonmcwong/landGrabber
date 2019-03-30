/*This header provides functions to save the current input settings for the 
terminal and turn off the echo and canon mode. It also allows you to restore
the previous settings by calling restoreState().*/


#ifndef INPUT_H
#define INPUT_H

#include <termios.h>	//for controlling terminal settings, echo, buffered
#include <unistd.h>		//for STDOUT_FILENO
#include <stdlib.h>		//for malloc and free

struct input {
	struct termios oldt, newt;
	char * keypresses;

};

void setupInput(
	struct input * keypress);

void closeInput(
	struct input * keypress);

char * getKeys(
	struct input * keypress);



#endif