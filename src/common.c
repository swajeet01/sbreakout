#include <stdio.h>
#include <sysexits.h>

#include "common.h"

void must_init(bool test, const char* what) {
    if (test) return;
    fprintf(stderr, "Err: can't initialize %s\n", what);
    exit (EX_SOFTWARE);
}

bool collide(int ax1, int ay1, int ax2, int ay2,
        int bx1, int by1, int bx2, int by2) {
    if (ax1 > bx2 || ax2 < bx1 || ay1 > by2 || ay2 < by1)
        return false;
    return true;
}
