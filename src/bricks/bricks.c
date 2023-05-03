#include <stddef.h>
#include <stdio.h>

#include <allegro5/allegro5.h>
#include <allegro5/allegro_primitives.h>

#include "../../include/display.h"
#include "../../include/bricks.h"

brick_color brick_colors[] = {
    { .r = 1, .g = 1, .b = 1 },
    { .r = 0, .g = 0, .b = 1 },
    { .r = 0, .g = 1, .b = 0 },
    { .r = 1, .g = 0, .b = 0 },
};

void init_bricks(Brick bricks[BRICK_R][BRICK_C]) {

    for (size_t i = 0; i < BRICK_R; i++) {
        for (size_t j = 0; j < BRICK_C; j++) {
            bricks[i][j] = (Brick) {
                .x = BRICK_START_X + j * BRICK_W,
                .y = BRICK_START_Y + i * BRICK_H,
                .destroyed = false,
                .hits_remaining = BRICK_R - i
            };
            bricks[i][j].color.r = brick_colors[bricks[i][j].hits_remaining - 1].r;
            bricks[i][j].color.g = brick_colors[bricks[i][j].hits_remaining - 1].g;
            bricks[i][j].color.b = brick_colors[bricks[i][j].hits_remaining - 1].b;
        }
    }
}

void draw_bricks(Brick bricks[BRICK_R][BRICK_C]) {
    for (size_t i = 0; i < BRICK_R; i++) {
        for (size_t j = 0; j < BRICK_C; j++) {
            Brick brick = bricks[i][j];
            if (brick.destroyed) continue;
            al_draw_filled_rectangle(brick.x, brick.y, brick.x + BRICK_W,
                    brick.y + BRICK_H,
                    al_map_rgb_f(brick.color.r, brick.color.g, brick.color.b));
            al_draw_rectangle(brick.x, brick.y, brick.x + BRICK_W,
                    brick.y + BRICK_H,
                    al_map_rgb_f(0, 0, 0), 1);
        }
    }
}

