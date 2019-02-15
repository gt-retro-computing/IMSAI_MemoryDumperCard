//
// Created by Will Gulian on 2019-02-14.
//

#include "bus_io.h"
#include "Shift595.h"
#include "cmsis_os.h"
#include "cpp_main.h"

bus_pin led1{GPIOB, GPIO_PIN_0};
bus_pin led2{GPIOB, GPIO_PIN_1};

// active low

void cpp_main() {
    S100::init();

    osDelay(500);

    S100::acquire();

    uint8_t data[] = {0x3E, 0x00, 0x06, 0x01, 0x2E, 0xFF, 0x4F, 0x80, 0xDA, 0x00, 0x00, 0xAD, 0xD3, 0xFF, 0xAD, 0x41, 0x67, 0x11, 0xFF, 0xFF, 0x1B, 0x7A, 0xB3, 0xC2, 0x14, 0x00, 0x7C, 0xC3, 0x06, 0x00};


    S100::write_mem(0, data, 0, sizeof(data) / sizeof(uint8_t));
    S100::release();

    osDelay(100);

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wmissing-noreturn"
    while (true) {

        for (int i = 0; i < 2; i++) {

            bus_write_pin(&led1, i != 0);
            bus_write_pin(&led2, i == 0);

            osDelay(200);
        }

    }
#pragma clang diagnostic pop
}


