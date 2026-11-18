#include "lcd_driver.h"
#include "string.h"

struct frame_buffer lcd_fb;

/*--------------------------------*/
//Firmware abstraction for LCD display

/*Draw pixel base function
* @param p_xy Struct containing the coordinates for the pixel being set
* @param rgb  Struct containing the color to be set on the frame buffer matrix
* @param *fb  Pointer to frame_buffer object containing the data for all the pixels on the display
*
* Returns a bit_nset value when the xy coordinates go outside range
*/
bit_set draw_pixel(struct point p_xy, struct rgb p_rgb, struct frame_buffer *fb) {
    uint16_t original_x;
    uint16_t original_y;
    uint32_t p_addr;    
    uint32_t size_in_bytes =  LCD_PX_COUNT >> 3;
    
    if (p_xy.x > LCD_X_SIZE | p_xy.y > LCD_Y_SIZE) {
        return bit_nset;
    };

    original_x = p_xy.x;
    original_y = p_xy.y;

    p_addr = p_xy.x * p_xy.y;

    fb->px[p_addr].r = p_rgb.r;
    fb->px[p_addr].g = p_rgb.g;
    fb->px[p_addr].b = p_rgb.b;

    return set;
}

/*
* 
*
*
*
*
*/
bit_set draw_square(struct point start_point, struct point end_point, struct rgb line_color) {

}
bool draw_circle(struct point center, struct rgb line_color);
uint32_t get_pixel(struct point p_xy, struct frame_buffer *fb);
bool write_text(int text, struct frame_buffer *fb);
