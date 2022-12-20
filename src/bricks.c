#include <stdio.h>

#include "display.h"
#include "bricks.h"

#include <allegro5/allegro5.h>
#include <allegro5/allegro_primitives.h>

void init_bricks(Brick bricks[BRICK_R][BRICK_C]) {

#if BRICK_DEBUG == 1
    printf("BRICK_R=%d\nBRICK_C=%d\n", BRICK_R, BRICK_C);
#endif

    struct { float f; float g; float b; } brick_colors[] = {
        { .r = 1, .g = 0, .b = 0 },
        { .r = 0, .g = 1, .b = 0 },
        { .r = 0, .g = 0, .b = 1 },
        { .r = 1, .g = 1, .b = 1 },
    }

    const size_t brick_color_size = 
        sizeof(brick_colors) / sizeof(color_profiles[0]);

#if BRICK_DEBUG == 1
    printf("profile_size=%zu\n", brick_color_size);
#endif

    for (size_t i = 0; i < BRICK_R; i++) {
        for (size_t j = 0; j < BRICK_C; j++) {
            bricks[i][j] = {
                .x = BRICK_START_X + j * BRICK_W,
                .y = BRICK_START_Y + i * BRICK_H,
                .destroyed = false,
                .color = {
                    .r = brick_colors[i % brick_color_size].r,
                    .g = brick_colors[i % brick_color_size].g,
                    .b = brick_colors[i % brick_color_size].b,
                }
            };
#if BRICK_DEBUG == 1
            printf("(.x = %d, .y = %d, .r = %f, .g = %f, .b = %f)\n",
                    bricks[i][j].x, bricks[i][j].y
                    bricks[i][j].color.r,
                    bricks[i][j].color.g,
                    bricks[i][j].color.b
            );
#endif
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

