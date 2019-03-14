CC = sdcc
LD = sdld
STM8FLASH = stm8flash

CFLAGS = --std-sdcc99 -Iperipherals

OBJS=peripherals/uart.rel main.rel

.PHONY: flash
flash: controller.ihx
	$(STM8FLASH) -c stlinkv2 -p stm8s003f3 -s flash -w controller.ihx

controller.ihx: $(OBJS)
	$(CC) -lstm8 -mstm8 --out-fmt-ihx $(LDFLAGS) $(OBJS) -o $@

%.rel: %.c
	$(CC) -lstm8 -mstm8 $(CFLAGS) -c $< -o $@

.PHONY: clean
clean:
	rm -f controller.ihx
