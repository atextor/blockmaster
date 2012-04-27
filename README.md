Blockmaster
===========

This is the source code for the first game (and the first project
bigger than Hello World) I have written in C. I started on this
in 2001 and worked on and off until summer 2002. When I started,
I only knew BASIC and learned C and SDL in the course of
it. For this reason, don't be surprised if you encounter crude
parts in the code :-)

The game itself is inspired by Sokoban and Chip's Challenge,
and based on two similar games I had written earlier in QBasic
(for which I have lost the sources, unfortunately). The graphics
for the guys you control are cropped from screenshots of the
awesome Westwood RPG "Nox", and I used an SDL bitmap font
library by Karl Bartel, everything else was made by me.

The only parts I have changed in this release are a new Makefile
(the old one I had written back then didn't seem to work at an up
to date system), and I removed the loading of the (mandatory)
config file. If you want to use it, remove the comment for
ReadConfig() in main.c and  ln -s data/game.conf ~/.blockmasterrc.

To build it:

	make

Also, I removed some shell scripts I had set up for cross compiling
the game to run under windows using Mingw32 and SDL.dll
(I remember how that was a major PITA).

Controls
--------
The game has an isometric view and you control two guys with the
arrow keys; "North" is upper left. Spacebar to switch between the guys.
You can move around the arrow blocks, push them into the weirdly-shaped
holes. Blocks with green borders can be toggled on and off by the
green switches. Colored keys match the corresponding doors.
There is one working level, but nothing happens if you beat it.
