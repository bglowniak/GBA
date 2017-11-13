#include "myLib.h"
#include "graphics.h"
#include "game.h"
#include <stdio.h>

extern u16 *videoBuffer;
extern LEVEL levels[];
extern int numLevels;

enum GBAState {
	START,
	START_NODRAW,
	INIT_LEVEL,
	GAME,
	NEXT_LEVEL,
	GAME_OVER,
	GAME_OVER_NODRAW,
	VICTORY,
	VICTORY_NODRAW
};

int main() {
	REG_DISPCTL = MODE3 | BG2_ENABLE;

	enum GBAState state = START;
	GameState gameState;
	int startPressed = FALSE;
	LEVEL currentLevel;
	PLAYER player = {0, 0, 0, 0};

	u32 color = WHITE;
	char buffer[12];

	gameState.player = &player;
	gameState.currentLevel = &currentLevel;

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
					currentLevel = levels[0];
					player.deaths = 0;
					startPressed = TRUE;
				}
				break;
			case INIT_LEVEL:
				player.x = currentLevel.playerStartX;
				player.y = currentLevel.playerStartY;
				player.pickupCollected = !currentLevel.hasPickup;

				drawImage3(0, 0, 240, 160, currentLevel.backgroundImage);
				sprintf(buffer, "Level %d", currentLevel.levelID);
				drawString(149, 10, buffer, WHITE);
				drawRect(146, 120, 120, 14, BLACK);
				sprintf(buffer, "Deaths: %d", player.deaths);
				drawString(149, 170, buffer, color);
				drawGame(&gameState);
				state = GAME;
				break;
			case GAME:
				processMovements(&gameState);
				drawGame(&gameState);
				if (checkDeath(&gameState)) {
					gameState.player->x = currentLevel.playerStartX;
					gameState.player->y = currentLevel.playerStartY;
					gameState.player->deaths++;
					int deaths = gameState.player->deaths;
					if (deaths >= 20) {
						state = GAME_OVER;
					} else {
						drawGame(&gameState);
						drawRect(146, 120, 120, 14, BLACK);
				    	sprintf(buffer, "Deaths: %d", deaths);
				    	unsigned int color;
				    	if (deaths >= 19) {
				        	color = RED;
				    	} else if (deaths >= 10) {
				        	color = YELLOW;
				    	} else {
							color = WHITE;
						}
				    	drawString(149, 170, buffer, color);
					}
				}
				if (checkVictory(&gameState)) {
					state = NEXT_LEVEL;
				}
				if (KEY_DOWN_NOW(BUTTON_SELECT)) {
					state = START;
				}
				break;
			case NEXT_LEVEL:
				if (currentLevel.levelID == numLevels) {
					state = VICTORY;
				} else {
					currentLevel = levels[currentLevel.levelID];
					state = INIT_LEVEL;
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
			case VICTORY:
				drawVictory();
				state = VICTORY_NODRAW;
				break;
			case VICTORY_NODRAW:
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
