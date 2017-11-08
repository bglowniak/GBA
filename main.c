#include <stdio.h>
#include "library.h"
#include "graphics.h"

extern unsigned short *videoBuffer;

enum GBAState {
	START,
	START_NODRAW,
	GAME_OVER,
	GAME_OVER_NODRAW
};

int main() {
	REG_DISPCTL = MODE3 | BG2_ENABLE;
	enum GBAState state = START;
	while(1) {
		waitForVblank();
		switch(state) {
			case START:
				drawSplashScreen();
				state = START_NODRAW;
				break;
			case START_NODRAW:
				if (KEY_DOWN_NOW(BUTTON_SELECT)) {
					state = GAME_OVER;
				}
				break;
			case GAME_OVER:
				drawRect(0, 0, 160, 240, BLACK);
				drawString(76, 90, "Game Over!", YELLOW);
				state = GAME_OVER_NODRAW;
				break;
			case GAME_OVER_NODRAW:
				if (KEY_DOWN_NOW(BUTTON_A)) {
					state = START;
				}
				break;
		}
	}
}
