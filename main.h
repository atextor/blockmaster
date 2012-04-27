#include <SDL.h>
#include <stdlib.h>
#include <stdio.h>
#include "settings.h"
#include "sfont.h"

// functions
Uint32 time_left(void);
void RenderLevel();
void BlitImage(SDL_Surface *block, SDL_Surface *screen, int x, int y);
void BlitImageAlpha(SDL_Surface *block, SDL_Surface *screen, int x, int y, int alpha);
void LoadLevel(char levelfile[]);
void LevelInfo(char *info, char *param);
void ReadConfig(char *configfile);
void ConfigSetting(char *setting, char *param, int line);
void removeBlock(int x, int y);
int takeItem(int x, int y);
int hasBlockBit(int x, int y, int Bit);

// structures
struct tGraphicSettings {
    int fullscreen;
	Uint32 videoflags;
} vid;

struct tPathSettings {
    char data[255];
    char levels[255];
    char themes[255];
} path;

struct tLevel {
	int data[150][150];
	int size_x;
	int size_y;
	char title[80];
	char author[80];
    char desc[255];
    char difficulty[80];
	char theme[80];
    char message1[255];
    char message2[255];
    char message3[255];
    char message4[255];
    char message5[255];
} level;

struct tLiving {
    int 	coord_x;
	int		coord_y;
    int 	direction;
	float	animation_x;
	float	animation_y;
} player[3];

struct tAnimation {
	SDL_Surface *gfx[10];
	int 		numphases;
	int			currentphase;
	int			tickcount;
	int 		random;
} animation[ANIMATIONCOUNT];

struct tInventory {
	int redKeys;
	int blueKeys;
	int greenKeys;
	int yellowKeys;
	int flippers;
	int fireshoes;
} inventory;

// variables
extern int running;

extern int chosenGuy;
extern int playerCount;
extern int levelsizeX;
extern int levelsizeY;
extern int blockHeight[25];

extern int blitMe;
extern int toggleBlocks;
extern const int viewX;
extern const int viewY;
extern const int viewStartX;
extern const int viewStartY;

extern int beginX;
extern int beginY;
extern int renderX;
extern int renderY;

extern Uint32 now;

extern SDL_Surface *screen;
extern SDL_Surface *menu[4];
extern SDL_Surface *block[27];
extern SDL_Surface *characters[5];
extern SDL_Surface *font[1];
