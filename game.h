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
    enum Direction direction;
} ENEMY;

typedef struct {
    const unsigned short* backgroundImage;
    int numEnemies;
    ENEMY* enemies;
    int playerStartX;
    int playerStartY;
    int levelID;
} LEVEL;

typedef struct {
	PLAYER* player;
	LEVEL* currentLevel;
} GameState;

void drawGame(GameState* pointer);
void processMovements(GameState* state);
int movePlayer(PLAYER* player, int* xdel, int* ydel);
void moveEnemy(ENEMY* enemy);
int checkVictory(GameState* state);
int checkDeath(GameState* state);
extern void drawSquareDude(int r, int c);
extern void drawCircleEnemy(int r, int c);
extern void drawRect(int r, int c, int width, int height, unsigned short color);
extern unsigned short checkPixel(int r, int c);
