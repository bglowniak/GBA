#include "library.h"
#include "splash.h"

extern unsigned short *videoBuffer;
void drawImage3(int r, int c, int width, int height, const u16* image) {
    for (int row = 0; row < height; row++) {
		DMA[3].src = &image[OFFSET(row, 0, width)];
		DMA[3].dst = &videoBuffer[OFFSET(r + row, c, 240)];
	    DMA[3].cnt = (width) | DMA_ON;
	}
}

void setPixel(int row, int col, u16 color) {
	videoBuffer[OFFSET(row, col, 240)] = color;
}

void drawRect(int row, int col, int height, int width, u16 color) {
	for(int r = 0; r < height; r++) {
		DMA[3].src = &color;
		DMA[3].dst = &videoBuffer[OFFSET(row + r, col, 240)];
		DMA[3].cnt = (width) | DMA_ON | DMA_DESTINATION_INCREMENT | DMA_SOURCE_FIXED;
	}
}

void drawChar(int row, int col, char ch, unsigned short color) {
	for(int r=0; r< 8; r++) {
		for(int c=0; c<6; c++) {
			if (fontdata_6x8[OFFSET(r, c, 6) + ch*48] == 1)	{
				setPixel(row+r, col+c, color);
			}
		}
	}
}

void drawString(int row, int col, char str[], unsigned short color) {
	while(*str) {
		drawChar(row, col, *str++, color);
		col += 6;
	}
}

void drawSplashScreen() {
    drawImage3(0, 0, SPLASH_WIDTH, SPLASH_HEIGHT, splash);
}
