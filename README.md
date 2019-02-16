# STM8 robot vacuum controller

This firmware replaces the firmware on a cheap KK290B vacuum cleaner. This project is a PoC, the robot hasn't been fully reversed yet.

## Toolchain

`sdcc` and `make` are required to build this project.

## SWIM pinout

```
1. 5V
2. GND
3. NRST
4. SWIM
```

You can use a cheap ST-LinkV2 clone with [stm8flash](https://github.com/vdudouyt/stm8flash) to flash your STM8.