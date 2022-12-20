#ifndef BRICKS_INCL
#define BRICKS_INCL

#include "display.h"

#define BRICK_W (BUFFER_W * DISP_SCALE)
#define BRICK_H (BUFFER_H * DISP_SCALE)

#define BRICK_R 4
#define BRICK_C (BUFFER_W / BRICK_W)

#define BRICK_START_X 50
#define BRICK_START_Y 0

typedef struct {
    int x;
    int y;
    bool destroyed;
    struct {
        float r;
        float g;
        float b;
    } color;
} Bricks;

void init_bricks(Bricks bricks[BRICK_R][BRICK_C]);
void draw_bricks(Bricks bricks[BRICK_R][BRICK_C]);

#endif
