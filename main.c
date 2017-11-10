#include "myLib.h"
#include "graphics.h"
#include "game.h"

extern unsigned short *videoBuffer;
extern LEVEL level_1;

enum GBAState {
	START,
	START_NODRAW,
	INIT_LEVEL,
	GAME,
	GAME_OVER,
	GAME_OVER_NODRAW
};

int main() {
	REG_DISPCTL = MODE3 | BG2_ENABLE;

	enum GBAState state = START;
	GameState gameState;
	int startPressed = FALSE;
	LEVEL currentLevel;
	PLAYER player = {0, 0, 0};

	while(1) {
		waitForVblank();
		switch(state) {
			case START:
				drawSplashScreen();
				state = START_NODRAW;
				break;
			case START_NODRAW:
				if (!startPressed && KEY_DOWN_NOW(BUTTON_START)) {
					state = INIT_LEVEL;
					currentLevel = level_1;
					player.deaths = 0;
					startPressed = TRUE;
				}
				break;
			case INIT_LEVEL:
				clearScreen();
				player.x = currentLevel.playerStartX;
				player.y = currentLevel.playerStartY;
				gameState.player = &player;
				gameState.currentLevel = &currentLevel;
				drawImage3(0, 0, 240, 160, currentLevel.backgroundImage);
				drawGame(&gameState);
				state = GAME;
				break;
			case GAME:
				processGame(&gameState);
				drawGame(&gameState);
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
