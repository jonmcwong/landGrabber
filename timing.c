#include "timing.h"

#include <time.h>		//for delay

void delay(size_t ms) { //need to deal with overflow bug TODO
	//delay function works
	size_t deltaClock = ms * CLOCKS_PER_SEC / 1000;
	size_t timeStamp = clock();
	while (clock() - timeStamp < deltaClock) {} //blocking wait
	return;
}