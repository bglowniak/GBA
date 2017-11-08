#include <stdio.h>
#include "library.h"
#include "diddy.h"

unsigned short *videoBuffer = (unsigned short *) 0x6000000;

// Prototypes
void setPixel(int row, int col, u16 color);
void drawRect(int row, int col, int height, int width, u16 color);
void drawChar(int row, int col, char ch, u16 color);
void drawString(int row, int col, char str[], u16 color);

int main() {
	REG_DISPCTL = MODE3 | BG2_ENABLE;
	while(1);
/*	int row = 80;
	int col = 120;
	int rdel = 0;
	int cdel = 0;
	int size = 5;
	int oldrow = row;
	int oldcol = col;
	int score = 0;
	char buffer[41];
	int color = YELLOW;
	int otherColor = WHITE;
	int previousA = 0;

	int bgcolor = RED;

	REG_DMA3SAD = (u32) &bgcolor; // This is always an address!
	REG_DMA3DAD = (u32) videoBuffer; // This is always an address!
	REG_DMA3CNT = (240 * 160) | DMA_ON | DMA_DESTINATION_INCREMENT | DMA_SOURCE_FIXED;

	while(1)
	{
		if (!previousA && KEY_DOWN_NOW(BUTTON_A)) {
			score++;
			previousA = 1;
			int temp = color;
			color = otherColor;
			otherColor = temp;
		}
		if(KEY_DOWN_NOW(BUTTON_UP)) {
			rdel = -1;
		}
		if(KEY_DOWN_NOW(BUTTON_DOWN)) {
			rdel = 1;
		}
		if (KEY_DOWN_NOW(BUTTON_LEFT)) {
			cdel = -1;
		}
		if (KEY_DOWN_NOW(BUTTON_RIGHT)) {
			cdel = 1;
		}
		row = row + rdel;
		col = col + cdel;

		if(row < 0) {
			row = 0;
		}
		if(row > SCREENHEIGHT - size + 1) {
			row = SCREENHEIGHT - size + 1;
		}
		if(col < 0) {
			col = 0;
		}
		if(col > 239 - size + 1) {
			col = 239 - size + 1;
		}
		waitForVblank();
		drawRect(150, 179, 10, 60, bgcolor);
		sprintf(buffer, "Score: %d", score);
		drawString(150, 179, buffer, color);
		drawRect(oldrow, oldcol, size, size, bgcolor);
		drawRect(row, col, size, size, color);
		oldcol = col;
		oldrow = row;
		rdel = 0;
		cdel = 0;
		if (!KEY_DOWN_NOW(BUTTON_A)) {
			previousA = 0;
		}
	}
*/
}

void setPixel(int row, int col, u16 color) {
	videoBuffer[OFFSET(row, col, 240)] = color;
}

void drawRect(int row, int col, int height, int width, u16 color) {
	for(int r = 0; r < height; r++) {
		REG_DMA3SAD = (u32) &color; // This is always an address!
		REG_DMA3DAD = (u32) &videoBuffer[OFFSET(row + r, col, 240)]; // This is always an address!
		//REG_DMA3DAD = (u32)(videoBuffer + OFFSET(row+r, col, 240) ); // This is always an address!
		REG_DMA3CNT = (width) | DMA_ON | DMA_DESTINATION_INCREMENT | DMA_SOURCE_FIXED;
		/*for(int c = 0; c < width; c++) {
			setPixel(row + r, col + c, color);
		}*/
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
