CC = sdcc
LD = sdld
STM8FLASH = stm8flash

CFLAGS = --std-sdcc99

.PHONY: flash
flash: controller.ihx
	$(STM8FLASH) -c stlinkv2 -p stm8s003f3 -s flash -w controller.ihx

controller.ihx: main.c
	$(CC) -lstm8 -mstm8 --out-fmt-ihx $(CFLAGS) $(LDFLAGS) $< -o $@

.PHONY: clean
clean:
	rm -f controller.ihx
