#include <allegro5/allegro5.h>
#include <allegro5/allegro_primitives.h>

#include "display.h"
#include "pad.h"

void draw_pad(int pad_x) {
    al_draw_filled_rectangle(pad_x, BUFFER_H - PAD_H, pad_x + PAD_W, BUFFER_H,
            al_map_rgb_f(1, 1, 1)
    );
}
