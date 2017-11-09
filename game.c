#include "level1.h"
#include "game.h"

ENEMY level1E[] = {
    {65, 24, 1, UP},
    {45, 46, 1, RIGHT},
    {45, 46, 1, RIGHT},
    {188, 61, -1, LEFT},
    {45, 76, 1, RIGHT},
    {188, 91, -1, LEFT},
    {45, 106, 1, RIGHT},
    {146, 125, -1, DOWN}
};

LEVEL level_1 = {level1, level1E, 14, 14};
