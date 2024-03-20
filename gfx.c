#include "gfx.h"
#include "SDL_video.h"

//https://github.com/codetechandtutorials/sdl2_demo/blob/master/src/main.cpp

SDL_Window* window;
SDL_GLContext context;

bool init_win() {
	if (SDL_Init(SDL_INIT_VIDEO))
	{
		printf("Failed to init SDL Video, error: %s", SDL_GetError());
		return false;
	}

	window = SDL_CreateWindow(
		"Raycaster go brrr", 				// title
		SDL_WINDOWPOS_UNDEFINED,		  			// x
		SDL_WINDOWPOS_UNDEFINED,					// y
		SCREEN_WIDTH,							// width
		SCREEN_HEIGHT,							// height
		SDL_WINDOW_OPENGL					// flags
	);

	if (window == NULL) {
		printf("Failed to create window, error: %s", SDL_GetError());
		return false;
	}

	context = SDL_GL_CreateContext(window);

	glClearColor(1.0,0.0,0.0,0.0);
	glViewport(0, 0, SCREEN_WIDTH, SCREEN_WIDTH);

	SDL_GL_SwapWindow(window);

	return true;
}