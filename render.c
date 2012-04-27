#include "main.h"
#include <SDL.h>

void RenderLevel()
{
	int x, y, i, j;
	int animated = -1;  // toggles wether the block is animated or not
	int whichani;

	beginX = player[chosenGuy].coord_x - (viewX/2);
	beginY = player[chosenGuy].coord_y - (viewY/2);

	// render level
	for (j=0; j<2; j++) {
		for (x=(viewX+beginX); x>=beginX; x--) {
			for (y=beginY; y<=(viewY+beginY); y++) {

				if ((( x <= levelsizeX-1 ) && ( y <= levelsizeY-1 )) && (( x >= 0 ) && ( y >= 0)))
					// only render stuff that really exists

					switch ( level.data[x][y] )
					{
						case B_TOGGLE1:
							// these are toggleable blocks. we have to check here wether they
							// are toggled or not.
							if ( toggleBlocks == 0)
							{
								blitMe = B_TOGGLE1;
								blockHeight[blitMe] = 1;
							} else {
								blitMe = B_TOGGLE2;
								blockHeight[blitMe] = 0;
							}
							break;
						case B_TOGGLE2:
							if ( toggleBlocks == 1)
							{
								blitMe = B_TOGGLE1;
								blockHeight[blitMe] = 1;
							} else {
								blitMe = B_TOGGLE2;
								blockHeight[blitMe] = 0;
							}
							break;
						case B_FIRE:
							whichani = 0;
							animated = 1;
						default:
							blitMe = level.data[x][y];
							break;
					}
				else
					// else fill it with an air block
					blitMe = B_AIR;


				renderX = ((x-beginX)*22) - viewStartX + (y*22) - (player[chosenGuy].coord_y*22);
				// check block height, for 3d effect
				if ( (blockHeight[blitMe] == 0))
					//renderY = ((y-beginY)*22) - viewStartY - (x*22) + (player[chosenGuy].coord_x*22);
					renderY = ((y-beginY)*22) - viewStartY - (x*22) + (player[chosenGuy].coord_x*22) + (25*j);
				else
					//renderY = ((y-beginY)*22) - viewStartY - (x*22) + (player[chosenGuy].coord_x*22) - 25;
					renderY = ((y-beginY)*22) - viewStartY - (x*22) + (player[chosenGuy].coord_x*22) - 25 + (25*j);


				// finally, draw our block
				//if (( renderX < 540  && renderY < 480 ) || ( renderX > (-60 + (BLOCKHEIGHT*j)) &&
					//renderY > (-40 + (BLOCKHEIGHT*j)) ))
				if (( renderX < 540  && renderY < 480 ) || ( renderX > -60 && renderY > -40))
				{
					if ( animated == -1 )
						//BlitImage(block[blitMe], screen, renderX, renderY);
						if (j==0)
							//BlitImageAlpha(block[blitMe], screen, renderX, renderY, 255);
							BlitImage(block[blitMe], screen, renderX, renderY);
						else
							//BlitImageAlpha(block[blitMe], screen, renderX, renderY, 160);
							BlitImage(block[blitMe], screen, renderX, renderY);
					else {
						if (animation[whichani].random == 1) animation[whichani].currentphase = rand() % animation[whichani].numphases;
						BlitImage(animation[whichani].gfx[animation[whichani].currentphase], screen, renderX, renderY);
						//BlitImageAlpha(animation[whichani].gfx[animation[whichani].currentphase], screen, renderX, renderY, 255-(j*255));
						animated = -1;
					}
				}

				// ...and the guy, if necessary
				for (i=0; i<playerCount; i++) {
					if ((player[i].coord_x == x) && (player[i].coord_y == y))
					{
						if ( blockHeight[blitMe] == 0)
						{
							BlitImage(characters[player[i].direction], screen, renderX + 15, renderY - 25);
						} else {
							BlitImage(characters[player[i].direction], screen, renderX + 15, renderY + 5);
						}
					}
				}
				// yellow triangle
				BlitImage(characters[4], screen, 327, 193);
			}
		}
	}
}

void BlitImage(SDL_Surface *block, SDL_Surface *screen, int x, int y)
{
    SDL_Rect dest;

    dest.x = x;
    dest.y = y;
	dest.w = block->w;
    dest.h = block->h;
	//SDL_SetAlpha(block, SDL_SRCALPHA, 128);
	SDL_BlitSurface(block, NULL, screen, &dest);
}

void BlitImageAlpha(SDL_Surface *block, SDL_Surface *screen, int x, int y, int alpha)
{
    SDL_Rect dest;

    dest.x = x;
    dest.y = y;
	dest.w = block->w;
    dest.h = block->h;
	SDL_SetAlpha(block, SDL_SRCALPHA, alpha);
	SDL_BlitSurface(block, NULL, screen, &dest);
}
