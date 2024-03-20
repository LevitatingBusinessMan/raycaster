#include "gfx.h"
#include <SDL2/SDL.h>

//https://github.com/codetechandtutorials/sdl2_demo/blob/master/src/main.cpp

void screen() {
	SDL_Window* sdl_window = SDL_CreateWindow(
		"Raycaster go brrr", 				// title
		SDL_WINDOWPOS_UNDEFINED,		  	// x
		SDL_WINDOWPOS_UNDEFINED,			// y
		SCREEN_WIDTH,						// width
		SCREEN_HEIGHT,						// height
		SDL_WINDOW_OPENGL						// flags
	);
	SDL_Event sdl_event;
	while (SDL_PollEvent(&sdl_event) != 0)
	{
        if (sdl_event.type == SDL_QUIT)
        {
            break;
        }
    }
    SDL_Quit();
}