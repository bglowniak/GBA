//x represents column
//y represents row
typedef struct {
    int x;
    int y;
    int deaths;
    int pickupCollected;
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
    int x;
    int y;
} PICKUP;

typedef struct {
    const unsigned short* backgroundImage;
    int numEnemies;
    ENEMY* enemies;
    int hasPickup;
    PICKUP pickup;
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
int movePlayer(PLAYER* player, int* xdpointer, int* ydpointer);
void moveEnemy(ENEMY* enemy);
int checkVictory(GameState* state);
int checkDeath(GameState* state);
int checkPickupCollision(PLAYER* player, int pickupX1, int pickupY1);
extern void drawSquareDude(int r, int c);
extern void drawCircleEnemy(int r, int c);
extern void drawRect(int r, int c, int width, int height, unsigned short color);
extern void drawString(int r, int c, char str[], unsigned short color);
extern unsigned short checkPixel(int r, int c);
extern void drawTrianglePickup(int r, int c);
