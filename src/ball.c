#include <allegro5/allegro5.h>
#include <allegro5/allegro_primitives.h>

#include "ball.h"

void draw_ball(int ball_x, int ball_y) {
    al_draw_filled_circle(ball_x, ball_y, BALL_R, al_map_rgb_f(0.5, 0.5, 1));
}
