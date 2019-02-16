CC = sdcc
LD = sdld

CFLAGS = --std-sdcc99

.PHONY: flash
flash: controller.ihx
	stm8flash -c stlinkv2 -p sm8s003f3 -s flash -w controller.ihx

controller.ihx: main.c
	$(CC) -lstm8 -mstm8 --out-fmt-ihx $(CFLAGS) $(LDFLAGS) $< -o $@

.PHONY: clean
clean:
	rm -f controller.ihx
