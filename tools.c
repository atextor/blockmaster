#include "main.h"

// this will shutdown sdl and quit the program
void quit(int ret_val)
{
    printf ("Quitting...\n");
    SDL_Quit();
    exit(ret_val);
}
