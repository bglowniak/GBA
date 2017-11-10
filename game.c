#include "level1.h"
#include "game.h"
#include "myLib.h"

extern unsigned short *videoBuffer;

void drawGame(GameState* state) {
    PLAYER player = *(state->player);
    drawSquareDude(player.y, player.x);

    LEVEL level = *(state->currentLevel);
    ENEMY* enemies = level.enemies;
    for (int i = 0; i <= level.numEnemies; i++) {
        ENEMY enemy = *(enemies + i);
        drawCircleEnemy(enemy.y, enemy.x);
    }
}

void processGame(GameState* state) {
    PLAYER* player = state->player;
    ENEMY* enemies = state->currentLevel->enemies;
    for (int i = 0; i < state->currentLevel->numEnemies; i++) {
        moveEnemy(enemies + i);
    }
    int xdel = 0;
    int ydel = 0;
    if (KEY_DOWN_NOW(BUTTON_UP)) {
        ydel = -1;
    }
    if (KEY_DOWN_NOW(BUTTON_DOWN)) {
        ydel = 1;
    }
    if (KEY_DOWN_NOW(BUTTON_RIGHT)) {
        xdel = 1;
    }
    if (KEY_DOWN_NOW(BUTTON_LEFT)) {
        xdel = -1;
    }

    if (movePlayer(player, &xdel, &ydel)) {
        drawRect(player->y - ydel, player->x - xdel, PLAYER_SIZE, PLAYER_SIZE, WHITE);
    }
    state->player = player;
    state->currentLevel->enemies = enemies;
}

int movePlayer(PLAYER* player, int* xdel, int* ydel) {
    int leftX = player->x;
    int rightX = player->x + PLAYER_SIZE - 1;
    int topY = player->y;
    int bottomY = player->y + PLAYER_SIZE - 1;
    //top
    if ((*ydel == -1) && (checkPixel(topY + *ydel, leftX) == BLACK || checkPixel(topY + *ydel, rightX) == BLACK)) {
        *ydel = 0;
    }

    //bottom
    if ((*ydel == 1) && (checkPixel(bottomY + *ydel, leftX) == BLACK || checkPixel(bottomY + *ydel, rightX) == BLACK)) {
        *ydel = 0;
    }
    //left
    if ((*xdel == -1) && (checkPixel(topY, leftX + *xdel) == BLACK || checkPixel(bottomY, leftX + *xdel) == BLACK)) {
        *xdel = 0;
    }
    //right
    if ((*xdel == 1) && (checkPixel(topY, rightX + *xdel) == BLACK || checkPixel(bottomY, rightX + *xdel) == BLACK)) {
        *xdel = 0;
    }
    player->x = player->x + *xdel;
    player->y = player->y + *ydel;
    return ((*xdel != 0) || (*ydel != 0));
}

void moveEnemy(ENEMY* enemy) {
    int leftX = enemy->x;
    int rightX = enemy->x + ENEMY_SIZE - 1;
    int topY = enemy->y;
    int bottomY = enemy->y + ENEMY_SIZE - 1;
    int xdel = 0;
    int ydel = 0;
    int vel = enemy->velocity;
    switch(enemy->direction) {
        case UP:
            if (checkPixel(topY - 1, leftX) == BLACK || checkPixel(topY - 1, rightX) == BLACK) {
                enemy->direction = DOWN;
                ydel = vel;
            } else {
                ydel = -vel;
            }
            break;
        case DOWN:
            if (checkPixel(bottomY + 1, leftX) == BLACK || checkPixel(bottomY + 1, rightX) == BLACK) {
                enemy->direction = UP;
                ydel = -vel;
            } else {
                ydel = vel;
            }
            break;
        case RIGHT:
            if (checkPixel(topY, rightX + 1) == BLACK || checkPixel(bottomY, rightX + 1) == BLACK) {
                enemy->direction = LEFT;
                xdel = -vel;
            } else {
                xdel = vel;
            }
            break;
        case LEFT:
            if (checkPixel(topY, leftX - 1) == BLACK || checkPixel(bottomY, leftX - 1) == BLACK) {
                enemy->direction = RIGHT;
                xdel = vel;
            } else {
                xdel = -vel;
            }
            break;
    }

    enemy->x = leftX + xdel;
    enemy->y = topY + ydel;
    drawRect(topY, leftX, ENEMY_SIZE, ENEMY_SIZE, WHITE);
}

int checkVictory(GameState* state) {
    int x = state->player->x;
    int y = state->player->y;
    return (checkPixel(y, x + 8) == 0x2f46);
}

ENEMY level1E[] = {
    {65, 28, 1, UP},
    {45, 46, 2, RIGHT},
    {187, 61, 2, LEFT},
    {45, 76, 2, RIGHT},
    {187, 91, 2, LEFT},
    {45, 106, 2, RIGHT},
    {146, 125, 1, DOWN}
};

LEVEL levels[] = {
    {level1, 7, level1E, 14, 14, 1}
};
