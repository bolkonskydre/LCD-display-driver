#include "gui.h"

window gui_create_window(struct screen *scr, struct frame_buffer *fb, struct point sp, struct point ep) {
    window win = {
        .sp = sp,
        .ep = ep,
        .fb = fb,
        .scr = scr,
        .x_size = ep.x - sp.x,
        .y_size = ep.y - sp.y,
    };
    return win;
};

