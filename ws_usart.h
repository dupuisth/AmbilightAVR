#ifndef WS_USART_H
#define	WS_USART_H

#include "ws.h"
#include <stdint.h>

#ifdef	__cplusplus
extern "C" {
#endif
    
    void ws_usart_init(void);
    void ws_usart_send_pixel(uint8_t r, uint8_t g, uint8_t b);
    void ws_usart_send_pixels(void);

#ifdef	__cplusplus
}
#endif

#endif	/* WS_USART_H */

