//
// Created by Will Gulian on 2019-02-14.
//

#include <Shift595.h>
#include "cpp_main.h"

bus_pin led1{GPIOB, GPIO_PIN_0};
bus_pin led2{GPIOB, GPIO_PIN_1};

// active low
bus_pin pin_addr_dsbl{GPIOB, GPIO_PIN_10};
bus_pin pin_out_dsbl{GPIOB, GPIO_PIN_11};
bus_pin pin_cc_dsbl{GPIOB, GPIO_PIN_8};

Shift595 shift_addr{
        {GPIOA, GPIO_PIN_2}, // srclk
        {GPIOA, GPIO_PIN_3}, // rclk
        {GPIOA, GPIO_PIN_1}, // ser
        {GPIOA, GPIO_PIN_4}, // oe
};

void cpp_main() {
    shift_addr.init();
    shift_addr.set_enabled(true);

    bus_write_pin(&pin_addr_dsbl, false);
    bus_write_pin(&pin_out_dsbl, false);
    bus_write_pin(&pin_cc_dsbl, false);

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wmissing-noreturn"
    while (true) {

        uint8_t nums[] = {0xFF, 0};

        for (int i = 0; i < 2; i++) {

            bus_write_pin(&led1, i != 0);
            bus_write_pin(&led2, i == 0);

            shift_addr.load_byte(nums[i]);
            HAL_Delay(200);
        }

    }
#pragma clang diagnostic pop
}


