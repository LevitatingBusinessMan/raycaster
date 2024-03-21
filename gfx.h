#include <stdbool.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>

#define SCREEN_HEIGHT 480
#define SCREEN_WIDTH 640

extern SDL_Window* window;
extern SDL_GLContext gl_context;

bool init_win();
void line(int x, int h, int color, bool darkened);
void set_color(int color, bool darkened);
void cls();
void draw();
void cleanup();

