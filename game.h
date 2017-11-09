typedef struct {
    int x;
    int y;
    int deaths;
} PLAYER;

typedef struct {
    int startX;
    int startY;
    int currentX;
    int currentY;
    int endX;
    int endY;
} ENEMY;

typedef struct {
    u32 numEnemies;
    u16 backgroundColor;
    const u16* backgroundImage;
    struct ENEMY* enemies;
} LEVEL;
