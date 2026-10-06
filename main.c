#include "config.h"

#include <avr/io.h>
#include <avr/cpufunc.h>
#include <util/delay.h>
#include <stdlib.h>

#include "ws.h"
#include "ws_usart.h"


void CLOCK_init(void) {
    // Select internal high frequency osc
    ccp_write_io((void*)(&CLKCTRL.MCLKCTRLA), CLKCTRL_CLKSEL_OSCHF_gc);
    
    // Set the frequency to 24MHz
    ccp_write_io((void*)&CLKCTRL.OSCHFCTRLA, CLKCTRL_FRQSEL_24M_gc);
    
    // Do not use the prescaler
    ccp_write_io((void*)(&CLKCTRL.MCLKCTRLB), 0);
}

int main(void) {
    CLOCK_init();
    ws_usart_init();
    
    uint8_t c = 0;
    uint8_t state = 0;
    
    while (1) {
 
        c++;
        if (c == 255) {
            state += 1;
            c = 0;
        }
        if (state == 5) {
            state = 0;
        }
        
        for (uint8_t i = WS_LED_COUNT-1; i != 0; i--) {
            ws_pixels[i][0] = ws_pixels[i - 1][0];
            ws_pixels[i][1] = ws_pixels[i - 1][1];
            ws_pixels[i][2] = ws_pixels[i - 1][2];
        }
        
        if (state == 0) {
            ws_pixels[0][0] = c;
            ws_pixels[0][1] = 0;
            ws_pixels[0][2] = 0;
        } else if (state == 1) {
            ws_pixels[0][0] = 0;
            ws_pixels[0][1] = c;
            ws_pixels[0][2] = 0;
        }else if (state == 2) {
            ws_pixels[0][0] = 0;
            ws_pixels[0][1] = 0;
            ws_pixels[0][2] = c;
        }else if (state == 3) {
            ws_pixels[0][0] = c;
            ws_pixels[0][1] = c;
            ws_pixels[0][2] = c;
        }else if (state == 4) {
            ws_pixels[0][0] = rand() % 255;
            ws_pixels[0][1] = rand() % 255;
            ws_pixels[0][2] = rand() % 255;
        }
        
        ws_usart_send_pixels();
        _delay_ms(41);
    }
}
