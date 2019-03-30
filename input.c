#include "input.h"
#include <unistd.h>		//for STDOUT_FILENO
#include <stdlib.h>		//for malloc and free

#define MAX_KEY_RATE 20 //per second

void setupInput(
	struct input * keypress) {
	//saves old terminal settings
	//turns off canonical mode and echo
	//allocates keypress buffer

	//copy old settings
	tcgetattr(STDOUT_FILENO, &(keypress->oldt)); 
	keypress->newt = keypress->oldt;

	//turns off echo and buffered input
	(keyress->newt).c_lflag &= ~(ECHO | ICANON); 
	tcsetattr(STDOUT_FILENO, TCSANOW, &(keypress->newt));

	keypress->keypresses = malloc(MAX_KEY_RATE);
}

void closeInput(
	struct input * keypress) {

	tcsetattr(STDOUT_FILENO, TCSANOW, &(keypress->oldt));
	free(keypress->keypresses);
}

char * getKeys(
	struct input * keypress) {

	//takes out all repetitions in the bufferer
	//creates null terminated C string and places in keypresses
}
