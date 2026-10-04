#ifndef WS28XX_H
#define	WS28XX_H

#include "config.h"
#include <stdint.h>

#ifdef	__cplusplus
extern "C" {
#endif
   
#ifndef WS_LED_COUNT
#error WS_LED_COUNT is not defined 
#elif WS_LED_COUNT > 255
#error This is not designed to support more than 255, update for 16bit indexing if required
#endif
    
    extern uint8_t ws_pixels[WS_LED_COUNT][3];

    void ws_set_pixel(uint8_t pixel, uint8_t r, uint8_t g, uint8_t b);
    void ws_clear(void);
    void ws_fill(uint8_t r, uint8_t g, uint8_t b);
    
#ifdef	__cplusplus
}
#endif

#endif	/* WS28XX_H */

