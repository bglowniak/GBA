#include "levels.h"
#include "game.h"
#include "myLib.h"
#include <stdio.h>

extern u16 *videoBuffer;
u16 vCol = 0x2f46; //the color that represents the victory zone

void drawGame(GameState* state) {
    PLAYER player = *(state->player);
    drawSquareDude(player.y, player.x);

    LEVEL level = *(state->currentLevel);
    ENEMY* enemies = level.enemies;
    for (int i = 0; i < level.numEnemies; i++) {
        ENEMY enemy = *(enemies + i);
        drawCircleEnemy(enemy.y, enemy.x);
    }

    if (!player.pickupCollected) {
        drawTrianglePickup(level.pickup.y, level.pickup.x);
    }
}

void processMovements(GameState* state) {
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

    if (!player->pickupCollected && checkPickupCollision(player, state->currentLevel->pickup.x, state->currentLevel->pickup.y)) {
        drawRect(state->currentLevel->pickup.y, state->currentLevel->pickup.x, PICKUP_SIZE, PICKUP_SIZE, WHITE);
        player->pickupCollected = 1;
    }
    state->player = player;
    state->currentLevel->enemies = enemies;
}

int movePlayer(PLAYER* player, int* xdpointer, int* ydpointer) {
    int leftX = player->x;
    int rightX = player->x + PLAYER_SIZE - 1;
    int topY = player->y;
    int bottomY = player->y + PLAYER_SIZE - 1;

    int xdel = *xdpointer;
    int ydel = *ydpointer;

    int freeMovement = 1;
    //top
    if (ydel == -1) {
        u16 topLeft = checkPixel(topY + ydel, leftX);
        u16 topRight = checkPixel(topY + ydel, rightX);
        if (topLeft == BLACK || topLeft == vCol || topRight == BLACK || topRight == vCol) {
            *ydpointer = 0;
            freeMovement = 0;
        }
    }
    //bottom
    if (ydel == 1) {
        u16 bottomLeft = checkPixel(bottomY + ydel, leftX);
        u16 bottomRight = checkPixel(bottomY + ydel, rightX);
        if (bottomLeft == BLACK || bottomLeft == vCol || bottomRight == BLACK || bottomRight == vCol) {
            *ydpointer = 0;
            freeMovement = 0;
        }
    }
    //left
    if (xdel == -1) {
        u16 leftTop = checkPixel(topY, leftX + xdel);
        u16 leftBottom = checkPixel(bottomY, leftX + xdel);
        if (leftTop == BLACK || leftTop == vCol || leftBottom == BLACK || leftBottom == vCol) {
            *xdpointer = 0;
            freeMovement = 0;
        }
    }
    //right
    if (xdel == 1) {
        u16 rightTop = checkPixel(topY, rightX + xdel);
        u16 rightBottom = checkPixel(bottomY, rightX + xdel);
        if (rightTop == BLACK || rightTop == vCol || rightBottom == BLACK || rightBottom == vCol) {
            *xdpointer = 0;
            freeMovement = 0;
        }
    }

    if (freeMovement && ydel != 0 && xdel != 0) {
        u16 diagonal;
        if (xdel == -1 && ydel == -1) {
            diagonal = checkPixel(topY + ydel, leftX + xdel);
        } else if (xdel == 1 && ydel == -1) {
            diagonal = checkPixel(topY + ydel, rightX + xdel);
        } else if (xdel == -1 && ydel == 1) {
            diagonal = checkPixel(bottomY + ydel, leftX + xdel);
        } else {
            diagonal = checkPixel(bottomY + ydel, rightX + xdel);
        }

        if (diagonal == BLACK) {
            *xdpointer = 0;
            *ydpointer = 0;
        }
    }

    player->x = player->x + *xdpointer;
    player->y = player->y + *ydpointer;
    return ((*xdpointer != 0) || (*ydpointer != 0));
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
    if (!state->player->pickupCollected) {
        return 0;
    }
    int x = state->player->x;
    int y = state->player->y;
    return (checkPixel(y, x + PLAYER_SIZE) == vCol || checkPixel(y + PLAYER_SIZE, x) == vCol
                || checkPixel(y - 1, x) == vCol || checkPixel(y, x - 1) == vCol);
}

int checkDeath(GameState* state) {
    int playerX1 = state->player->x;
    int playerX2 = state->player->x + PLAYER_SIZE - 1;
    int playerY1 = state->player->y;
    int playerY2 = state->player->y + PLAYER_SIZE - 1;
    int hasCollided = 0;
    int index = 0;
    ENEMY* enemies = state->currentLevel->enemies;
    while (index < state->currentLevel->numEnemies && !hasCollided) {
        ENEMY current = *(enemies + index++);
        //enemyX1 = current.x;
        int enemyX2 = current.x + ENEMY_SIZE - 1;
        //enemyY1 = current.y;
        int enemyY2 = current.y + ENEMY_SIZE - 1;

        hasCollided = (playerX1 <= enemyX2) && (playerX2 >= current.x) && (playerY1 <= enemyY2) && (playerY2 >= current.y);
    }
    if (hasCollided) {
        drawRect(playerY1, playerX1, PLAYER_SIZE, PLAYER_SIZE, WHITE);
        state->player->pickupCollected = !state->currentLevel->hasPickup;
    }
    return hasCollided;
}

int checkPickupCollision(PLAYER* player, int pickupX1, int pickupY1) {
    int playerX2 = player->x + PLAYER_SIZE - 1;
    int playerY2 = player->y + PLAYER_SIZE - 1;

    int pickupX2 = pickupX1 + PICKUP_SIZE - 1;
    int pickupY2 = pickupY1 + PICKUP_SIZE - 1;

    return (player->x <= pickupX2) && (playerX2 >= pickupX1) && (player->y <= pickupY2) && (playerY2 >= pickupY1);
}

ENEMY level1E[] = {
    {69, 26, 1, UP},
    {45, 48, 2, RIGHT},
    {187, 62, 2, LEFT},
    {45, 76, 2, RIGHT},
    {187, 90, 2, LEFT},
    {146, 113, 1, DOWN}
};

ENEMY level2E[] = {
    {206, 69, 2, LEFT}
};

ENEMY level3E[] = {
    {55, 57, 1, RIGHT},
    {85, 69, 1, LEFT},
    {55, 81, 1, RIGHT},
    {85, 93, 1, LEFT},
    {147, 57, 1, RIGHT},
    {177, 69, 1, LEFT},
    {147, 81, 1, RIGHT},
    {177, 93, 1, LEFT}
};

ENEMY level4E[] = {
    {29, 127, 1, UP},
    {26, 40, 3, RIGHT},
    {203, 37, 1, DOWN},
    {206, 124, 3, LEFT},
    {97, 99, 1, RIGHT}
};

int numLevels = 4;
LEVEL levels[] = {
    {level1, 6, level1E, 0, {0, 0}, 14, 14, 1},
    {level2, 1, level2E, 0, {0, 0}, 26, 57, 2},
    {level3, 8, level3E, 0, {0, 0}, 102, 28, 3},
    {level4, 5, level4E, 1, {116, 17}, 116, 71, 4}
};
