#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>

#include "hud.h"
#include "common.h"
#include "display.h"

ALLEGRO_FONT* font;

void create_hud() {
    font = al_create_builtin_font();
    must_init(font, "font");
}

void draw_hud(long frames, long score) {
    al_draw_textf(font, al_map_rgb_f(1, 1, 1), 2, 0, 0, "Score: %ld", score);
    al_draw_textf(font, al_map_rgb_f(1, 1, 1), 2, 10, 0, "Frames: %ld", frames);
}

const char* start_message = "PRESS <SPACE> TO START";

void draw_start_message() {
    al_draw_text(font, al_map_rgb_f(1, 1, 1), BUFFER_W / 2, BUFFER_H / 2 - 5, ALLEGRO_ALIGN_CENTER, "SBreakout by SG768");
    al_draw_text(font, al_map_rgb_f(1, 1, 1), BUFFER_W / 2, BUFFER_H / 2 + 5, ALLEGRO_ALIGN_CENTER, start_message);
}

const char* pause_message = "PRESS <P> TO RESUME";

void draw_pause_message() {
    al_draw_text(font, al_map_rgb_f(1, 1, 1), BUFFER_W / 2, BUFFER_H / 2, ALLEGRO_ALIGN_CENTER, pause_message);
}

void destroy_hud() {
    al_destroy_font(font);
}

