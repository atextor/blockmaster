#include "main.h"

// ------------
// variables
// ------------

// loop param
int running = 1;

int playerCount = 3;
int chosenGuy = 0;

// level size... what to say?
int levelsizeX = 150;
int levelsizeY = 150;

// this will hold the block-id to be rendered
// in the level-rendering section
int blitMe = 0;

// are the toggleable wall/air blocks toggled?
int toggleBlocks = 0;

// size of view (viewX x viewY blocks visible)
const int viewX = 25;
const int viewY = 40;

// x and y coords of leftupper viewfield corner
//const int viewStartX = 13;
//const int viewStartY = 40;
const int viewStartX = -50;
const int viewStartY = 200;

// where to begin with level rendering
int beginX = 0;
int beginY = 0;
int renderX = 0;
int renderY = 0;

// block heightmap
// stores information about which blocks should be drawn
// raised, and which should not
int blockHeight[25] = {
	0, 1, 1, 1, 0, 0, 0, 0, 0, 1, 0, 1, 0,
	0, 0, 0, 1, 1, 1, 1, 0, 1, 1, 0, 1
	};

// stores all the images
SDL_Surface *screen;
SDL_Surface *menu[4];
SDL_Surface *font[1];
SDL_Surface *block[27];
SDL_Surface *characters[5];

// other variables
char string[80];
int x, y, i;
static Uint32 next_time;
Uint32 now;

// ------------
// functions
// ------------
Uint32 time_left(void)
{
	now = SDL_GetTicks();
    if(next_time <= now)
        return 0;
    else
        return next_time - now;
}

int HandleAfterWalk(int x, int y)
{
	/*	Function: HandleAfterWalk
		Purpose: After walking to a direction, this function
			checks and does what has to be done to the stone
			we WERE standing on
		Returns: 1
		x,y: coordinates of the block to process */

	switch( level.data[x][y] )
	{
		case B_BROKENFLOOR :
			// this is splinted floor. this
			// has to be replaced with a hole.
			level.data[x][y] = 8;
			return 1;
			break;
		default:
			// default, this could be for example floor.
			// we do not change anything at the floor.
			return 1;
			break;
	}

}

