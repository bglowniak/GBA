#include <stdio.h>
#include "myLib.h"
#include "graphics.h"

extern unsigned short *videoBuffer;

enum GBAState {
	START,
	START_NODRAW,
	GAME,
	GAME_NODRAW,
	GAME_OVER,
	GAME_OVER_NODRAW
};

int main() {
	REG_DISPCTL = MODE3 | BG2_ENABLE;
	enum GBAState state = START;
	int startPressed = FALSE;
	int oldRow = 0;
	int oldCol = 0;
	int row;
	int col;
	int rdel;
	int cdel;
	while(1) {
		waitForVblank();
		switch(state) {
			case START:
				drawSplashScreen();
				state = START_NODRAW;
				break;
			case START_NODRAW:
				if (!startPressed && KEY_DOWN_NOW(BUTTON_START)) {
					state = GAME;
					startPressed = TRUE;
				}
				break;
			case GAME:
				clearScreen();
				drawSquareDude(50, 50);
				drawCircleEnemy(120, 80);
				drawCircleEnemy(80, 80);
				row = 50;
				col = 50;
				oldRow = 50;
				oldCol = 50;
				state = GAME_NODRAW;
				break;
			case GAME_NODRAW:
				rdel = 0;
				cdel = 0;
				oldRow = row;
				oldCol = col;
				if (KEY_DOWN_NOW(BUTTON_LEFT)) {
					cdel = -1;
				}
				if (KEY_DOWN_NOW(BUTTON_RIGHT)) {
					cdel = 1;
				}
				if (KEY_DOWN_NOW(BUTTON_UP)) {
					rdel = -1;
				}
				if (KEY_DOWN_NOW(BUTTON_DOWN)) {
					rdel = 1;
				}

				row = row + rdel;
				col = col + cdel;
				if (row < 0) {
					row = 0;
				}
				if (row >= HEIGHT - 7) {
					row = HEIGHT - 7;
				}
				if (col < 0) {
					col = 0;
				}
				if (col >= WIDTH - 7) {
					col = WIDTH - 7;
				}

				drawRect(oldRow, oldCol, PLAYER_SIZE, PLAYER_SIZE, WHITE);
				drawSquareDude(row, col);

				if (KEY_DOWN_NOW(BUTTON_SELECT)) {
					state = START;
				}
				break;
			case GAME_OVER:
				drawGameOver();
				state = GAME_OVER_NODRAW;
				break;
			case GAME_OVER_NODRAW:
				if (!startPressed && KEY_DOWN_NOW(BUTTON_START)) {
					state = START;
					startPressed = TRUE;
				}
				break;
		}

		if (!KEY_DOWN_NOW(BUTTON_START)) {
			startPressed = FALSE;
		}
	}
}
