#include "gfx.h"
#include "SDL_video.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>

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
		"Raycaster go brrr",
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		SCREEN_WIDTH,
		SCREEN_HEIGHT,
		SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN
	);

	if (window == NULL) {
		printf("Failed to create window, error: %s", SDL_GetError());
		return false;
	}
	context = SDL_GL_CreateContext(window);
	//glViewport(0, 0, SCREEN_WIDTH, SCREEN_WIDTH);

	cls();

	return true;
}

void line(int x, int h, int color, bool darkened) {
	// normalize x
	GLfloat x_normal = 2 * x / (GLfloat) SCREEN_WIDTH - 1;

	// normalize h
	GLfloat h_normal = 2 * h / (GLfloat) SCREEN_HEIGHT;
	GLfloat line_offset = (2 - h_normal) / 2.0;

	set_color(color, darkened);

	glBegin(GL_LINES);
	glVertex2f(x_normal, line_offset - 1);
	glVertex2f(x_normal, 1 - line_offset);
	glEnd();
}

void cls() {
	glClear(GL_COLOR_BUFFER_BIT);
}

void set_color(int color, bool darkened) {
	float value = darkened ? 0.5 : 1.0;
	switch (color) {
		case 1:
			glColor3f(value, 0.0, 0.0);
			break;
		case 2:
			glColor3f(0.0, value, 0.0);
			break;
		case 3:
			glColor3f(0.0, 0.0, value);
			break;
	}
}

void draw() {
	SDL_GL_SwapWindow(window);
}

void cleanup() {
	SDL_DestroyWindow(window);
	SDL_Quit();
}
