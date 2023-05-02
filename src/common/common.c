#include <stdio.h>
#include <sysexits.h>

#include "../../include/common.h"


void must_init(bool test, const char* what) {
    if (test) return;
    fprintf(stderr, "Err: can't initialize %s\n", what);
    exit(EX_SOFTWARE);
}

int check_moving_collision(int ax1, int ay1, int ax2, int ay2,
        int bx1, int by1, int bx2, int by2, int bdx, int bdy) {
    if (
        ax1 < bx2 + bdx &&
        ax2 > bx1 + bdx &&
        ay1 < by2 &&
        ay2 > by1
    ) {
        return COLL_HORZ;
    }

    if (
        ax1 < bx2 &&
        ax2 > bx1 &&
        ay1 < by2 + bdy &&
        ay2 > by1 + bdy 
    ) {
        return COLL_VERT;
    }

    return COLL_NONE;

}


bool collide(int ax1, int ay1, int ax2, int ay2,
        int bx1, int by1, int bx2, int by2) {
    if (
        ax1 < bx2 &&
        ax2 > bx1 &&
        ay1 < by2 &&
        ay2 > by1
    ) {
        return true;
    }
    return false;
}
