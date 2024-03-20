C=gcc
CFLAGS=-Wall -Wextra $$(pkg-config --cflags --libs sdl2 gl) -g

raycaster: raycaster.c gfx.c gfx.h map.h
