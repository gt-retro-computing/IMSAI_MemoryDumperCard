//
// Created by Will Gulian on 2019-02-19.
//

#include <USART.h>
#include "cpp_callbacks.h"

void cpp_init() {
    if(HAL_DMA_Start(&hdma_usart1_rx, (uint32_t)&huart1.Instance->DR, (uint32_t) USART::DMA_RX_Buffer, 64) != HAL_OK) {
        USART::send_string("error");
    }
}

