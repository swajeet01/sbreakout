#include <allegro5/mouse.h>

#include <allegro5/allegro5.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/mouse_cursor.h>

#include "../include/display.h"
#include "../include/common.h"
#include "../include/hud.h"
#include "../include/bricks.h"
#include "../include/pad.h"
#include "../include/ball.h"

typedef struct {
    long frames;
    long score;
    bool done;
    bool redraw;
    bool is_paused;
    bool is_started;
    bool ball_fallen;
    size_t brick_remaining;
    Brick bricks[BRICK_R][BRICK_C];
    Pad pad;
    Ball ball;
    float mouse_dx;
    int level;
} Game;

void reset_game(Game* game, int frames, int score, int level, float ball_dx, float ball_dy) {
    game->frames = frames;
    game->score = score;
    game->done = false;
    game->is_paused = false;
    game->is_started = false;
    game->ball_fallen = false;
    game->brick_remaining = BRICK_R * BRICK_C;
    init_bricks(game->bricks);
    game->pad.x = (BUFFER_W / 2) - (PAD_W / 2);
    game->pad.y = BUFFER_H - PAD_H;
    game->ball.x = BUFFER_W / 2.0;
    game->ball.y = game->pad.y - BALL_R;
    game->level = level;
}

void handle_keyboard(Game* game, ALLEGRO_EVENT* event) {
    switch (event->keyboard.keycode) {
        case ALLEGRO_KEY_ESCAPE:
            game->done = true;
            break;
        case ALLEGRO_KEY_SPACE:
            game->is_started = true;
            break;
        case ALLEGRO_KEY_P:
            if (game->is_started)
                game->is_paused = !game->is_paused;
            break;
    }
    if (game->is_started && !game->is_paused) {
        al_ungrab_mouse();
        al_show_mouse_cursor(disp);
    }
}

void handle_mouse(Game* game, ALLEGRO_EVENT* event) {
    if (game->is_started && !game->is_paused) {
        game->mouse_dx = event->mouse.dx;
        al_set_mouse_xy(disp, DISP_W / 2, DISP_H / 2);
    }
}


void ball_pad_collision(Game* game) {
    int collision = check_moving_collision(game->pad.x, game->pad.y, game->pad.x + PAD_W, game->pad.y + PAD_H,
            game->ball.x - BALL_R, game->ball.y, game->ball.x + BALL_R,
            game->ball.y + BALL_R, game->ball.dx, game->ball.dy);
    switch (collision) {
        case COLL_HORZ:
            game->ball.dx = -game->ball.dx;
            break;
        case COLL_VERT:
            game->ball.dy = -game->ball.dy;
            break;
    }
}

#define BRICK_AT(i, j) (game->bricks[i][j])

void ball_brick_collision(Game* game) {
    for (size_t i = 0; i < BRICK_R; i++) {
        for (size_t j = 0; j < BRICK_C; j++) {

            int collision = check_moving_collision(
                    BRICK_AT(i, j).x,
                    BRICK_AT(i, j).y,
                    BRICK_AT(i, j).x + BRICK_W,
                    BRICK_AT(i, j).y + BRICK_H,
                    game->ball.x - BALL_R, game->ball.y - BALL_R,
                    game->ball.x + BALL_R, game->ball.y + BALL_R,
                    game->ball.dx, game->ball.dy
            );

            if (!BRICK_AT(i, j).destroyed && collision) {

                switch (collision) {
                    case COLL_HORZ:
                        game->ball.dx = -game->ball.dx;
                        break;
                    case COLL_VERT:
                        game->ball.dy = -game->ball.dy;
                        break;
                }

                BRICK_AT(i, j).hits_remaining--;
                if (BRICK_AT(i, j).hits_remaining) {
                    BRICK_AT(i, j).color.r = brick_colors[BRICK_AT(i, j).hits_remaining - 1].r;
                    BRICK_AT(i, j).color.g = brick_colors[BRICK_AT(i, j).hits_remaining - 1].g;
                    BRICK_AT(i, j).color.b = brick_colors[BRICK_AT(i, j).hits_remaining - 1].b;
                    continue;
                }

                BRICK_AT(i, j).destroyed = true;
                game->brick_remaining--;
                game->score++;
            }
        }
    }
}

