#ifndef DISPLAY_INCL
#define DISPLAY_INCL

#include <allegro5/allegro5.h>
#include <allegro5/allegro_image.h>

#define BUFFER_W 320
#define BUFFER_H 240

#define DISP_SCALE 2
#define DISP_W (BUFFER_W * DISP_SCALE)
#define DISP_H (BUFFER_H * DISP_SCALE)

extern ALLEGRO_DISPLAY* disp;
extern ALLEGRO_BITMAP* buffer;

void create_display();
void destroy_display();
void disp_pre_draw();
void disp_post_draw();

#endif
