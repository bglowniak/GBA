//Function Prototypes
void drawImage3(int r, int c, int width, int height, const unsigned short* image);
void setPixel(int r, int c, unsigned short color);
unsigned short checkPixel(int r, int c);
void drawRect(int r, int c, int width, int height, unsigned short color);
void drawChar(int r, int c, char ch, unsigned short color);
void drawString(int r, int c, char str[], unsigned short color);
void drawSplashScreen();
void drawGameOver();
void clearScreen();
void drawSquareDude(int r, int c);
void drawCircleEnemy(int r, int c);