void update_ball(Game* game) {
    if (game->ball.x - BALL_R < 0 || game->ball.x + BALL_R > BUFFER_W)
        game->ball.dx = -game->ball.dx;
    if (game->ball.y - BALL_R < 0)
        game->ball.dy = -game->ball.dy;
    if (game->ball.y + BALL_R > BUFFER_H) {
        game->ball_fallen = true;
    }
    ball_pad_collision(game);
    ball_brick_collision(game);
    game->ball.x += game->ball.dx;
    game->ball.y += game->ball.dy;
}

void update_pad(Game* game) {
    if ((game->pad.x + PAD_W) > BUFFER_W) {
        game->pad.x = BUFFER_W - PAD_W;
    }
    if (game->pad.x < 0) {
        game->pad.x = 0;
    }
}

void update_bricks(Game* game) { }

int main() {
    must_init(al_init(), "allegro");
    must_init(al_install_keyboard(), "keyboard");
    must_init(al_install_mouse(), "mouse");

    ALLEGRO_TIMER* timer = al_create_timer(1.0 / 60.0);
    must_init(timer, "timer");

    ALLEGRO_EVENT_QUEUE* queue = al_create_event_queue();
    must_init(queue, "queue");

    create_hud();
    
    create_display();

    must_init(al_init_primitives_addon(), "primitives");

    al_register_event_source(queue, al_get_keyboard_event_source());
    al_register_event_source(queue, al_get_display_event_source(disp));
    al_register_event_source(queue, al_get_timer_event_source(timer));
    al_register_event_source(queue, al_get_mouse_event_source());

    Game game;

    reset_game(&game, 0, 0, 1, 0, 0);

    al_start_timer(timer);

    ALLEGRO_EVENT event;

    init_bricks(game.bricks);
    init_ball(&game.ball);

    while (1) {
        al_wait_for_event(queue, &event);

        switch (event.type) {
            case ALLEGRO_EVENT_TIMER:
                game.frames++;
                if (game.is_started && !game.is_paused) {
                    al_grab_mouse(disp);
                    al_hide_mouse_cursor(disp);
                    al_set_mouse_xy(disp, DISP_W / 2, DISP_H / 2);
                    update_pad(&game);
                    update_ball(&game);
                    if (game.ball_fallen) {
                        reset_game(&game, game.frames, 0, 1, 0, 0);
                    }
                    if (!game.brick_remaining) {
                        reset_game(&game, game.frames, game.score,
                                   game.level + 1, 0, 0);
                    }
                    game.pad.x += game.mouse_dx;
                    game.mouse_dx *= 0.05;
                }
                game.redraw = true;
                break;
            case ALLEGRO_EVENT_KEY_DOWN:
                handle_keyboard(&game, &event);
                break;
            case ALLEGRO_EVENT_MOUSE_AXES:
                handle_mouse(&game, &event);
                break;
            case ALLEGRO_EVENT_DISPLAY_CLOSE:
                game.done = true;
        }

        if (game.done) break;

        if (game.redraw && al_is_event_queue_empty(queue)) {
            disp_pre_draw();
            al_clear_to_color(al_map_rgb_f(0, 0, 0));
            draw_bricks(game.bricks);
            draw_pad(game.pad.x);
            draw_ball(game.ball.x, game.ball.y);
            draw_hud(game.frames, game.score, game.level);
            if (!game.is_started) draw_start_message();
            if (game.is_paused) draw_pause_message();
            disp_post_draw();
            game.redraw = false;
        }
    }

    destroy_hud();
    destroy_display();
    al_destroy_timer(timer);
    al_destroy_event_queue(queue);

    return 0;
}
