#include "ws_usart.h"

#include <util/delay.h>
#include <avr/io.h>


const uint8_t ws_lut[8] = {
    // Comments indicate the transmitted bits (ws bit)
    // (Data is sent using Lsb)
    0b1011011, // 0-0-0 (000)
    0b1011010, // 1-0-0 (001)
    0b1010011, // 0-1-0 (010)
    0b1010010, // 1-1-0 (011)
    0b0011011, // 0-0-1 (100)
    0b0011010, // 1-0-1 (101)
    0b0010011, // 0-1-1 (110)
    0b0010010, // 1-1-1 (111)
};

void ws_usart_init(void) {
    // Setup PD4
    PORTD.DIRSET = (1 << 4);
    PORTD.PIN4CTRL = PORT_INVEN_bm;
    PORTD.OUTCLR = (1 << 4);
    
    // Setup USART
    // With a 77 BAUD and CLK2X, f_baud = 2.5MHz (~400ns per bit)
    USART0.BAUD = 77; 
    USART0.CTRLC = USART_CHSIZE_7BIT_gc;
    USART0.CTRLB = USART_TXEN_bm | USART_RXMODE_CLK2X_gc;

    // Setup portmultiplexer to set TX on PD4.
    PORTMUX.USARTROUTEA = PORTMUX_USART0_ALT3_gc;
}

static inline void ws_usart_send_triplet(uint8_t bits) {
    while (!(USART0.STATUS & USART_DREIF_bm)) ;
    
    // TODO : Make the modification directly in the LUT table
    // This is a hot fix to make it works
    bits &= 0x07;
    bits = ((0x01 & bits) << 2) | ((0x04 & bits) >> 2) | (0x2 & bits);
    
    USART0.TXDATAL = ws_lut[bits & 0x7];
}

void ws_usart_send_pixel(uint8_t r, uint8_t g, uint8_t b)
{    
    ws_usart_send_triplet(g >> 5);
    ws_usart_send_triplet(g >> 2);
    ws_usart_send_triplet(((0x03 & g) << 1) | ((0x80 & r) >> 7));
    ws_usart_send_triplet(r >> 4);
    ws_usart_send_triplet(r >> 1);
    ws_usart_send_triplet(((0x01 & r) << 2) | ((0xC0 & b) >> 6));
    ws_usart_send_triplet(b >> 3);
    ws_usart_send_triplet(b);
}

void ws_usart_send_pixels(void) {
    for (uint8_t i = 0; i < WS_LED_COUNT; i++) {
        ws_usart_send_triplet(ws_pixels[i][0]);
        ws_usart_send_triplet(ws_pixels[i][1]);
        ws_usart_send_triplet(ws_pixels[i][2]);
    }
}