int main(int argc, char *argv[])
{

	char rc_file[255];
	char levelToLoad[] = "1";
    int i;
	SDL_Event event; // keyboard handling

	// default values
	inventory.redKeys = 0;
	inventory.greenKeys = 0;
	inventory.blueKeys = 0;
	inventory.yellowKeys = 0;

  vid.fullscreen = FULLSCREEN_DEFAULT;
	vid.videoflags = SDL_SWSURFACE;
	strcpy(level.theme, DEFAULTTHEME);
	sprintf(path.levels, "%s%s", DATAPATH_DEFAULT, LEVELPATH);
	sprintf(path.themes, "%s%s", DATAPATH_DEFAULT, THEMEPATH);
	animation[0].numphases = 4; // fire animation
	animation[0].tickcount = 1;
	animation[0].random = 1;

  // set up rcfile
  sprintf(rc_file, "%s/.blockmasterrc", getenv("HOME"));

	// check for arguments setting the configfile or requesting help
	for ( i=1; argv[i]; ++i ) {
		if ((strcmp(argv[i], "--config") == 0) || (strcmp(argv[i], "-c") == 0)) {
			// set new config file
			sprintf(rc_file, "%s", argv[i+1]);
		}

		if ((strcmp(argv[i], "--help") == 0 ) || (strcmp(argv[i], "-h") == 0)) {
			printf("\nBlockmaster v%d.%d%d\n-----------------\n", VERSION_MAJOR, VERSION_MINOR, VERSION_REV);
			printf("-h or --help             : display this message\n");
			printf("-f or --fullscreen       : select fullscreen display\n");
			printf("-w or --window           : select window display (default)\n");
			printf("-l # or --level #        : load level number #\n");
			printf("-c file or --config file : specify config file other than ~/.blockmasterrc\n");
			printf("\n");
			exit(1);
		}

	}

	// read config
	//ReadConfig(rc_file);

	// check command line for arguments that may override the config settings
	for ( i=1; argv[i]; ++i ) {
		if ((strcmp(argv[i], "--fullscreen") == 0) || (strcmp(argv[i], "-f") == 0))
			vid.fullscreen = TRUE;

		if ((strcmp(argv[i], "--window") == 0 ) || (strcmp(argv[i], "-w") == 0))
			vid.fullscreen = FALSE;

		if ((strcmp(argv[i], "--level") == 0) || (strcmp(argv[i], "-l") == 0)) {
			strcpy(levelToLoad, argv[i+1]);
		}

	}

	// initialize SDL

	// create surface
	if (SDL_Init (SDL_INIT_VIDEO) < 0) {
		fprintf(stdout, "*** Error: Init failed: %s\n", SDL_GetError());
		exit(1);
	}

	// clean up on exit
	atexit(SDL_Quit);

	// create screen
	if (vid.fullscreen == 1)
		vid.videoflags = SDL_FULLSCREEN;
	else
		vid.videoflags = SDL_SWSURFACE;

	screen = SDL_SetVideoMode(640, 480, 16, vid.videoflags);
	if ( screen == NULL) {
		fprintf(stdout, "*** Error: 640x480x16 not possible: %s\n", SDL_GetError());
		exit(1);
	}

	// ignore mouse / focus events
	SDL_EventState(SDL_ACTIVEEVENT, SDL_IGNORE);
	SDL_EventState(SDL_MOUSEMOTION, SDL_IGNORE);

/* -- INITIALIZATION COMPLETE -- */

/* -- BEGIN MAIN PROGRAM LOOP -- */

	// will load level data and all graphics
	// (the theme according to the level)
	LoadLevel(levelToLoad);

	// enable unicode translation
	SDL_EnableUNICODE( 1 );

	SDL_SetAlpha(block[11], SDL_SRCALPHA, 100);
	SDL_SetAlpha(block[24], SDL_SRCALPHA, 100);

	// set window caption
	sprintf(string, "Blockmaster v0.00 - %s by %s", level.title, level.author);
	SDL_WM_SetCaption(string, NULL);

	// ticker
    next_time = SDL_GetTicks() + TICK_INTERVAL;

	while (running == 1) {

  // loop until SDL_Quit event is found
  // or escape key is pressed
    while( SDL_PollEvent( &event ) ) {
    switch( event.type ) {
        case SDL_KEYDOWN:
          switch( event.key.keysym.sym ) {
          case SDLK_LEFT:// || SDLK_h:
            player[chosenGuy].direction = LEFT;
            if(hasBlockBit(player[chosenGuy].coord_x-1, player[chosenGuy].coord_y, ISWALKABLE) == 1)
              movePlayer(chosenGuy,player[chosenGuy].direction);
            break;
          case SDLK_RIGHT: // || SDLK_l:
            player[chosenGuy].direction = RIGHT;
            if(hasBlockBit(player[chosenGuy].coord_x+1, player[chosenGuy].coord_y, ISWALKABLE) == 1)
              movePlayer(chosenGuy,player[chosenGuy].direction);
            break;
          case SDLK_UP: // || SDLK_k:
            player[chosenGuy].direction = UP;
            if(hasBlockBit(player[chosenGuy].coord_x, player[chosenGuy].coord_y-1, ISWALKABLE) == 1)
              movePlayer(chosenGuy,player[chosenGuy].direction);
            break;
          case SDLK_DOWN: // || SDLK_j:
            player[chosenGuy].direction = DOWN;
            if(hasBlockBit(player[chosenGuy].coord_x, player[chosenGuy].coord_y+1, ISWALKABLE) == 1)
              movePlayer(chosenGuy,player[chosenGuy].direction);
            break;
          case SDLK_SPACE:
            chosenGuy++;
            if (chosenGuy == playerCount) chosenGuy = 0;
            break;
          case SDLK_ESCAPE:
            running = 0;
            break;
          case SDLK_q:
            running = 0;
            break;
          default:
            break;
          }

          break;
        case SDL_KEYUP:
          break;
        case SDL_QUIT:
          running = 0;
          break;
        default:
          break;
       }
			}

			RenderLevel();

			// process animations
			for (i = 0; i<ANIMATIONCOUNT; i++) {
				// check for tick interval
				if (now % animation[i].tickcount == 0) {
					animation[i].currentphase++;
					if (animation[i].currentphase >= animation[i].numphases)
						animation[i].currentphase = 0;
				}
			}

			// not to forget our menu
			BlitImage(menu[0], screen, 539, 0);

			// print stuff
			PutString(screen,560,150,"Keys:");
			BlitImage(menu[1],screen,550,170);
			BlitImage(menu[2],screen,590,170);
			BlitImage(menu[3],screen,550,220);
			BlitImage(menu[4],screen,590,220);
			sprintf(string,"%d",inventory.greenKeys);
			PutString(screen,570,190,string);
			sprintf(string,"%d",inventory.blueKeys);
			PutString(screen,610,190,string);
			sprintf(string,"%d",inventory.yellowKeys);
			PutString(screen,570,240,string);
			sprintf(string,"%d",inventory.redKeys);
			PutString(screen,610,240,string);

			sprintf(string,"%d",now);
			PutString(screen,5,5,string);

			// update the whole screen
			SDL_UpdateRect(screen, 0, 0, 0, 0);

			// game delay
			SDL_Delay(time_left());
			next_time += TICK_INTERVAL;
        }
	quit(0);
}
