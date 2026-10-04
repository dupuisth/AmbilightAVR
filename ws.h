#ifndef WS28XX_H
#define	WS28XX_H

#include <stdint.h>

#ifdef	__cplusplus
extern "C" {
#endif
    
#ifndef WS_LED_COUNT
#warning WS_LED_COUNT is not defined
#define WS_LED_COUNT 0
#endif

    extern uint8_t ws_pixels[WS_LED_COUNT][3];

    void ws_set_pixel(uint8_t pixel, uint8_t r, uint8_t g, uint8_t b);
    void ws_clear(void);
    void ws_fill(uint8_t r, uint8_t g, uint8_t b);
    
#ifdef	__cplusplus
}
#endif

#endif	/* WS28XX_H */

