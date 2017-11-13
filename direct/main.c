#include "myLib.h"
#include "graphics.h"
#include "game.h"
#include <stdio.h>

/**
 * main.c is the loop/state machine that runs the game and calls on the game's functions.
 */

extern u16 *videoBuffer;
extern LEVEL levels[];
extern int numLevels;

/**
 * Enum that keeps track of the current state of the game.
 * "NODRAW" states are used so that backgrounds aren't constantly redrawn
 * while waiting for user input.
 */
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
	int startPressed = FALSE;

	//used for drawing strings
	u32 color = WHITE;
	char buffer[12];

	//set up important game variables before running loop
	LEVEL currentLevel;
	PLAYER player = {0, 0, 0, 0};
	GameState gameState;
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
					//reset player death count in case the user is restarting after having played.
					player.deaths = 0;
					startPressed = TRUE;
				}
				break;
			case INIT_LEVEL: //reset the player and initialize the new level
				player.x = currentLevel.playerStartX;
				player.y = currentLevel.playerStartY;

				//if a level does not have a pickup, the user defaults to having it
				player.pickupCollected = !currentLevel.hasPickup;

				//draw out the level background and detail strings
				drawImage3(0, 0, 240, 160, currentLevel.backgroundImage);
				sprintf(buffer, "Level %d", currentLevel.levelID);
				drawString(149, 10, buffer, WHITE);
				drawRect(146, 120, 120, 14, BLACK);
				sprintf(buffer, "Deaths: %d", player.deaths);
				drawString(149, 170, buffer, color);

				state = GAME;
				break;
			case GAME:
				processMovements(&gameState);
				drawGame(&gameState);
				if (checkDeath(&gameState)) {
					//reset the player to the starting position
					gameState.player->x = currentLevel.playerStartX;
					gameState.player->y = currentLevel.playerStartY;

					//update death count
					gameState.player->deaths++;
					int deaths = gameState.player->deaths;
					if (deaths >= 20) {
						state = GAME_OVER;
					} else {
						//update death count string with correct color
						drawRect(146, 120, 120, 14, BLACK);
				    	sprintf(buffer, "Deaths: %d", deaths);
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
					//user has beaten every level
					state = VICTORY;
				} else {
					//set currentLevel and reinitialize
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

		/**
		 * This condition is used to make sure that a start button press only
		 * affects one frame until it is released
		 */
		if (!KEY_DOWN_NOW(BUTTON_START)) {
			startPressed = FALSE;
		}
	}
}
