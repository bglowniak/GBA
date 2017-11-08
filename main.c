#include <stdio.h>
#include "library.h"
#include "graphics.h"

extern unsigned short *videoBuffer;

int main() {
	REG_DISPCTL = MODE3 | BG2_ENABLE;
	drawSplashScreen();
	while(1);
}
