#include "SDL_events.h"
#include "map.h"
#include "gfx.h"
#include <stdbool.h>
#include <stdio.h>

static double pos_x = 16, pos_y = 29; // the current position of the player
static double dir_x = 0, dir_y = -1; // the direction the player is looking at
static double plane_x, plane_y; // the camera plane, perpendicular to the dir vector but shorter (basically the right side of it)

void main_loop();
void test();

int main(int argc, char** argv) {
	double time_prev;
	double time;

	init_win();

	main_loop();

	cleanup();

	return 0;
}

// calculates the plane vector
void calc_plane() {
	plane_x = -dir_y * 0.66;
	plane_y = dir_x * 0.66;
}

// work through the event queue
void handle_events(bool* quit) {
	SDL_Event e;
	while (SDL_PollEvent(&e) != 0) {
		if (e.type == SDL_QUIT) {
			*quit = true;
		}
		switch (e.type) {
			case SDL_QUIT:
				*quit = true;
				break;
			case SDL_KEYDOWN:
				switch (e.key.keysym.sym) {
					case SDLK_UP:
						pos_x += dir_x;
						pos_y += dir_y;
						break;
				}
				break;
		}
	}
}

void main_loop() {
	bool quit = false;

	while (!quit) {
		handle_events(&quit);

		for (int screen_x = 0; screen_x < (double) SCREEN_WIDTH; screen_x++) {
			calc_plane();

			// The camera plane x-coordinate, from -1 to 1 (y not needed it's a raycaster)
			double camera_x = 2 * screen_x / (double) SCREEN_WIDTH - 1; 

			// The ray vector emitted from player
			double ray_dir_x = dir_x + plane_x * camera_x,
			ray_dir_y = dir_y + plane_y * camera_x;

			// delta_dist_x is the distance from the first x-side to the next x-side on the grid
			// it can be calculated with `sqrt(1 + (ray_dir_y*ray_dir_y) / (ray_dir_x*ray_dir_x))`
			// delta_dist_y is the distance from the first y-side to the next y-side on the grid
			// it can be calculated with `sqrt(1 + (ray_dir_y*ray_dir_y) / (ray_dir_x*ray_dir_x))`
			// through math these calculations can be simplified
			double delta_dist_x = fabs(1 / ray_dir_x),
			delta_dist_y = fabs(1 / ray_dir_y);

			// the current box in the map grid
			int map_x = (int) pos_x,
			map_y = (int) pos_y;

			// length of ray to next x-side or next y-side
			double side_dist_x, side_dist_y;

			// the step direction that dda takes
			// (based off the ray dir)
			// either 1 or -1
			int dda_step_x, dda_step_y;

			if (ray_dir_x < 0) {
				dda_step_x = -1;
				side_dist_x = (pos_x - map_x) * delta_dist_x;
			} else {
				dda_step_x = 1;
				side_dist_x = (map_x - pos_x + 1.0) * delta_dist_x;
			}

			if (ray_dir_y < 0) {
				dda_step_y = -1;
				side_dist_y = (pos_y - map_y) * delta_dist_y;
			} else {
				dda_step_y = 1;
				side_dist_y = (map_y - pos_y + 1.0) * delta_dist_y;
			}

			// which side of the block was hit? true for x, false for y
			bool side_was_x;

			while (true) {
				// will the x-side or the y-side hit first?
				if (side_dist_x < side_dist_y) {
					side_dist_x += delta_dist_x;
					map_x += dda_step_x;
					side_was_x = true;
				} else {
					side_dist_y += delta_dist_y;
					map_y += dda_step_y;
					side_was_x = false;
				}
				// do we encounter a wall/object?
				if (world_map[map_y][map_x] > 0) break;
			}

			// printf("hit x%d y%d (%d) xplane: (%f), ray: (x%f y%f) delta: (x%f y%f)\n",
			// map_x, map_y, screen_x, camera_x, ray_dir_x, ray_dir_y, delta_dist_x, delta_dist_y);

			// the distance to the hit x-side or y-side
			// perpendicular from the camera plane (avoid fisheye)
			// how this is equal to side_dist (minus the last step) I am not sure
			double perp_dist = side_was_x ? side_dist_x - delta_dist_x : side_dist_y - delta_dist_y;

			// height of the line to draw
			int line_height = (int) (SCREEN_HEIGHT / perp_dist);
			line(screen_x, line_height, world_map[map_y][map_x], side_was_x);
		}
		draw();
		cls();
	}
}
