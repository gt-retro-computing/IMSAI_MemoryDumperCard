//
// Created by Codetector on 2019/2/14.
//

#include <Shift165.h>
#include "Shift165.h"

void Shift165::init() {

}

uint8_t Shift165::load_byte() {
    uint8_t rtnByte = 0;
    // Latch data
    ld_pin.gpio->BRR = (ld_pin.pin);
    ld_pin.gpio->BSRR = (ld_pin.pin);

    // Shift data
    for (int i = 0; i < 8; ++i) {
        rtnByte = (uint8_t) ((rtnByte << 1) | ((data_pin.gpio->IDR & data_pin.pin) != 0));
        clk_pin.gpio->BSRR = clk_pin.pin;
        clk_pin.gpio->BRR = clk_pin.pin;
    }

    return rtnByte;
}


uint16_t Shift165::load_uint16() {
    uint16_t rtnByte = 0;
    // Latch data
    ld_pin.gpio->BRR = (ld_pin.pin);
    ld_pin.gpio->BSRR = (ld_pin.pin);

    // Shift data
    for (int i = 0; i < 16; ++i) {
        rtnByte = (uint8_t) ((rtnByte << 1) | ((data_pin.gpio->IDR & data_pin.pin) != 0));
        clk_pin.gpio->BSRR = clk_pin.pin;
        clk_pin.gpio->BRR = clk_pin.pin;
    }

    return rtnByte;
}