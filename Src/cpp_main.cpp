//
// Created by Will Gulian on 2019-02-14.
//

#include <USART.h>
#include "bus_io.h"
#include "Shift595.h"
#include "cmsis_os.h"
#include "cpp_main.h"

bus_pin led1{GPIOB, GPIO_PIN_0};
bus_pin led2{GPIOB, GPIO_PIN_1};

// active low

void cpp_init() {
    if(HAL_DMA_Start(&hdma_usart1_rx, (uint32_t)&huart1.Instance->DR, (uint32_t) USART::DMA_RX_Buffer, 64) != HAL_OK) {
        USART::send_string("error");
    }

}

void cpp_main() {
    S100::init();

    osDelay(500);

    S100::release();

    osDelay(100);

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wmissing-noreturn"
    while (true) {

        for (int i = 0; i < 2; i++) {

            bus_write_pin(&led1, i != 0);
            bus_write_pin(&led2, i == 0);

            osDelay(200);
        }

    }
#pragma clang diagnostic pop
}


