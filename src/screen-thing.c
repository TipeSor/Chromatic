#include "chromatic.h"
#include "sb.h"
#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>

#define SCREEN_HEIGHT 100
#define SCREEN_WIDTH 100

void cleanup(void);
void fragment(int x, int y, color_t *color);
void random_noise(texture_t *random_noise, unsigned int seed);

void print_texture(texture_t *tex);

texture_t *noise_texture;
texture_t *base_texture;

StringBuilder *sb;

int main(void) {
    printf("\033[2J");
    
    base_texture = texture_create(SCREEN_WIDTH, SCREEN_HEIGHT);
    
    texture_fill_rect(base_texture, 0, 0, 7, 7, COLOR_RED);
    texture_fill_rect(base_texture, 0, 0, 6, 6, COLOR_BLUE);
    texture_fill_rect(base_texture, 0, 0, 5, 5, COLOR_GREEN);
    texture_fill_rect(base_texture, 0, 0, 4, 4, COLOR_RED);
    texture_fill_rect(base_texture, 0, 0, 3, 3, COLOR_BLUE);
    texture_fill_rect(base_texture, 0, 0, 2, 2, COLOR_GREEN);
    texture_fill_rect(base_texture, 0, 0, 1, 1, COLOR_RED);

    texture_draw_line(base_texture, 99, 0, 0, 99, COLOR_WHITE);
    
    print_texture(base_texture);

    cleanup();
}

void cleanup(void) {
    if (base_texture)
        texture_destroy(base_texture);
    if (noise_texture)
        texture_destroy(noise_texture);
    sb_free(sb);
    printf("\033[0m");
    fflush(stdout);
}

void fragment(int x, int y, color_t *color) {
    color->r = (int)(255.0 * x / SCREEN_WIDTH);
    color->g = (int)(255.0 * y / SCREEN_HEIGHT);
    color->b = 0;
}

void random_rgb_noise(texture_t *random_noise, unsigned int seed) {
    srand(seed);
    for (int index = 0; index < random_noise->height * random_noise->width; index++) {
        random_noise->pixels[index] =
            (color_t){.r = rand() % 256, .g = rand() % 256, .b = rand() % 256};
    }
}

void random_noise(texture_t *random_noise, unsigned int seed) {
    srand(seed);
    for (int index = 0; index < random_noise->height * random_noise->width; index++) {
        int col = rand() % 256;
        random_noise->pixels[index] = (color_t){.r = col, .g = col, .b = col};
    }
}

void print_texture(texture_t *tex) {
    if (!sb) 
    {
        sb = sb_create();
    }
    else sb_clear(sb);
    sb_append(sb, "\033[H");
    for (int y = 0; y < tex->height / 2; y++) {
        for (int x = 0; x < tex->width; x++) {

            color_t top_cell = tex->pixels[x + (y * 2) * tex->width];
            sb_appendf(sb, "\033[38;2;%d;%d;%dm", top_cell.r, top_cell.g, top_cell.b);

            color_t btm_cell = tex->pixels[x + (y * 2 + 1) * tex->width];
            sb_appendf(sb, "\033[48;2;%d;%d;%dm", btm_cell.r, btm_cell.g, btm_cell.b);

            sb_append(sb, "▀");
        }
        sb_appendf(sb, "\033[0m\r\n");
    }
    printf("%s", sb->data);
    fflush(stdout);
    // write(STDOUT_FILENO, sb->data, sb->length);
    // tcdrain(STDOUT_FILENO);
}

/*
`\033[H`        | Move to top-left (home)
`\033[<r>;<c>H` | Move to row `r`, column `c`
`\033[A`        | Move up one line
`\033[B`        | Move down one line
`\033[C`        | Move right one column
`\033[D`        | Move left one column
`\033[2J`       | Clear screen
`\033[K`        | Clear to end of line
*/
