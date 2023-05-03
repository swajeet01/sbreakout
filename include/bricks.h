#ifndef BRICKS_INCL
#define BRICKS_INCL

#include "display.h"

#define BRICK_W (BUFFER_W / 10)
#define BRICK_H 10

#define BRICK_R 4
#define BRICK_C (BUFFER_W / BRICK_W)

#define BRICK_START_X 0
#define BRICK_START_Y 50

typedef struct { float r; float g; float b; } brick_color;

extern brick_color brick_colors[];

typedef struct {
    int x;
    int y;
    bool destroyed;
    struct {
        float r;
        float g;
        float b;
    } color;
    int hits_remaining;
} Brick;

void init_bricks(Brick bricks[BRICK_R][BRICK_C]);
void draw_bricks(Brick bricks[BRICK_R][BRICK_C]);

#endif
