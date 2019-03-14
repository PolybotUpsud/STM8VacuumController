#include <stdint.h>
#include <stdbool.h>

#include "registers.h"
#include "uart.h"

void uart_init() {
    UART_BRR2 = 0x00;
    UART_BRR1 = 0x0D;
    UART_CR2 = (1 << UART_TEN) | (1 << UART_REN);
}

uint8_t uart_read() {
	while (!(UART_SR & (1 << UART_RXNE)));
    return UART_DR;
}

bool uart_read_available() {
    return !!(UART_SR & (1 << UART_RXNE));
}

uint8_t uart_read_nonblocking() {
    return UART_DR;
}

void uart_write(uint8_t data) {
    UART_DR = data;
    while (!(UART_SR & (1 << UART_TC)));
}

void uart_writes(const char *str) {
	for (; *str; str++) {
		uart_write(*str);
	}
}

bool uart_write_available() {
    return !!(UART_SR & (1 << UART_TC));
}

void uart_write_nonblocking(uint8_t data) {
    UART_DR = data;
}