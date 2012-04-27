#include "main.h"

void removeBlock(int x, int y)
{
	/* 	Function: removeBlock
		Purpose:  Replace the Block at x,y with 0 (air)
	*/
	
	level.data[x][y] = B_AIR;
	// wow this was hard
}


int takeItem(int x, int y)
{
	/* 	Function: takeItem
		Purpose:  Take an item located at x,y and remove it on the map
	*/
	
	// if we can't take it, return
	//if ( hasBlockBit(x, y, ISFETCHABLE) == 0) return 0;
		
	switch ( level.data[x][y] )
	{
		case B_REDKEY:
			inventory.redKeys++;
			removeBlock(x, y);
			break;
		case B_GREENKEY:
			inventory.greenKeys++;
			removeBlock(x, y);
			break;
		case B_BLUEKEY:
			inventory.blueKeys++;
			removeBlock(x, y);
			break;
		case B_YELLOWKEY:
			inventory.yellowKeys++;
			removeBlock(x, y);
			break;
		default:
			return 0;
			break;
	}
	
	return 1;
}

void movePlayer(int whichPlayer, int direction)
{
	/* 	Function: movePlayer
		Purpose:  Move a Player to a certain direction
	*/
	
	int targetBlock, targetX, targetY, targetX2, targetY2;
	switch ( direction )
	{
		case UP:   
			targetX = player[whichPlayer].coord_x;
			targetY = player[whichPlayer].coord_y - 1; 
			targetX2 = player[whichPlayer].coord_x;
			targetY2 = player[whichPlayer].coord_y - 2;
			break;
		case DOWN: 
			targetX = player[whichPlayer].coord_x;
			targetY = player[whichPlayer].coord_y + 1; 
			targetX2 = player[whichPlayer].coord_x;
			targetY2 = player[whichPlayer].coord_y + 2;
			break;
		case LEFT: 
			targetX = player[whichPlayer].coord_x - 1;
			targetY = player[whichPlayer].coord_y;
			targetX2 = player[whichPlayer].coord_x - 2;
			targetY2 = player[whichPlayer].coord_y;
			break;
		case RIGHT:
			targetX = player[whichPlayer].coord_x + 1;
			targetY = player[whichPlayer].coord_y;
			targetX2 = player[whichPlayer].coord_x + 2;
			targetY2 = player[whichPlayer].coord_y;
			break;
	}
	
	targetBlock = level.data[targetX][targetY];
	
	// item
	if ( hasBlockBit(targetX, targetY, ISFETCHABLE) ) {
		takeItem(targetX, targetY);
	}
	
	// movable block
	if ( hasBlockBit(targetX, targetY, ISMOVABLE) ) {
		// water or hole
		if ( hasBlockBit(targetX2, targetY2, ISBLOCKDESTROYER) ) {
			removeBlock(targetX2, targetY2);	
			removeBlock(targetX, targetY);
		// other block container
		} else if ( hasBlockBit(targetX2, targetY2, ISBLOCKCONTAINER) ) {
			level.data[targetX2][targetY2] = level.data[targetX][targetY];
			removeBlock(targetX, targetY);
			addActivity(targetX, targetY, BLOCKMOVE);
		}
	}
	
	// arrow fields
	if ( (level.data[targetX][targetY] == B_UPARROW) ||
		 (level.data[targetX][targetY] == B_DOWNARROW) ||
		 (level.data[targetX][targetY] == B_RIGHTARROW) ||
		 (level.data[targetX][targetY] == B_LEFTARROW)) {
		addActivity(targetX, targetY, PLAYERMOVE);
	}

	// doors	
	if (targetBlock == B_REDDOOR) {
		inventory.redKeys--;
		removeBlock(targetX, targetY);
	}
	if (targetBlock == B_GREENDOOR) {
		inventory.greenKeys--;
		removeBlock(targetX, targetY);
	}
	if (targetBlock == B_BLUEDOOR) {
		inventory.blueKeys--;
		removeBlock(targetX, targetY);
	}
	if (targetBlock == B_YELLOWDOOR) {
		inventory.yellowKeys--;
		removeBlock(targetX, targetY);
	}
	
	// toggle button
	if (targetBlock == B_BUTTON) {
		toggleBlocks = !toggleBlocks;	
	}

	// general player movement	
	if ( hasBlockBit(targetX, targetY, ISWALKABLE) ) {
		player[whichPlayer].coord_x = targetX;
		player[whichPlayer].coord_y = targetY;		
	}
	// TODO
	// broken floor
	// finish
	// fake wall (air)
	// water w/ flippers
	// fire w/ fireshoes
	
	return;
	
}

