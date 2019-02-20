//
// Created by Will Gulian on 2019-02-19.
//

#ifndef IMSAI8080STM32PROGRAMMER_CPP_CALLBACKS_H
#define IMSAI8080STM32PROGRAMMER_CPP_CALLBACKS_H

#include "stm32f1xx_hal.h"

#ifdef __cplusplus
extern "C" {
#endif

void cpp_init();

void usart_rx_check();

#ifdef __cplusplus
};
#endif


#endif //IMSAI8080STM32PROGRAMMER_CPP_CALLBACKS_H
