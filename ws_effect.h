#ifndef WS_EFFECTS_H
#define	WS_EFFECTS_H

#include <avr/io.h>

#ifdef	__cplusplus
extern "C" {
#endif

    void ws_effect_dim(uint8_t intensity);
    
#define WS_EFFECT_MIX_LOOP 0x01
#define WS_EFFECT_MIX_NOLOOP 0x00
    void ws_effect_mix(uint8_t keep_ratio, uint8_t propagate_ratio, uint8_t flags);
    
#define WS_EFFECT_SHIFT_FORWARD 0x01
#define WS_EFFECT_SHIFT_BACKWARD 0x00
#define WS_EFFECT_SHIFT_LOOP 0x02
#define WS_EFFECT_SHIFT_NOLOOP 0x00
    void ws_effect_shift(uint8_t flags);
#ifdef	__cplusplus
}
#endif

#endif	/* WS_EFFECTS_H */

