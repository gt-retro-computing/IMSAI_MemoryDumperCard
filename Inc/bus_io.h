//
// Created by Will Gulian on 2019-02-14.
//

#ifndef IMSAI8080STM32PROGRAMMER_BUS_IO_H
#define IMSAI8080STM32PROGRAMMER_BUS_IO_H

#include "Shift595.h"
#include <stdint.h>

namespace S100 {

    extern bool bus_has_control;

    void init();
    void acquire();
    void release();
    void write_mem(uint16_t start_addr, uint8_t buf[], uintptr_t offset, uintptr_t size);

};

#endif //IMSAI8080STM32PROGRAMMER_BUS_IO_H
