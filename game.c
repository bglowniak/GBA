#include "level1.h"
#include "game.h"

void drawGame(GameState* pointer) {
    GameState state = *pointer;
    PLAYER player = *(state.player);
    drawSquareDude(player.x, player.y);

    LEVEL level = *(state.currentLevel);
    ENEMY* enemies = level.enemies;
    for (int i = 0; i <= level.numEnemies; i++) {
        ENEMY enemy = *(enemies + i);
        drawCircleEnemy(enemy.y, enemy.x);
    }
}

ENEMY level1E[] = {
    {65, 28, 1, UP},
    {45, 46, 1, RIGHT},
    {45, 46, 1, RIGHT},
    {188, 61, -1, LEFT},
    {45, 76, 1, RIGHT},
    {188, 91, -1, LEFT},
    {45, 106, 1, RIGHT},
    {146, 125, -1, DOWN}
};

LEVEL level_1 = {level1, 7, level1E, 14, 14};
