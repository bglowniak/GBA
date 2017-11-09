//x represents column
//y represents row

typedef struct {
    int x;
    int y;
    int deaths;
} PLAYER;

enum Direction {
    UP,
    DOWN,
    LEFT,
    RIGHT
};

typedef struct {
    int x;
    int y;
    int velocity;
    enum Direction startD;
} ENEMY;

typedef struct {
    const unsigned short* backgroundImage;
    ENEMY* enemies;
    int playerStartX;
    int playerStartY;
} LEVEL;
