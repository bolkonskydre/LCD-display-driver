#pragma once

#include <stdint.h>

#define LCD_X_SIZE      1024
#define LCD_Y_SIZE      600

#define LCD_PX_COUNT    (LCD_X_SIZE * LCD_Y_SIZE)


#define OUTER_SIZE(p1, p2)            ((p2 - p1) + 1)
#define INNER_SIZE(var, line)         (var - (line * 2))


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

typedef struct {
    struct point sp;
    struct point ep;
} rect;

struct font {
    uint8_t *font_array;
    uint8_t width;
    uint8_t height;
};

struct lcd_data {
    uint32_t x_size;
    uint32_t y_size;
};

bit_set bit_nset = false;
bit_set set = true;

bit_set draw_pixel(struct point p_xy, struct rgb p_rgb, struct frame_buffer *fb);
bit_set draw_rectangle(rect outer_rect, struct rgb line_color, struct rgb bg, uint16_t line_width, struct frame_buffer *fb, bool fill);
bool draw_circle(struct point center, struct rgb line_color);
uint32_t get_pixel(struct point p_xy, struct frame_buffer *fb);
bit_set draw_text(int text, struct frame_buffer *fb);
bit_set draw_char(char ascii_char, struct rgb text_color, struct point start, struct frame_buffer *fb);




