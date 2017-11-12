#include "myLib.h"
#include "graphics.h"
#include "screens.h"
#include "characters.h"

extern u16 *videoBuffer;

void drawImage3(int r, int c, int width, int height, const u16* image) {
    for (int row = 0; row < height; row++) {
		DMA[3].src = &image[OFFSET(row, 0, width)];
		DMA[3].dst = &videoBuffer[OFFSET(r + row, c, 240)];
	    DMA[3].cnt = (width) | DMA_ON;
	}
}

void setPixel(int r, int c, u16 color) {
	videoBuffer[OFFSET(r, c, 240)] = color;
}

u16 checkPixel(int r, int c) {
    return videoBuffer[OFFSET(r, c, 240)];
}

void drawRect(int r, int c, int width, int height, u16 color) {
	for(int row = 0; row < height; row++) {
		DMA[3].src = &color;
		DMA[3].dst = &videoBuffer[OFFSET(row + r, c, 240)];
		DMA[3].cnt = (width) | DMA_ON | DMA_DESTINATION_INCREMENT | DMA_SOURCE_FIXED;
	}
}

void drawChar(int r, int c, char ch, u16 color) {
	for(int row = 0; row < 8; row++) {
		for(int col = 0; col < 6; col++) {
			if (fontdata_6x8[OFFSET(row, col, 6) + ch * 48] == 1)	{
				setPixel(row + r, col + c, color);
			}
		}
	}
}

void drawString(int r, int c, char str[], u16 color) {
	while(*str) {
		drawChar(r, c, *str++, color);
		c += 6;
	}
}

void drawSplashScreen() {
    drawImage3(0, 0, SPLASH_WIDTH, SPLASH_HEIGHT, splash);
}

void drawGameOver() {
    drawImage3(0, 0, GAMEOVER_WIDTH, GAMEOVER_HEIGHT, gameOver);
}

void clearScreen() {
    drawRect(0, 0, WIDTH, HEIGHT, WHITE);
}

void drawSquareDude(int r, int c) {
    drawImage3(r, c, PLAYER_SIZE, PLAYER_SIZE, square_dude);
}

void drawCircleEnemy(int r, int c) {
    for (int row = 0; row < ENEMY_SIZE; row++) {
        for (int col = 0; col < ENEMY_SIZE; col++) {
            unsigned int pixel = circle_enemy[(OFFSET(row, col, ENEMY_SIZE))];
            if (pixel != 0x2ffe) {
                setPixel(row + r, col + c, pixel);
            }
        }
    }
    //drawImage3(r, c, ENEMY_SIZE, ENEMY_SIZE, circle_enemy);
}

void drawTrianglePickup(int r, int c) {
    for (int row = 0; row < PICKUP_SIZE; row++) {
        for (int col = 0; col < PICKUP_SIZE; col++) {
            unsigned int pixel = triangle_pickup[(OFFSET(row, col, PICKUP_SIZE))];
            if (pixel != 0x2ffe) {
                setPixel(row + r, col + c, pixel);
            }
        }
    }
}
