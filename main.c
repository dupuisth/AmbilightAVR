#include "config.h"

#include <avr/io.h>
#include <avr/cpufunc.h>
#include <util/delay.h>

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
    ws_fill(255, 0, 0);
    
    while (1) {
        ws_usart_send_pixels();
        _delay_ms(55);
    }
}
