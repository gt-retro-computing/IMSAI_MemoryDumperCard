//
// Created by Will Gulian on 2019-02-19.
//

#ifndef IMSAI8080STM32PROGRAMMER_USART_H
#define IMSAI8080STM32PROGRAMMER_USART_H

#include <stm32f1xx_hal.h>

extern UART_HandleTypeDef huart1;
extern DMA_HandleTypeDef hdma_usart1_rx;

namespace USART {

    extern uint8_t DMA_RX_Buffer[64];

    void rx_check();

    void process_uart_data(uint8_t* data, size_t len);

    void send_string(const char* str);

    void send_data(uint8_t* data, size_t len);

}

extern "C" {
    void usart_rx_check();
};


#endif //IMSAI8080STM32PROGRAMMER_USART_H
