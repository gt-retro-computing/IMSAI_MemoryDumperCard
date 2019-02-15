//
// Created by Will Gulian on 2019-02-14.
//

#ifndef IMSAI8080STM32PROGRAMMER_SHIFT595_H
#define IMSAI8080STM32PROGRAMMER_SHIFT595_H

#include "stm32f1xx_hal.h"
#include "SharedStructs.h"




static void bus_write_pin(bus_pin *pin, bool state) {
    HAL_GPIO_WritePin(pin->gpio, pin->pin, state ? GPIO_PIN_SET : GPIO_PIN_RESET);
}

struct Shift595 {
    bus_pin srclk; // SRCLK
    bus_pin rclk; // RCLK
    bus_pin ser; // SER
    bus_pin oe; // \OE
    // bus_pin srclr; // \SR_CLR

    bool initialized;

    Shift595(bus_pin srclk, bus_pin rclk, bus_pin ser, bus_pin oe) : srclk(srclk), rclk(rclk), ser(ser), oe(oe), initialized(false) {
    }

    void init();

    void load_byte(unsigned char data);

    void load_uint16(uint16_t data);

    void set_enabled(bool enabled);

};


#endif //IMSAI8080STM32PROGRAMMER_SHIFT595_H
