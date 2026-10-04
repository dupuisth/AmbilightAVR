#include "ws.h"

#include <assert.h>

uint8_t ws_pixels[WS_LED_COUNT][3];

void ws_set_pixel(uint8_t pixel, uint8_t r, uint8_t g, uint8_t b) {
    assert(pixel > 0 && pixel < WS_LED_COUNT);
    
    ws_pixels[pixel][0] = r;
    ws_pixels[pixel][1] = g;
    ws_pixels[pixel][2] = b;
}

void ws_clear(void) {
    ws_fill(0, 0, 0);
}

void ws_fill(uint8_t r, uint8_t g, uint8_t b) {
    for (uint8_t i = 0; i < WS_LED_COUNT; i++) {
        ws_pixels[i][0] = r;
        ws_pixels[i][1] = g;
        ws_pixels[i][2] = b;
    }
}