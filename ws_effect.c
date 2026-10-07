#include "ws_effect.h"
#include "ws.h"
#include "config.h"


void ws_effect_dim(uint8_t intensity) {
    for (uint8_t i = 0; i < WS_LED_COUNT; i++) {
        for (uint8_t c = 0; c < 3; c++) {
            if (ws_pixels[i][c] < intensity) {
                ws_pixels[i][c] = 0;
            } else {
                ws_pixels[i][c] -= intensity;
            }
        }
    }
}

// Generated w/ AI
void ws_effect_mix(uint8_t keep_ratio,
                   uint8_t propagate_ratio,
                   uint8_t flags) {
    if (WS_LED_COUNT == 0) {
        return;
    }

    uint8_t first[3];
    uint8_t prev[3];
    uint8_t current[3];
    uint8_t next[3];

    /* Save first LED for loop-around. */
    for (uint8_t c = 0; c < 3; c++) {
        first[c] = ws_pixels[0][c];
        current[c] = ws_pixels[0][c];
    }

    /* Previous value for LED 0. */
    if (flags & WS_EFFECT_MIX_LOOP) {
        for (uint8_t c = 0; c < 3; c++) {
            prev[c] = ws_pixels[WS_LED_COUNT - 1][c];
        }
    } else {
        for (uint8_t c = 0; c < 3; c++) {
            prev[c] = 0;
        }
    }

    for (uint8_t i = 0; i < WS_LED_COUNT; i++) {

        /* Read next LED before modifying current LED. */
        if (i + 1 < WS_LED_COUNT) {
            for (uint8_t c = 0; c < 3; c++) {
                next[c] = ws_pixels[i + 1][c];
            }
        } else if (flags & WS_EFFECT_MIX_LOOP) {
            for (uint8_t c = 0; c < 3; c++) {
                next[c] = first[c];
            }
        } else {
            for (uint8_t c = 0; c < 3; c++) {
                next[c] = 0;
            }
        }

        for (uint8_t c = 0; c < 3; c++) {

            uint16_t divisor = keep_ratio;
            uint32_t value =
                (uint32_t)current[c] * keep_ratio;

            /*
             * Left neighbor.
             * In NOLOOP mode LED 0 only has a right neighbor.
             */
            if (i > 0 || (flags & WS_EFFECT_MIX_LOOP)) {
                value += (uint32_t)prev[c] * propagate_ratio;
                divisor += propagate_ratio;
            }

            /*
             * Right neighbor.
             * In NOLOOP mode the last LED only has a left neighbor.
             */
            if (i + 1 < WS_LED_COUNT ||
                (flags & WS_EFFECT_MIX_LOOP)) {
                value += (uint32_t)next[c] * propagate_ratio;
                divisor += propagate_ratio;
            }

            if (divisor != 0) {
                /* + divisor / 2 gives rounded division. */
                ws_pixels[i][c] =
                    (uint8_t)((value + divisor / 2) / divisor);
            } else {
                ws_pixels[i][c] = current[c];
            }
        }

        /*
         * Shift the original values.
         * current[] is still the original LED value, not the mixed one.
         */
        for (uint8_t c = 0; c < 3; c++) {
            prev[c] = current[c];
            current[c] = next[c];
        }
    }
}

void ws_effect_shift(uint8_t flags) {
    
}