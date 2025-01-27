CC=sdcc
STVP=..\stvp\stvp_cmdline
SVFP_FALGS=-Port=USB -ProgMode=SWIM -verbose -no_loop -no_log
STM8FLASH=stm8flash
CFLAGS=-mstm8 --std-sdcc11 --opt-code-speed
DEFINES=STM8S005
PROCESSOR=STM8S005K6
STLINK_VERSION=2

MAIN=electronic_load.c
SRC=display.c uart.c utils.c fan.c ui.c systick.c load.c settings.c \
 	adc.c beeper.c menu_items.c
BUILDDIR=build

SRC:=$(MAIN) $(SRC)
REL=$(SRC:%.c=$(BUILDDIR)/%.rel)
IHX=$(MAIN:%.c=$(BUILDDIR)/%.ihx)
HEX=$(IHX:.ihx=.hex)
DEP=$(REL:%.rel=%.d)

.PHONY: all mkdir bin clean flash unlock clear_eeprom \
		mkdir_windows bin_windows clean_windows flash_windows unlock_windows clear_eeprom_windows \
		mkdir_unix bin_unix clean_unix flash_unix unlock_unix clear_eeprom_unix

all: bin

# SDCC includes working wrong on Windows with "/" slahes
ifeq ($(OS),Windows_NT)
PROGRAMMER=ST-LINK
mkdir: mkdir_windows
bin: bin_windows
clean: clean_windows
flash: flash_windows
unlock: unlock_windows
clear_eeprom: clear_eeprom_windows
else
PROGRAMMER=stlinkv$(STLINK_VERSION)
mkdir: mkdir_unix
bin: bin_unix
clean: clean_unix
flash: flash_unix
unlock: unlock_unix
clear_eeprom: clear_eeprom_unix
endif

CFLAGS+=$(INCLUDES) -D $(DEFINES)

$(IHX): $(REL)
	$(CC) $(CFLAGS) $^ -o $@

#-MMD = automatically create dependency files
$(BUILDDIR)/%.rel: %.c mkdir
	$(CC) -c $(CFLAGS) -MMD $< -o $@

$(HEX): $(IHX)
	packihx $< > $@

mkdir_windows:
	@if not exist $(BUILDDIR) mkdir $(BUILDDIR)

mkdir_unix:
	@mkdir -p $(BUILDDIR)

bin_windows: mkdir $(HEX)

bin_unix: mkdir $(IHX)

clean_windows:
	@rmdir /s /q $(BUILDDIR)

clean_unix:
	rm -rf $(BUILDDIR)

flash_windows: $(HEX)
	$(STVP) -BoardName=$(PROGRAMMER) -Device=$(PROCESSOR) $(SVFP_FALGS) -FileProg=$<

flash_unix: $(IHX)
	$(STM8FLASH) -c $(PROGRAMMER) -p $(PROCESSOR) -w $<

unlock_windows: unlock.hex
	$(STVP) -BoardName=$(PROGRAMMER) -Device=$(PROCESSOR) $(SVFP_FALGS) -FileOption=$<

unlock_unix:
	$(STM8FLASH) -c $(PROGRAMMER) -p $(PROCESSOR) -u # Works in stm8flash versions after git commit f3f547b4

clear_eeprom_windows: empty_eeprom.hex
	$(STVP) -BoardName=$(PROGRAMMER) -Device=$(PROCESSOR) $(SVFP_FALGS) -FileData=$<

clear_eeprom_unix: empty_eeprom
	$(STM8FLASH) -c $(PROGRAMMER) -p $(PROCESSOR) -s eeprom -w $<

-include $(DEP)
