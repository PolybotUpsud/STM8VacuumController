#include <stdint.h>
#include <stdbool.h>

#include "registers.h"
#include "pins.h"

static void cfg_hw(void) {
	/* LEDS */
	PB_ODR |= GREEN_LED | RED_LED;
	PB_CR1 |= GREEN_LED | RED_LED;

	/* BUZZER */
	PD_ODR |= BUZZER;
	PD_CR1 |= BUZZER;

	/* POWER BUTTON */
	PD_ODR &= ~PWR_BTN;
	PD_CR1 &= ~PWR_BTN;

	/* BUCK ENABLE */
	PC_ODR |= BUCK_EN;
	PC_CR1 |= BUCK_EN;
}

static bool read_btn(void) {
	return !!(PD_IDR & PWR_BTN);
}

void main(void) {
	cfg_hw();
}