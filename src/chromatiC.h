#ifndef CHROMATIC
#define CHROMATIC
#include <stdio.h>

void fg_color(int r, int g, int b) {
	printf("\033[38;2;%d;%d;%dm", r, g, b);
}

void bg_color(int r, int g, int b) {
	printf("\033[48;2;%d;%d;%dm", r, g, b);
}

void color(int r, int g, int b) {
	fg_color(r, g, b);
	bg_color(r, g, b);
}

void reset(void) {
	printf("\033[0m");
}


#endif
