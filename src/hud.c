#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>

#include "hud.h"
#include "common.h"

ALLEGRO_FONT* font;

void create_hud() {
    font = al_create_builtin_font();
    must_init(font, "font");
}

void draw_hud(long frames, long score) {
    al_draw_textf(font, al_map_rgb_f(1, 1, 1), 2, 0, 0, "Score: %ld", score);
    al_draw_textf(font, al_map_rgb_f(1, 1, 1), 2, 0, 0, "Frame: %ld", frames);
}
