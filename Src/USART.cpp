//
// Created by Will Gulian on 2019-02-19.
//

#include <vector>
#include <functional>

#include <stm32f1xx_hal.h>
#include <system_stm32f1xx.h>
#include <cmsis_os.h>

#include <cstddef>
#include <cstdint>
#include <USART.h>
#include <cstring>
#include <stdarg.h>
#include <Hex.h>
#include <bus_io.h>

#include "USART.h"

namespace USART {
    uint8_t DMA_RX_Buffer[64];
    uint8_t line_buffer[1000];

    char printf_buffer[1000];

    uint8_t *line_buffer_ptr = nullptr;

    void printf(const char *fmt, ...);
}

void USART::init() {

    printf("Hello world %d\r\n", 567);

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

void process_uart_line(uint8_t *data, size_t len) {
    if (len == 0) {
        // sanity check, this should never be called with a zero length
        return;
    }

    uint8_t target = *data;

    if (target == ':') {
        USART::printf("HEX:\r\n");
        USART::send_data(data, len);
        USART::send_string("\r\n");

        Hex hex;

        if (hex.read_string(data, len) < 0) {
            USART::send_string("Malformed HEX :(\r\n");
            return;
        }

//        USART::printf("Start Addr: %x\r\n", hex.start_addr);
//        USART::printf("Total Bytes %x\r\n", hex.length);
//
//        for (size_t i = 0; i < hex.length; i++) {
//            USART::printf("%x\r\n", hex.buf[i]);
//        }

        S100::acquire();
        S100::write_mem(hex.start_addr, hex.buf, 0, hex.length);
        S100::release();

        USART::send_string("Written\r\n");

        return;
    }

    USART::send_string("Unknown instruction:\r\n");
    USART::send_data(data, len);
    USART::send_string("\r\n");
}

void USART::process_uart_data(uint8_t *data, size_t len) {
    enum uart_data_t {
        udt_start,
        udt_data
    };

    static uart_data_t state = udt_start;

    if (line_buffer_ptr == nullptr) {
        line_buffer_ptr = line_buffer;
    }

    for (size_t i = 0; i < len; i++) {
        uint8_t byte = *(data++);

        switch (byte) {
            case '\r':
            case '\n':
                if (state != udt_start) {
                    process_uart_line(line_buffer, line_buffer_ptr - line_buffer);
                    line_buffer_ptr = line_buffer;
                }
                state = udt_start;
                break;
            default:
                *(line_buffer_ptr++) = byte;
                state = udt_data;
                break;
        }
    }
}


void USART::send_string(const char* str) {
    send_data((uint8_t *)str, strlen(str));
}

void USART::send_data(uint8_t* data, size_t len) {
    HAL_UART_Transmit(&huart1, data, (uint16_t) len, 1000);
}

void USART::printf(const char *fmt, ...) {
    va_list args;
    va_start(args, fmt);

    int written = vsnprintf(printf_buffer, sizeof(printf_buffer), fmt, args);
    if (written < 0) {
        send_string("failed to printf()\r\n");
    }

    if (written > sizeof(printf_buffer)) {
        written = sizeof(printf_buffer);
    }

    send_data((uint8_t *) printf_buffer, (size_t) written);

    va_end(args);
}

