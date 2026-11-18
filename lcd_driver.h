#pragma once

#include <stdint.h>

#define LCD_X_SIZE      1024
#define LCD_Y_SIZE      600

#define LCD_PX_COUNT    (LCD_X_SIZE * LCD_Y_SIZE)

struct point {
    uint16_t x;
    uint16_t y;
};

struct rgb {
    uint8_t r;
    uint8_t g;
    uint8_t b;
};

struct frame_buffer {
    struct rgb px[LCD_PX_COUNT];
};

typedef bool bit_set;

bit_set bit_nset = false;
bit_set set = true;

bit_set draw_pixel(struct point p_xy, struct rgb p_rgb, struct frame_buffer *fb);
bool draw_square(struct point start_point, struct point end_point, struct rgb line_color);
bool draw_circle(struct point center, struct rgb line_color);
uint32_t get_pixel(struct point p_xy, struct frame_buffer *fb);
bool write_text(int text, struct frame_buffer *fb);





