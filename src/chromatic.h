#ifndef CHROMATIC_H
#define CHROMATIC_H

#include <stdint.h>
#include <stddef.h>
typedef struct Color {
    uint8_t r, g, b;
} color_t;

extern const color_t COLOR_BLACK;
extern const color_t COLOR_WHITE;
extern const color_t COLOR_RED;
extern const color_t COLOR_GREEN;
extern const color_t COLOR_BLUE;

typedef struct Texture {
    size_t width, height;
    color_t *pixels;
} texture_t;

texture_t *texture_create(size_t w, size_t h);
void texture_destroy(texture_t *tex);
void texture_clear(texture_t *tex);

color_t texture_get_pixel(texture_t *tex, int x, int y);
void texture_set_pixel(texture_t *tex, int x, int y, color_t color);

void texture_draw_line(texture_t *tex, int x0, int y0, int x1, int y1, color_t color);

void texture_draw_hline(texture_t *tex, int x, int y, int w, color_t color);
void texture_draw_vline(texture_t *tex, int x, int y, int h, color_t color);

void texture_fill_rect(texture_t *tex, int x, int y, int w, int h, color_t color);

#endif
