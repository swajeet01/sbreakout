#ifndef COMMON_INCL
#define COMMON_INCL

#include <allegro5/allegro5.h>

#define COLL_VERT   1
#define COLL_HORZ   2
#define COLL_NONE   0

void must_init(bool test, const char* what);

int check_moving_collision(int ax1, int ay1, int ax2, int ay2,
        int bx1, int by1, int bx2, int by2, int bdx, int bdy);

bool collide(int ax1, int ay1, int ax2, int ay2,
        int bx1, int by1, int bx2, int by2);

#endif
