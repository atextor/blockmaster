#include "main.h"

void LoadTheme(char themename[])
{		
	char blockToFile[] = "00010202030405060708091011121314151617181920212223";
	char charToFile[] = "01234";
	char menuToFile[] = "01234";
	char aniToFile[] = "01";
	char aniphaseToFile[] = "abcdefghij";
	char fullpath[80];
    char blockfilename[] = "blockXX.bmp";
	char charfilename[] = "guyX.bmp";
	char menufilename[] = "menuX.bmp";
	char anifilename[] = "aniXXY.bmp";
	int i, j;

	printf (" Loading Theme %s...\n", themename);
	
	// block graphics
    for (i = 0; i<BLOCKCOUNT; i++) {
		blockfilename[5] = blockToFile[(i*2)];
        blockfilename[6] = blockToFile[(i*2)+1];
		sprintf(fullpath, "%s%s/%s", path.themes, themename, blockfilename);
		
        block[i] = SDL_LoadBMP(fullpath);
		if (!block[i]) {
            printf ("*** Loading of %s failed.\n", fullpath);
			quit(1);
		}
		
		SDL_SetColorKey(block[i], SDL_SRCCOLORKEY, 0);
    }
	
	// animations
	for (i = 0; i<ANIMATIONCOUNT; i++) {
		anifilename[3] = aniToFile[(i*2)];
		anifilename[4] = aniToFile[(i*2)+1];
		for (j = 0; j<animation[i].numphases; j++) {
			anifilename[5] = aniphaseToFile[j];
			sprintf(fullpath, "%s%s/%s", path.themes, themename, anifilename);
			
			animation[i].gfx[j] = SDL_LoadBMP(fullpath);
			if (!animation[i].gfx[j]) {
				printf ("*** Loading of %s failed.\n", fullpath);
				quit(1);
			}
			SDL_SetColorKey(animation[i].gfx[j], SDL_SRCCOLORKEY, 0);
			SDL_SetAlpha(animation[0].gfx[j], SDL_SRCALPHA, 100);
		}
	}
	
		
	// character graphics
	for (i = 0; i<5; i++) {
		charfilename[3] = charToFile[i];
		sprintf(fullpath, "%s%s/%s", path.themes, themename, charfilename);
		
		characters[i] = SDL_LoadBMP(fullpath);
		if (!characters[i]) {
			printf("*** Loading of %s failed.\n", fullpath);
			quit(1);
		}
		
		SDL_SetColorKey(characters[i], SDL_SRCCOLORKEY, 0);
	}
	// yellow triangle transparency
	SDL_SetAlpha(characters[4], SDL_SRCALPHA, 15);
	
	// font
	sprintf(fullpath, "%s%s/font.bmp", path.themes, themename);
	font[0] = SDL_LoadBMP(fullpath);

	if (!font[0]) {
		printf( "*** Loading of %s failed.\n", fullpath);
		quit(1);
	}
		
	SDL_SetColorKey(font[0], SDL_SRCCOLORKEY, 0);
	InitFont(font[0]);
	
	// menu
	for (i = 0; i<5; i++) {
		menufilename[4] = menuToFile[i];
		sprintf(fullpath, "%s%s/%s", path.themes, themename, menufilename);
	
		menu[i] = SDL_LoadBMP(fullpath);
		if (!menu[i]) {
			printf("*** Loading of %s failed.\n", fullpath);
			quit(1);
		}
		
		SDL_SetColorKey(menu[i], SDL_SRCCOLORKEY, 0);
	}
}
