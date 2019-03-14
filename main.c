#include <stdint.h>
#include <stdbool.h>
#include <registers.h>
#include <uart.h>

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
	PB_CR1 |= ((1 << 3));
	PB_CR2 &= ~((1 << 3));

	//PD2
	/* LEFT BUMPER */
	PD_DDR &= ~LEFT_BUMPER_BTN;
	PD_CR1 |= LEFT_BUMPER_BTN;
	PD_CR2 &= ~LEFT_BUMPER_BTN;
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

static bool read_left_bumper(void) {
	return !(PD_IDR & LEFT_BUMPER_BTN);
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

void main(void) {
	uint8_t uart_char;

	cfg_hw();
	uart_init();

	set_sensor_enable(1);
	set_beep(0);
	set_buck(1);
	set_leds(0,0);
	set_motor_left(0,0);
	set_motor_right(0,0);

	/*while (1) {
		if (read_btn()) {
			set_beep(1);
			set_leds(1,0);
		} else {
			set_beep(0);
			set_leds(0,1);
		}

		uart_writes("CC dille :)\n");
		uart_writes((PB_IDR & (1 << 3)) ? "PB3 = 1" : "PB3 = 0");
	}*/

	while (1) {
		/* Emergency stop */
		if (read_btn()) {
			set_motor_left(0,0);
			set_motor_right(0,0);
		}

		/* Handle UART commands */
		if (uart_read_available()) {
			uart_char = uart_read_nonblocking();

			switch (uart_char) {
			/* Move robot backwards */
			case 's':
				set_motor_left(1,0);
				set_motor_right(0,1);
				break;
			/* Move robot forward */
			case 'z':
				set_motor_left(0,1);
				set_motor_right(1,0);
				break;
			/* Move to the left */
			case 'q':
				set_motor_left(0,0);
				set_motor_right(0,1);
				break;
			/* Move to the right */
			case 'd':
				set_motor_left(0,1);
				set_motor_right(0,0);
				break;
			/* Rotate clockwise */
			case 'e':
				set_motor_left(0,1);
				set_motor_right(0,1);
				break;
			/* Rotate anti-clockwise */
			case 'a':
				set_motor_left(1,0);
				set_motor_right(1,0);
				break;
			/* Stop motors */
			case 'x':
				set_motor_left(0,0);
				set_motor_right(0,0);
				break;
			/* Enable beep */
			case 'b':
				set_beep(1);
				break;
			/* Stop beep */
			case 'n':
				set_beep(0);
				break;
			/* Green LED */
			case 'o':
				set_leds(0,1);
				break;
			/* Red LED */
			case 'p':
				set_leds(1,0);
				break;
			/* Both LEDs */
			case 'l':
				set_leds(1,1);
				break;
			/* No LEDs */
			case 'm':
				set_leds(0,0);
				break;
			/* Display data */
			case 't':
				uart_writes("left bumper:");
				uart_write(read_left_bumper() ? '1' : '0');
				uart_writes("\r\n");
				break;
			default:
				break;
			}
		}
	}
}