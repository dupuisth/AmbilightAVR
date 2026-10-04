// 24 MHz
#define F_CPU 24000000

#include <avr/io.h>
#include <avr/cpufunc.h>

void CLOCK_init(void) {
    // Select internal high frequency osc
    ccp_write_io((void*)(&CLKCTRL.MCLKCTRLA), CLKCTRL_CLKSEL_OSCHF_gc)
    
    // Set the frequency to 24MHz
    ccp_write_io((void*)&CLKCTRL.OSCHFCTRLA, CLKCTRL_FRQSEL_24M_gc);
    
    // Do not use the prescaler
    ccp_write_io((void*)(&CLKCTRL.MCLKCTRLB), 0);
}

int main(void) {
    CLOCK_init();
    
    while (1) {
    }
}
