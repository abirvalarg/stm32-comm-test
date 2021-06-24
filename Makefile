PREFIX=arm-none-eabi-
CC=$(PREFIX)gcc
AS=$(PREFIX)as
LD=$(PREFIX)ld
OBJCOPY=$(PREFIX)objcopy
OBJDUMP=$(PREFIX)objdump -D

CFLAGS=-c -mthumb -O2 -std=c11
SFLAGS=-mthumb
LFLAGS=-nostdlib --gc-sections

OUTPUT=comm_test

CSRC=$(wildcard src/*.c)
SSRC=$(wildcard src/*.s)
OBJ=${CSRC:src/%.c=obj/%.o} ${SSRC:src/%.s=obj/%.o}
HDR=$(wildcard src/*.h) $(wildcard src/*.inc)

all: $(OUTPUT).bin

dfu: $(OUTPUT).bin
	dfu-util -D $< -a 0 -s 0x08000000

dump: $(OUTPUT)
	$(OBJDUMP) $< | less

$(OUTPUT).bin: $(OUTPUT)
	$(OBJCOPY) -O binary $< $@

$(OUTPUT): link.ld $(OBJ)
	$(LD) $(LFLAGS) -o $@ -T $^

obj/%.o: src/%.s $(HDR) Makefile
	@mkdir -p $(@D)
	$(AS) $(SFLAGS) -o $@ $<

obj/%.o: src/%.c $(HDR) Makefile
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -o $@ $<

clear:
	@rm -r obj $(OUTPUT){,.bin} 2> /dev/null || true

.PHONY: all dump clear
