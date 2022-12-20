#ifndef COMMON_INCL
#define COMMON_INCL

#include <allegro5/allegro5.h>

void must_init(bool test, const char* what);

bool collide(int ax1, int ay1, int ax2, int ay2,
        int bx1, int by1, int bx2, int by2);

#endif
