#include "myLib.h"

u16 *videoBuffer = (u16 *) 0x6000000;

void waitForVblank() {
	while(SCANLINECOUNTER > 160);
	while(SCANLINECOUNTER < 161);
}
