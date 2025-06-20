#include "chromatic.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const color_t COLOR_BLACK = {0, 0, 0};
const color_t COLOR_WHITE = {255, 255, 255};
const color_t COLOR_RED = {255, 0, 0};
const color_t COLOR_GREEN = {0, 255, 0};
const color_t COLOR_BLUE = {0, 0, 255};

texture_t *texture_create(size_t w, size_t h) {
    texture_t *tex = malloc(sizeof(texture_t));
    if (!tex)
        return NULL;

    tex->pixels = calloc(w * h, sizeof(color_t));
    if (!tex->pixels) {
        free(tex);
        return NULL;
    }

    tex->width = w;
    tex->height = h;
    return tex;
}

void texture_destroy(texture_t *tex) {
    if (tex) {
        free(tex->pixels);
        free(tex);
    }
}

void texture_clear(texture_t *tex) {
    if (tex && tex->pixels)
        memset(tex->pixels, 0, tex->width * tex->height * sizeof(color_t));
}

color_t texture_get_pixel(texture_t *tex, int x, int y) {
    if (x < 0 || x >= tex->width || y < 0 || y >= tex->height)
        return COLOR_BLACK;
    return tex->pixels[x + y * tex->width];
}

void texture_set_pixel(texture_t *tex, int x, int y, color_t color) {
    if (x < 0 || x >= tex->width || y < 0 || y >= tex->height)
        return;
    tex->pixels[x + y * tex->width] = color;
}

void texture_draw_line(texture_t *tex, int x0, int y0, int x1, int y1, color_t color) {
    int dx = abs(x1 - x0);
    int dy = abs(y1 - y0);

    int sx = (x0 < x1) ? 1 : -1;
    int sy = (y0 < y1) ? 1 : -1;

    int err = dx - dy;

    while (1) {
        texture_set_pixel(tex, x0, y0, color);
        if (x0 == x1 && y0 == y1)
            break;
        int e2 = 2 * err;
        if (e2 > -dy) {
            err -= dy;
            x0 += sx;
        }
        if (e2 < dx) {
            err += dx;
            y0 += sy;
        }
    }
}

void texture_draw_hline(texture_t *tex, int x, int y, int w, color_t color) {
    if (y < 0 || y > tex->height)
        return;

    int x0 = x < 0 ? 0 : x;
    int w0 = x + w > tex->width ? tex->width : x + w;

    for (int i = 0; i < w0; i++) {
        texture_set_pixel(tex, x0 + i, y, color);
    }
}

void texture_draw_vline(texture_t *tex, int x, int y, int h, color_t color) {
    if (x < 0 || x > tex->width)
        return;

    int y0 = y < 0 ? 0 : y;
    int h0 = y + h > tex->height ? tex->height : y + h;

    for (int i = 0; i < h0; i++) {
        texture_set_pixel(tex, x, y0 + i, color);
    }
}

void texture_fill_rect(texture_t *tex, int x, int y, int w, int h, color_t color) {
    int y0 = y < 0 ? 0 : y;
    int x0 = x < 0 ? 0 : x;
    int y1 = y + h > tex->height ? tex->height : y + h;
    int x1 = x + w > tex->width ? tex->width : x + w;

    for (int row = y0; row < y1; row++) {
        color_t *p = tex->pixels + row * tex->width + x0;
        color_t *end = p + (x1 - x0);
        while (p < end) {
            *p++ = color;
        }
    }
}
