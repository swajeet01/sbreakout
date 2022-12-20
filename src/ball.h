#ifndef BALL_INCL
#define BALL_INCL

#define BALL_R 5

typedef struct {
    int x;
    int y;
    int dx;
    int dy;
} Ball;

void draw_ball(int ball_x, int ball_y);

#endif
