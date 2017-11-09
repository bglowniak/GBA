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
    int numEnemies;
    ENEMY* enemies;
    int playerStartX;
    int playerStartY;
} LEVEL;

typedef struct {
	PLAYER* player;
	LEVEL* currentLevel;
} GameState;

void drawGame(GameState* pointer);
extern void drawSquareDude(int r, int c);
extern void drawCircleEnemy(int r, int c);
