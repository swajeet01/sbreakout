
#include "display.h";
#include "bricks.h";
#include "pad.h";
#include "ball.h";

typedef struct {
    long frames;
    long score;
    Brick bricks[BRICK_R][BRICK_C];
    Pad pad;
    Ball ball;
} Game;


