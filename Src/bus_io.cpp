//
// Created by Will Gulian on 2019-02-14.
//

#include <stdbool.h>

#include "main.h"
#include "bus_io.h"
#include "Shift595.h"

//Shift595 shift_addr{
//        {GPIOA, GPIO_PIN_2}, // srclk
//        {GPIOA, GPIO_PIN_3}, // rclk
//        {GPIOA, GPIO_PIN_1}, // ser
//        {GPIOA, GPIO_PIN_4}, // oe
//};
//
//Shift595 data_out_addr{
//        {GPIOA, GPIO_PIN_2}, // srclk
//        {GPIOA, GPIO_PIN_3}, // rclk
//        {GPIOA, GPIO_PIN_1}, // ser
//        {GPIOA, GPIO_PIN_4}, // oe
//};


bool bus_has_control = false;

void bus_init() {
//    shift_addr.init();
//
//    shift_addr.set_enabled(true);
//
//
//    shift_addr.load_byte(0x7F);


}

void bus_acquire() {
    if (bus_has_control) {
        return;
    }


    // TODO
}

void bus_release() {
    // TODO
}


