//
// Created by Will Gulian on 2019-02-19.
//

#include <stm32f1xx_hal.h>
#include <system_stm32f1xx.h>

#include <cstddef>
#include <cstdint>
#include <USART.h>
#include <cstring>

#include "USART.h"

namespace USART {
    uint8_t DMA_RX_Buffer[64];
}

void USART::rx_check() {
    static size_t old_pos;
    size_t pos;

    /* Calculate current position in buffer */
    pos = sizeof(DMA_RX_Buffer) - hdma_usart1_rx.Instance->CNDTR;
    if (pos != old_pos) {                       /* Check change in received data */
        if (pos > old_pos) {                    /* Current position is over previous one */
            /* We are in "linear" mode */
            /* Process data directly by subtracting "pointers" */
            process_uart_data(&DMA_RX_Buffer[old_pos], pos - old_pos);
        } else {
            /* We are in "overflow" mode */
            /* First process data to the end of buffer */
            process_uart_data(&DMA_RX_Buffer[old_pos], sizeof(DMA_RX_Buffer) - old_pos);
            /* Continue with beginning of buffer */
            process_uart_data(&DMA_RX_Buffer[0], pos);
        }
    }
    old_pos = pos;                              /* Save current position as old */

    /* Check and manually update if we reached end of buffer */
    if (old_pos == sizeof(DMA_RX_Buffer)) {
        old_pos = 0;
    }
}

void USART::process_uart_data(uint8_t *data, size_t len) {
    send_data(data, len);
}

void USART::send_string(const char* str) {
    send_data((uint8_t *)str, strlen(str));
}

void USART::send_data(uint8_t* data, size_t len) {
    HAL_UART_Transmit(&huart1, data, (uint16_t) len, 1000);
}

void usart_rx_check() {
    USART::rx_check();
}