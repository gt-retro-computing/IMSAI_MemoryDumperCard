//
// Created by Codetector on 2019/2/14.
//

#ifndef IMSAI8080STM32PROGRAMMER_SHIFT165_H
#define IMSAI8080STM32PROGRAMMER_SHIFT165_H

#include "stm32f1xx_hal.h"
#include "SharedStructs.h"

class Shift165 {
public:
    bus_pin ld_pin;
    bus_pin clk_pin;
    bus_pin data_pin;

    void init();

    uint8_t load_byte();

    uint16_t load_uint16();
};


#endif //IMSAI8080STM32PROGRAMMER_SHIFT165_H
