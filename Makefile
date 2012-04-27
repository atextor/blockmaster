GCC=gcc
CCFLAGS=-Wall -pedantic -std=c99 -I/usr/include/SDL
LDFLAGS=-lSDL
PROG=blockmaster
MODS=main.o handleblock.o render.o level.o sfont.o tools.o gfx.o config.o activity.o

all: $(PROG)

%.o: %.c
	$(GCC) -c $(CCFLAGS) -o $@ $<

$(PROG): $(MODS)
	$(GCC) -o $@ $(MODS) $(LDFLAGS)

clean:
	-rm -f $(PROG) $(MODS)

