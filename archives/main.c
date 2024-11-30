#include "setup.h"

int main (int argc, char *arcv[]) {
	int loop=1;
	DVD dvd;

	window();
	dvdConfig(&dvd);
	drawImg(&dvd);
	gameLoop(&dvd);
	finishOff();
	return 0;
}