int hasBlockBit(int x, int y, int Bit)
{
	/* 	Function: hasBlockBit
		Purpose: Check if a given block has a certain bit
		Returns: 1 if the bit is set
				 0 if the bit isn't set
	*/

	switch( level.data[x][y] )
	{
		case B_AIR: 
			if ((Bit == ISWALKABLE) || (Bit == ISBLOCKCONTAINER)) return 1;
			break;
		case B_WALL: 
			break;
		case B_FAKEAIR: 
			if ((Bit == ISWALKABLE) || (Bit == ISBLOCKCONTAINER)) return 1;
			break;
		case B_FAKEWALL: 
			if (Bit == ISWALKABLE) return 1;
			break;
		case B_LEFTARROW: 
			if ((Bit == ISWALKABLE) || (Bit == ISBLOCKCONTAINER)) return 1;
			break;
		case B_UPARROW: 
			if ((Bit == ISWALKABLE) || (Bit == ISBLOCKCONTAINER)) return 1;
			break;
		case B_RIGHTARROW: 
			if ((Bit == ISWALKABLE) || (Bit == ISBLOCKCONTAINER)) return 1;
			break;
		case B_DOWNARROW:
			if ((Bit == ISWALKABLE) || (Bit == ISBLOCKCONTAINER)) return 1;
			break;
		case B_HOLE: 
			if ((Bit == ISBLOCKCONTAINER) || (Bit == ISBLOCKDESTROYER)) return 1;
			break;
		case B_BLOCK:
			switch( player[chosenGuy].direction ) {
				case DOWN:
					if ( hasBlockBit(x, y+1, ISBLOCKCONTAINER) == 1) 
						if ((Bit == ISWALKABLE) || (Bit == ISMOVABLE)) return 1;
					break;
				case RIGHT:
					if ( hasBlockBit(x+1, y, ISBLOCKCONTAINER) == 1)
						if ((Bit == ISWALKABLE) || (Bit == ISMOVABLE)) return 1;
					break;
				case UP: 
					if ( hasBlockBit(x, y-1, ISBLOCKCONTAINER) == 1)
						if ((Bit == ISWALKABLE) || (Bit == ISMOVABLE)) return 1;
					break;
				case LEFT:
					if ( hasBlockBit(x-1, y, ISBLOCKCONTAINER) == 1)
						if ((Bit == ISWALKABLE) || (Bit == ISMOVABLE)) return 1;
					break;
			}
			break;
		case B_BROKENFLOOR: 
			if ((Bit == ISWALKABLE) || (Bit == ISBLOCKCONTAINER)) return 1;
			break;
		case B_FINISH:
			if (Bit == ISWALKABLE) return 1;
			break;
		case B_REDKEY:
			if ((Bit == ISWALKABLE) || (Bit == ISFETCHABLE)) return 1;
			break;
		case B_GREENKEY: 
			if ((Bit == ISWALKABLE) || (Bit == ISFETCHABLE)) return 1;	
			break;
		case B_BLUEKEY:
			if ((Bit == ISWALKABLE) || (Bit == ISFETCHABLE)) return 1;	
			break;
		case B_YELLOWKEY:
			if ((Bit == ISWALKABLE) || (Bit == ISFETCHABLE)) return 1;
			break;
		case B_REDDOOR:
			if (inventory.redKeys > 0)
				if ((Bit == ISWALKABLE) || (Bit == ISDOOR)) return 1;
			break;
		case B_GREENDOOR:
			if (inventory.greenKeys > 0)
				if ((Bit == ISWALKABLE) || (Bit == ISDOOR)) return 1;
			break;
		case B_BLUEDOOR:
			if (inventory.blueKeys > 0)
				if ((Bit == ISWALKABLE) || (Bit == ISDOOR)) return 1;
			break;
		case B_YELLOWDOOR:
			if (inventory.yellowKeys > 0)
				if ((Bit == ISWALKABLE) || (Bit == ISDOOR)) return 1;
			break;
		case B_BUTTON:
			if ((Bit == ISWALKABLE) || (Bit == ISBLOCKCONTAINER)) return 1;	
			break;
		case B_TOGGLE1:
			if (toggleBlocks == 1) // in this case: floor
				if ((Bit == ISWALKABLE) || (Bit == ISBLOCKCONTAINER)) return 1;
			break;
		case B_TOGGLE2:
			if (toggleBlocks == 0) // in this case: floor
				if ((Bit == ISWALKABLE) || (Bit == ISBLOCKCONTAINER)) return 1;
			break;
		case B_WATER:
			if (inventory.flippers > 0)
				if ((Bit == ISWALKABLE) || (Bit == ISBLOCKCONTAINER) || 
					(Bit == ISBLOCKDESTROYER)) return 1;
			else
				if ((Bit == ISBLOCKCONTAINER) || (Bit == ISBLOCKDESTROYER)) return 1;
			break;
		case B_FIRE:
			if (inventory.fireshoes > 0)
				if (Bit == ISWALKABLE) return 1;
			break;
	}
	
	return 0;
	
}
