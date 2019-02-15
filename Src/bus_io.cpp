//
// Created by Will Gulian on 2019-02-14.
//

#include <stdbool.h>

#include "main.h"
#include "bus_io.h"
#include "Shift595.h"

namespace S100 {

    Shift595 shift_addr{
            {GPIOA, GPIO_PIN_2}, // srclk
            {GPIOA, GPIO_PIN_3}, // rclk
            {GPIOA, GPIO_PIN_1}, // ser
            {GPIOA, GPIO_PIN_4}, // oe
    };

    Shift595 data_out_addr{
            {GPIOA, GPIO_PIN_6}, // srclk
            {GPIOA, GPIO_PIN_7}, // rclk
            {GPIOA, GPIO_PIN_5}, // ser
            {GPIOA, GPIO_PIN_8}, // oe
    };

    // active low
    bus_pin pin_addr_dsbl{GPIOB, GPIO_PIN_10};
    bus_pin pin_out_dsbl{GPIOB, GPIO_PIN_11};
    bus_pin pin_cc_dsbl{GPIOB, GPIO_PIN_8};
    bus_pin pin_p_write{GPIOB, GPIO_PIN_12};

    bool bus_has_control = false;

    void init() {

        shift_addr.init();
        shift_addr.set_enabled(false);

        data_out_addr.init();
        data_out_addr.set_enabled(false);

        bus_write_pin(&pin_addr_dsbl, true);
        bus_write_pin(&pin_out_dsbl, true);
        bus_write_pin(&pin_cc_dsbl, true);
        bus_write_pin(&pin_p_write, true);

    }

    void acquire() {
        if (bus_has_control) {
            return;
        }

        bus_write_pin(&pin_addr_dsbl, false);
        bus_write_pin(&pin_out_dsbl, false);
        bus_write_pin(&pin_cc_dsbl, false);

        shift_addr.set_enabled(true);
        data_out_addr.set_enabled(true);

        bus_has_control = true;
    }

    void release() {
        if (!bus_has_control) {
            return;
        }

        bus_has_control = false;

        shift_addr.set_enabled(false);
        data_out_addr.set_enabled(false);

        bus_write_pin(&pin_addr_dsbl, true);
        bus_write_pin(&pin_out_dsbl, true);
        bus_write_pin(&pin_cc_dsbl, true);
        bus_write_pin(&pin_p_write, true);
    }

    void write_mem(uint16_t start_addr, uint8_t buf[], uintptr_t offset, uintptr_t size) {
        if (!bus_has_control) {
            return;
        }

        for (uintptr_t i = 0; i < size; i++) {
            auto addr = (uint16_t) (start_addr + i);

            shift_addr.load_uint16(addr);
#ifdef MEM_WRITE_DELAY
            osDelay(1);
#endif

            data_out_addr.load_byte(buf[offset + i]);

#ifdef MEM_WRITE_DELAY
            osDelay(1);
#endif

            bus_write_pin(&pin_p_write, false);

#ifdef MEM_WRITE_DELAY
            osDelay(1);
#endif

            bus_write_pin(&pin_p_write, true);

#ifdef MEM_WRITE_DELAY
            osDelay(1);
#endif
        }
    }

};


