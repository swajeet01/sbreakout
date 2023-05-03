#ifndef BALL_INCL
#define BALL_INCL

#define BALL_R 5

typedef struct {
    float x;
    float y;
    float dx;
    float dy;
} Ball;

void init_ball(Ball* ball);

void draw_ball(float ball_x, float ball_y);

#endif
