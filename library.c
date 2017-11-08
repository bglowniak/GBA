#include "library.h"

extern unsigned short *videoBuffer;

void waitForVblank() {
	while(SCANLINECOUNTER > 160);
	while(SCANLINECOUNTER < 160);
}

void delay(int n) {
	volatile int size = 0;
	for(int i = 0; i < n * 4000; i++) {
		size = size + 1;
	}
}

void drawImage3(int r, int c, int width, int height, const u16* image) {
    for (int row = 0; row < height; row++) {
		DMA[3].src = &image[OFFSET(row, 0, width)];
		DMA[3].dst = &videoBuffer[OFFSET(r + row, c, 240)];
	    DMA[3].cnt = (width) | DMA_ON;//| DMA_DESTINATION_INCREMENT | DMA_SOURCE_INCREMENT;
	}
}
