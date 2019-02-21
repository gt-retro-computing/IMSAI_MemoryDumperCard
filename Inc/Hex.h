//
// Created by Will Gulian on 2019-02-19.
//

#ifndef IMSAI8080STM32PROGRAMMER_HEX_H
#define IMSAI8080STM32PROGRAMMER_HEX_H

#include <stdint.h>

struct Hex {
    uint16_t start_addr;
    uint16_t length;
    uint8_t buf[256];

    Hex() : start_addr(0), length(0), buf{} {}

    int read_string(uint8_t *data, size_t len);
};

#endif //IMSAI8080STM32PROGRAMMER_HEX_H
