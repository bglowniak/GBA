#include "myLib.h"
#include "graphics.h"
#include "screens.h"
#include "characters.h"

/**
 * Function that draws an image using DMA.
 */
void drawImage3(int r, int c, int width, int height, const u16* image) {
    for (int row = 0; row < height; row++) {
		DMA[3].src = &image[OFFSET(row, 0, width)];
		DMA[3].dst = &videoBuffer[OFFSET(r + row, c, 240)];
	    DMA[3].cnt = (width) | DMA_ON;
	}
}

/**
 * Function that sets a pixel in the video buffer.
 */
void setPixel(int r, int c, u16 color) {
	videoBuffer[OFFSET(r, c, 240)] = color;
}

/**
 * Function that returns the color value of a specific pixel.
 * Used for border collision detection.
 */
u16 checkPixel(int r, int c) {
    return videoBuffer[OFFSET(r, c, 240)];
}

/**
 * Function that draws a rectangle using DMA.
 * Used to "reset" portions of the screen while drawing the game.
 */
void drawRect(int r, int c, int width, int height, u16 color) {
	for(int row = 0; row < height; row++) {
		DMA[3].src = &color;
		DMA[3].dst = &videoBuffer[OFFSET(row + r, c, 240)];
		DMA[3].cnt = (width) | DMA_ON | DMA_DESTINATION_INCREMENT | DMA_SOURCE_FIXED;
	}
}

/**
 * Function that draws a character from the font.c data.
 */
void drawChar(int r, int c, char ch, u16 color) {
	for(int row = 0; row < 8; row++) {
		for(int col = 0; col < 6; col++) {
			if (fontdata_6x8[OFFSET(row, col, 6) + ch * 48] == 1)	{
				setPixel(row + r, col + c, color);
			}
		}
	}
}

/**
 * Function that utilizes drawChar to draw a full string.
 */
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

void drawVictory() {
    drawImage3(0, 0, VICTORY_WIDTH, VICTORY_HEIGHT, victory);
}

void drawSquareDude(int r, int c) {
    drawImage3(r, c, PLAYER_SIZE, PLAYER_SIZE, square_dude);
}

/**
 * Function that draws a circle enemy.
 * Does not use DMA in order to draw transparency.
 * Transparency is represented by 0x2ffe, a color unused in the game.
 */
void drawCircleEnemy(int r, int c) {
    for (int row = 0; row < ENEMY_SIZE; row++) {
        for (int col = 0; col < ENEMY_SIZE; col++) {
            unsigned int pixel = circle_enemy[(OFFSET(row, col, ENEMY_SIZE))];
            if (pixel != 0x2ffe) { // if pixel does not equal our predefined "transparent" color, ignore it
                setPixel(row + r, col + c, pixel);
            }
        }
    }
}

/**
 * Function that draws a triangle pickup.
 * Does not use DMA to allow for transparency like drawCircleEnemy.
 * 0x2ffe is the "transparent" color.
 */
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
