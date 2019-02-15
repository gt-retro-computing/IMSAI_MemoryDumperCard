//
// Created by Codetector on 2019/2/14.
//

#ifndef IMSAI8080STM32PROGRAMMER_SHAREDSTRUCTS_H
#define IMSAI8080STM32PROGRAMMER_SHAREDSTRUCTS_H
typedef struct {
    GPIO_TypeDef *gpio;
    uint16_t pin;
} bus_pin;
#endif //IMSAI8080STM32PROGRAMMER_SHAREDSTRUCTS_H
