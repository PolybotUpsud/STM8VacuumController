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
	PC_DDR &= ~PWR_BTN;
	PC_CR1 |= PWR_BTN;
	PC_CR2 &= ~PWR_BTN;

	/* BUCK ENABLE */
	PC_DDR |= BUCK_EN;
	PC_CR1 |= BUCK_EN;

	/* MOTORS */
	PB_DDR |= MOT_L_BI | MOT_L_FI;
	PB_CR1 |= MOT_L_BI | MOT_L_FI;
	PC_DDR |= MOT_R_BI | MOT_R_FI;
	PC_CR1 |= MOT_R_BI | MOT_R_FI;

	/* ENABLE SENSORS & LEDS */
	PD_DDR |= SENSE_EN;
	PD_CR1 |= SENSE_EN;

	PB_DDR &= ~((1 << 3));
	PB_CR1 |= ((1 << 3));;
	PB_CR2 &= ~((1 << 3));;
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

static void set_beep(bool en) {
	if (en) {
		PD_ODR |= BUZZER;
	} else {
		PD_ODR &= ~BUZZER;
	}
}

static bool read_btn(void) {
	return !(PC_IDR & PWR_BTN);
}

static void set_motor_left(bool fi, bool bi) {
	PB_ODR |= (fi ? MOT_L_FI : 0) | (bi ? MOT_L_BI : 0);
	PB_ODR &= ~((!fi ? MOT_L_FI : 0) | (!bi ? MOT_L_BI : 0));
}

static void set_motor_right(bool fi, bool bi) {
	PC_ODR |= (fi ? MOT_R_FI : 0) | (bi ? MOT_R_BI : 0);
	PC_ODR &= ~((!fi ? MOT_R_FI : 0) | (!bi ? MOT_R_BI : 0));
}

static void set_sensor_enable(bool en) {
	if (en) {
		PD_ODR |= SENSE_EN;
	} else {
		PD_ODR &= ~SENSE_EN;
	}
}

static void uart_init() {
    UART_BRR2 = 0x00;
    UART_BRR1 = 0x0D;
    UART_CR2 = (1 << UART_TEN) | (1 << UART_REN);
}

static void uart_write(uint8_t data) {
    UART_DR = data;
    while (!(UART_SR & (1 << UART_TC)));
}

static void uart_writes(const char *str) {
	for (; *str; str++) {
		uart_write(*str);
	}
}

void main(void) {
	/* Initialization code for internal peripherals */
	cfg_hw();
	uart_init();

	/* Enable sensor power, needed to power LEDs on */
	set_sensor_enable(1);

	/* Enable the buck regulator, needed to power motors on */
	set_buck(1);

	/* Enable the buzzer*/
	set_beep(1);

	/* Turn on red LED on */
	set_leds(1,0);
	/* Turn on green LED on */
	set_leds(0,1);

	/* Turn on left motor */
	set_motor_left(1,0);
	/* Reverse its direction */
	set_motor_left(0,1);

	/* Turn on right motor */
	set_motor_right(1,0);
	/* Reverse its direction */
	set_motor_right(0,1);

	/* Turn off both motors */
	set_motor_left(0,0);
	set_motor_right(0,0);

	/* Read button state */
	int btn_status = read_btn();

	/* Send a character to UART */
	uart_write('a');
	/* Send a string to UART */
	uart_writes("Hello world\n");
}