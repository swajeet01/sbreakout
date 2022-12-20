#include <sysexits.h>

#include <allegro5/allegro5.h>
#include <allegro5/allegro_primitives.h>

#include "display.h"
#include "common.h"
#include "hud.h"
#include "bricks.h"
#include "pad.h"
#include "ball.h"

typedef struct {
    long frames;
    long score;
    bool done;
    bool redraw;
    bool is_paused;
    bool is_started;
    Brick bricks[BRICK_R][BRICK_C];
    Pad pad;
    Ball ball;
} Game;

void reset_game(Game* game) {
    game->frames = 0;
    game->score = 0;
    init_bricks(game->bricks);
    game->done = false;
    game->redraw = true;
    game->is_paused = false;
    game->is_started = false;
    game->pad.x = (BUFFER_W / 2) - (PAD_W / 2);
    game->pad.y = BUFFER_H - PAD_H;
    game->ball.x = game->pad.y - (BALL_R / 2);
    game->ball.y = BUFFER_W / 2;
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
            game->is_paused = !game->is_paused;
            break;
    }
}

void handle_mouse(Game* game, ALLEGRO_EVENT* event) {
    game->pad.x = event->mouse.x;
}

void update_pad(Game* game) {
    if ((game->pad.x + PAD_W) > BUFFER_W)
        game->pad.x = BUFFER_W - PAD_W;
    if (game->pad.x < 0)
        game->pad.x = 0;
}

void update_ball(Game* game) {
    if (game->ball.x - BALL_R < 0 || game->ball.x + BALL_R > BUFFER_W)
        game->ball.dx = -game->ball.dx;
    if (game->ball.y - BALL_R < 0 || game->ball.y + BALL_R > BUFFER_H)
        game->ball.dy = -game->ball.dy;
    game->ball.x += game->ball.dx;
    game->ball.y += game->ball.dy;
}

int main() {
    must_init(al_init(), "allegro");
    must_init(al_install_keyboard(), "keyboard");
    must_init(al_install_mouse(), "mouse");

    ALLEGRO_TIMER* timer = al_create_timer(1.0 / 30.0);
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

    reset_game(&game);

    al_grab_mouse(disp);
    al_hide_mouse_cursor(disp);

    al_start_timer(timer);

    ALLEGRO_EVENT event;

    init_bricks(game.bricks);
    init_ball(&game.ball);

    while (1) {
        al_wait_for_event(queue, &event);

        switch (event.type) {
            case ALLEGRO_EVENT_TIMER:
                // game logic;
                game.frames++;
                update_pad(&game);
                update_ball(&game);
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
            draw_hud(game.frames, game.score);

            disp_post_draw();
            game.redraw = false;
        }
    }

    destroy_hud();
    destroy_display();
    al_destroy_timer(timer);
    al_destroy_event_queue(queue);

    return EX_OK;
}
