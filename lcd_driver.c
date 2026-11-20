#include "lcd_driver.h"
#include "string.h"
#include "font_data.h"

/*TODO
* when kit arrives, i need to write some functions to store the buffer bytes in ram, then read them individually and update the display,
* would be too costly to store frames in mcu memory.
*/

struct frame_buffer lcd_fb;

struct font dylex_cfg = {
    .font_array = &DYLEX_TERMINAL,
    .height = 20,
    .width = 10,
};


/*--------------------------------*/
//Firmware abstraction for LCD display

/*Draw pixel base function
* @param p_xy Struct containing the coordinates for the pixel being set
* @param rgb  Struct containing the color to be set on the frame buffer matrix
* @param *fb  Pointer to frame_buffer object containing the data for all the pixels on the display
*
* Returns a bit_nset value when the xy coordinates go outside range
*/
bit_set draw_pixel(struct point p_xy, struct rgb p_rgb, struct frame_buffer *fb, struct lcd_data *lcd) {

    uint32_t p_addr;    
    
    if (p_xy.x >= lcd->x_size || p_xy.y >= lcd->y_size) {
        return bit_nset;
    };

    p_addr = (uint32_t)p_xy.y * lcd->x_size + p_xy.x;

    fb->px[p_addr].r = p_rgb.r;
    fb->px[p_addr].g = p_rgb.g;
    fb->px[p_addr].b = p_rgb.b;

    return set;
}


/*Draw square/rectangle(?) function
* @param start_point Top left outermost pixel of the rectangle
* @param end_point Bottom right outermost pixel of the rectangle
* @param rgb Color of the area of the rectangle
* @param line_width Thickness of the line
*
* 
*/
bit_set draw_rectangle(rect outer_rect, struct rgb line_color, struct rgb bg, uint16_t line_width, struct frame_buffer *fb, bool fill) {
    uint16_t sp_orig_x = outer_rect.sp.x;
    uint16_t sp_orig_y = outer_rect.sp.y;
    uint16_t ep_orig_x = outer_rect.ep.x;
    uint16_t ep_orig_y = outer_rect.ep.y;

    if (outer_rect.sp.x > outer_rect.ep.x || outer_rect.sp.y > outer_rect.ep.y) return bit_nset;
    if (outer_rect.ep.x >= LCD_X_SIZE) outer_rect.ep.x = LCD_X_SIZE - 1;
    if (outer_rect.ep.y >= LCD_Y_SIZE) outer_rect.ep.y = LCD_Y_SIZE - 1;

    for (uint32_t y = sp_orig_y; y < ep_orig_y; y++) {
        for (uint32_t x = sp_orig_x; x <= ep_orig_x; x++) {
            struct point px = {.x = x, .y = y};
            bool border = (x > outer_rect.sp.x + line_width) || (x < outer_rect.ep.x - line_width) ||
                          (y > outer_rect.sp.y + line_width) || (y < outer_rect.ep.y - line_width);

            if (!fill) fb->px[y * LCD_X_SIZE + x] = border? line_color : bg;
            if (fill) fb->px[y * LCD_X_SIZE + x] = line_color;
        };
    };
    return set;
};

bit_set draw_char(char ascii_char, struct font *font_cfg, struct rgb text_color, struct rgb bg, struct point start, struct frame_buffer *fb) {
    uint8_t target = ascii_char - ' ';
    uint32_t bwidth = ((font_cfg->width / 8) + 1) * 8;
    const uint8_t *drawchar = font_cfg->font_array[target];

    for (uint32_t y = 0; y < font_cfg->height; y++) {
        for (uint8_t byte = 0; byte < bwidth / 2; byte++) {
            uint8_t row = drawchar[byte];
            for (uint32_t x = 0; x < 8; x++) {
                bool fill = (row >> (8 - 1 - x)) & 1;
                struct point px = {start.x + x, start.y + y};
                if (fill) {
                    fb->px[(start.y + y) * LCD_X_SIZE + (start.x + x)] = text_color;
                }
                else fb->px[(start.y + y) * LCD_X_SIZE + (start.x + x)] = bg;
            }
        }
    }    
    return true;
};

bit_set write_text(char *text, uint32_t len, uint32_t line, uint32_t pos, struct font *font_cfg, struct rgb text_color, struct rgb bg, struct lcd_data *lcd, bool cr) {
    uint32_t start_y = line * font_cfg->height;
    uint32_t start_x = pos * font_cfg->width;

    uint32_t newlnx = cr ? 0 : start_x;

    uint32_t runningX;
    uint32_t runningY;
    for (uint32_t i = 0; i <= len; i++) {

    }
}


bool draw_circle(struct point center, struct rgb line_color);
uint32_t get_pixel(struct point p_xy, struct frame_buffer *fb);

