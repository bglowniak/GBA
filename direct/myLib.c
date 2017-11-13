#include "myLib.h"

//Each value in the video buffer corresponds to a pixel on the GameBoy screen
u16 *videoBuffer = (u16 *) 0x6000000;

void waitForVblank() {
	while(SCANLINECOUNTER > 160);
	while(SCANLINECOUNTER < 161);
}
