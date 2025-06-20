#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "chromatiC.h"

#define SCREEN_HEIGHT 48
#define SCREEN_WIDTH  80

typedef struct Color {
	int r;
	int g;
	int b;
} color_t;

typedef struct Texture {
	color_t data[SCREEN_HEIGHT * SCREEN_WIDTH];
} texture_t;

void fragment(int x, int y, color_t* color);
texture_t random_noise(unsigned int seed);
color_t sample(int x, int y, texture_t texture);

texture_t random_noise_texture;

int main(void) {
	random_noise_texture = random_noise(time(NULL));

	color_t vram[SCREEN_HEIGHT * SCREEN_WIDTH];

	for (int y=0;y<SCREEN_HEIGHT/2;y++) {
		for (int x=0;x<SCREEN_WIDTH;x++) {
			color_t top_cell = vram[x+(y*2)*x];
			fragment(x, y*2, &top_cell);
			fg_color(top_cell.r, top_cell.g, top_cell.b);

			color_t bottom_cell = vram[x+(y*2+1)*x];
			fragment(x, y*2+1, &bottom_cell);
			bg_color(bottom_cell.r, bottom_cell.g, bottom_cell.b);

			printf("▀");
			reset();
		}
		printf("\n");
	}
}

void fragment(int x, int y, color_t* color) {
	color->r = x;
	color->g = y;
	color->b = sample(x, y, random_noise_texture).b;
}

color_t sample(int x, int y, texture_t texture) {
	return texture.data[x+y*x];
}

texture_t random_noise(unsigned int seed) {
	srand(seed);
	texture_t random_noise;
	for (int y=0;y<SCREEN_HEIGHT;y++) {
		for (int x=0;x<SCREEN_WIDTH;x++) {
			color_t pixel_color;

			pixel_color.r = rand() % 255;
			pixel_color.g = pixel_color.r;
			pixel_color.b = pixel_color.r;

			random_noise.data[x+y*x] = pixel_color;
		}
	}

	return random_noise;
}
