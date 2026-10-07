#include "config.h"

#include <avr/io.h>
#include <avr/cpufunc.h>
#include <util/delay.h>
#include <stdlib.h>

#include "ws.h"
#include "ws_usart.h"
#include "ws_effect.h"


void CLOCK_init(void) {
    // Select internal high frequency osc
    ccp_write_io((void*)(&CLKCTRL.MCLKCTRLA), CLKCTRL_CLKSEL_OSCHF_gc);
    
    // Set the frequency to 24MHz
    ccp_write_io((void*)&CLKCTRL.OSCHFCTRLA, CLKCTRL_FRQSEL_24M_gc);
    
    // Do not use the prescaler
    ccp_write_io((void*)(&CLKCTRL.MCLKCTRLB), 0);
}   

void propagate(void) {
    for (uint8_t i = WS_LED_COUNT - 1; i > 0; i--) {
        ws_pixels[i][0] = ws_pixels[i - 1][0];
        ws_pixels[i][1] = ws_pixels[i - 1][1];
        ws_pixels[i][2] = ws_pixels[i - 1][2];
    }
}

void state_0(uint8_t c) {
    propagate();
    ws_set_pixel(0, c, 0x00, 0x00);
}

void state_1(uint8_t c) {
    propagate();
    ws_set_pixel(0, 0x00, c, 0x00);
}


void state_2(uint8_t c) {
    propagate();
    ws_set_pixel(0, 0x00, 0x00, c);
}

void state_3(uint8_t c) {
    propagate();
    ws_set_pixel(0, c, c, c);    
}

void state_4(uint8_t c) {
    ws_effect_dim(1);
}

void state_5(uint8_t c) {
    ws_effect_dim(1);
    
    uint8_t x = rand() % 4;
    if (x == 0) {
        ws_set_pixel(rand() % WS_LED_COUNT, c, 0, 0);
    } else if (x == 1) {
        ws_set_pixel(rand() % WS_LED_COUNT, 0, c, 0);
    } else if (x == 2) {
        ws_set_pixel(rand() % WS_LED_COUNT, 0, 0, c);
    } else  {
        ws_set_pixel(rand() % WS_LED_COUNT, c, c, c);
    }

    ws_effect_mix(2, 1, WS_EFFECT_MIX_LOOP);
    
}


int main(void) {
    CLOCK_init();
    ws_usart_init();
    
    uint8_t c = 0;
    uint8_t state = 0;
    
    while (1) {   
        if (state == 0) {
            state_0(c);
        } else if (state == 1) {
            state_1(c);
        }else if (state == 2) {
            state_2(c);
        }else if (state == 3) {
            state_3(c);
        }else if (state == 4) {
            state_4(c);
        }else {
            state_5(255);
        }
        
        if (c == 255) {
            if (state == 6) {
                state = 0;
            } else {
                state++;
            }
        }
        
        c++;
        
        ws_usart_send_pixels();
        _delay_ms(41);
    }
    
}
