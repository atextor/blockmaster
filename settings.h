// game version & other stuff
#define VERSION_MAJOR 0
#define VERSION_MINOR 0
#define VERSION_REV 0

#define TRUE 1
#define FALSE 0
#define COMMENT '#'
#define BUFLEN 8192
#define COMMANDLINE -1
#define TICK_INTERVAL 1

// graphics
#define FULLSCREEN_DEFAULT FALSE
#define SCREEN_WIDTH_DEFAULT 800      // we want our screen width 800 pixels
#define SCREEN_HEIGHT_DEFAULT 600     // we want our screen height 600 pixels
#define SCREEN_DEPTH_DEFAULT 16       // we want 16 bits per pixel
#define DEFAULTTHEME "default"
#define ANIMATIONCOUNT 1
#define BLOCKHEIGHT 12

// paths
#define DATAPATH_DEFAULT "data/"
#define LEVELPATH "levels/"
#define THEMEPATH "themes/"

// program settings
// comment this out to get rid of a lot of output
#define _STATUSOUTPUT
#define _DEBUG

// directions
#define DOWN 0
#define RIGHT 1
#define UP 2
#define LEFT 3
#define NEUTRAL 4

// activities
#define BLOCKMOVE  0
#define PLAYERMOVE 1

// blocks
/* block description:

0 - floor           13 - green key
1 - wall            14 - blue key
2 - fake air        15 - yellow key
3 - fake wall       16 - red door
4 - left arrow      17 - green door
5 - up arrow        18 - blue door
6 - right arrow     19 - yellow door
7 - down arrow      20 - wall-air-togglebutton
8 - hole            21 - toggleable block 1
9 - moveable block  22 - toggleable block 2
10 - broken floor   23 - water
11 - finish         24 - fire
12 - red key
*/
#define BLOCKCOUNT    25
#define B_AIR          0
#define B_WALL         1
#define B_FAKEAIR      2
#define B_FAKEWALL     3
#define B_LEFTARROW    4
#define B_UPARROW      5
#define B_RIGHTARROW   6
#define B_DOWNARROW    7
#define B_HOLE         8
#define B_BLOCK        9
#define B_BROKENFLOOR 10
#define B_FINISH      11
#define B_REDKEY      12
#define B_GREENKEY    13
#define B_BLUEKEY     14
#define B_YELLOWKEY   15
#define B_REDDOOR     16
#define B_GREENDOOR   17
#define B_BLUEDOOR    18
#define B_YELLOWDOOR  19
#define B_BUTTON      20
#define B_TOGGLE1     21
#define B_TOGGLE2     22
#define B_WATER       23
#define B_FIRE        24

// block bits
#define ISELSE             0  // a block that does nothing... like a wall
#define ISWALKABLE         1  // like floor, you can walk on it
#define ISMOVABLE          2  // you can move it, like a block
#define ISFETCHABLE        4  // you can take it
#define ISBLOCKCONTAINER   8  // you can move a block onto it
#define ISBLOCKDESTROYER  16  // block with this bit + block = air
#define ISDOOR            32  // block can be removed with a key
