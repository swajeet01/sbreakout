#include <allegro5/allegro5.h>
#include <allegro5/allegro_primitives.h>

#include "ball.h"
#include "pad.h"
#include "display.h"

void init_ball(Ball* ball) {
    ball->dx = 4;
    ball->dy = 4;
    ball->x = BUFFER_W / 2;
    ball->y = BUFFER_H - PAD_H - BALL_R;
}

void draw_ball(int ball_x, int ball_y) {
    al_draw_filled_circle(ball_x, ball_y, BALL_R, al_map_rgb_f(1, 1, 0));
}
