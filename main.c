#include <stdint.h>
#include <stdbool.h>

#include "registers.h"
#include "pins.h"

static void cfg_hw(void) {
	/* LEDS */
	PB_DDR |= GREEN_LED | RED_LED;
	PB_CR1 |= GREEN_LED | RED_LED;

	/* BUZZER */
	PD_DDR |= BUZZER;
	PD_CR1 |= BUZZER;

	/* POWER BUTTON */
	PD_DDR &= ~PWR_BTN;
	PD_CR1 &= ~PWR_BTN;

	/* BUCK ENABLE */
	PC_DDR |= BUCK_EN;
	PC_CR1 |= BUCK_EN;
}

static void set_leds(bool red, bool green) {
	PB_ODR |= (red ? RED_LED : 0) | (green ? GREEN_LED : 0);
	PB_ODR &= ~((!red ? RED_LED : 0) | (!green ? GREEN_LED : 0));
}

static void set_buck(bool en) {
	if (en) {
		PC_ODR |= BUCK_EN;
	} else {
		PC_ODR &= ~BUCK_EN;
	}
}

static bool read_btn(void) {
	return !!(PD_IDR & PWR_BTN);
}

void main(void) {
	cfg_hw();
}