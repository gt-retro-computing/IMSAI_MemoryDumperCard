//
// Created by Will Gulian on 2019-02-14.
//

#include <Shift595.h>

#include "Shift595.h"

void Shift595::init() {
    bus_write_pin(&srclk, false);
    bus_write_pin(&ser, false);
    bus_write_pin(&rclk, true);
    // bus_write_pin(&srclr, true);
    bus_write_pin(&oe, true);
    initialized = true;

    // dump any random state in the shift registers.
    load_byte(0);
    load_byte(0);
    load_byte(0);
    load_byte(0);
}

void Shift595::load_byte(unsigned char data) {
    if (!initialized) {
        return;
    }

    bus_write_pin(&rclk, false);
#ifdef MEM_WRITE_DELAY
    osDelay(1);
#endif

    for (int i = 7; i >= 0; i--) {
        bus_write_pin(&ser, (data & (1 << i)) != 0);
        bus_write_pin(&srclk, true);
#ifdef MEM_WRITE_DELAY
        osDelay(1);
#endif
        bus_write_pin(&srclk, false);
    }

    bus_write_pin(&ser, false);
    bus_write_pin(&rclk, true);
#ifdef MEM_WRITE_DELAY
    osDelay(1);
#endif
    bus_write_pin(&rclk, false);
}

void Shift595::load_uint16(uint16_t data) {
    if (!initialized) {
        return;
    }

    bus_write_pin(&rclk, false);
#ifdef MEM_WRITE_DELAY
    osDelay(1);
#endif

    for (int i = 15; i >= 0; i--) {
        bus_write_pin(&ser, (data & (1 << i)) != 0);
        bus_write_pin(&srclk, true);
#ifdef MEM_WRITE_DELAY
        osDelay(1);
#endif
        bus_write_pin(&srclk, false);
#ifdef MEM_WRITE_DELAY
        osDelay(1);
#endif
    }

    bus_write_pin(&ser, false);
    bus_write_pin(&rclk, true);
#ifdef MEM_WRITE_DELAY
    osDelay(1);
#endif
    bus_write_pin(&rclk, false);
}

void Shift595::set_enabled(bool enabled) {
    if (!initialized) {
        return;
    }

    bus_write_pin(&oe, !enabled);
}



