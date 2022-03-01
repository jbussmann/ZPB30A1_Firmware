# ZPB30A1 Firmware
This repository is there to build an open-source firmware for the ZPB30A1 
electronic load (often sold as "60W/110W electronic load" without any article 
number).


## Features
* Modes
    * CC: Constant current
    * CR: Constant resistance
    * CP: Constant power
    * CV: Constant voltage (slow regulation due to hardware limitations)
* Easily usable menu system with many configuration options
* Logging of all operating parameters via UART.
* Much better accuracy than stock firmware.
* Clean firmware structure for easy extendability.


## Original Firmware
The original firmware has read out protection enabled. Therefore you can't go
back to this version once you flash a different one. But this firmware aims to
be much better in every possible way. If you need a feature either add it on
your own and submit a pull request or open an issue and wait till I add it.


## Compiler
This software requires [Small Device C Compiler (SDCC)](http://sdcc.sourceforge.net/)
version 3.8 or higher (3.7 sometimes crashes during compilation).


## Hardware platform
There are different hardware versions available requiring changes in the code.

### Display driver
The original units were equipped with TM1650 display drivers, whereas newer 
units use ET6226 drivers. While the chips are pin compatible, the layout changed 
from a shared clock line to a shared data line. The config file contains a 
`#define DISP_DRIVER_ET6226` to uncomment for use with ET6226 drivers.

The TM1650 drivers are mounted on the underside of the display board. The 
ET6226 drivers are sandwiched between display board and LED segment displays, 
while the underside of the board stays unpopulated. Also the ET6226 driver board 
is possibly marked as V2.9. See image folder or [this issue](https://github.com/herm/ZPB30A1_Firmware/issues/3) 
for further information. 

## Power rating
The load is available with 60W or 110W power rating, distinguishable by the size 
of the heatsink. The 60W version has a heatsink of roughly the hight and width 
of the fan, whereas the heatsink of the 110W version is noticably higher and 
wider than the fan. Uncomment `#define MAX_POWER_110W` in the config file to 
increase maximum allowable power dissipation.


## Chip
The datasheet of the STM8S005 claims a write endurance of only 100 flash cycles
but this is only for marketing purposes as it [contains the same die](https://hackaday.io/project/16097-eforth-for-cheap-stm8s-gadgets/log/76731-stm8l001j3-a-new-sop8-chip-and-the-limits-of-stm8flash)
as the STM8S105 which is rated for 10000 cycles. So you don't have to worry
about bricking your device by flashing it too often. Mine has far more than 100
cycles and still works. You can easily verify the two chips are the same as you
can write the whole 1kB of EEPROM the STM8S105 has instead of only 128 bytes
as claimed by the STM8S005 datasheet.


## Flashing
As the original firmware has the bootloader disabled a STLink programmer is 
needed in order to unlock and flash the chip. Under Windows, the programmer 
is interfaced using [ST Visual Programmer (STVP)](https://www.st.com/en/development-tools/stvp-stm8.html),
minimal files of the commandline version can be found in the stpv folder. For 
other operating systems [stm8flash](https://github.com/vdudouyt/stm8flash) is
used.

Connect the programmer like this:

![Programmer connection](images/stlink.jpg)

If you are programming the chip for the first time you have to unlock it.
'''WARNING:''' This irreversibly deletes the original firmware.

    make unlock

Then you write the new firmware with

    make flash

and if you are flashing for the first time you should also clear the EEPROM:

    make clear_eeprom

## Menu
Contrary to the original firmware which requires rebooting to change modes this
firmware is completely configurable by an integrated menu system. Push the
encoder button to select an item. The "Run" button acts as a back button in most
situations. Only in the top level menu it is used to enable the electronic load.
The currently selected option blinks. When setting a numeric value the two
LEDs between the displays show the selected digit.
Values shown with a decimal point are in the unit shown by the LEDs or on the
display. If no decimal point is shown it means the display shows 1/1000 of the
selected unit.
### Examples
* 10.0 + V LED: 10.0V
* 1.23 + A LED: 1.23A
* 900 + V LED: 900mV = 0.9V


### Menu structure
* MODE
    * CC: Constant current (default)
    * CV: Constant voltage
    * CR: Constant resistance
    * CW: Constant power
* VAL: Sets the target value for the currently selected mode. The upper display
        shows the unit.
* ILIM: Current limit (not active in CC mode)
* ...: More settings
    * BEEP: Beeper on/off
    * CUTO: Undervoltage cutoff
        * ENAB: Enable/disable
        * CVAL: Cutoff value in Volt
    * MAXP: Maximum power action
        * OFF: Turn off load when the required power would be greater than the hardware limit
        * LIM: Reduce load current to stay within hardware limits

## Run mode
While in run mode the top display show V, Ah, or Wh. The bottom display show
the current.
The unit in the top display switches automatically after some seconds. Rotating the encoder
changes the unit manually and disables automatic switching.
Pressing the encoder enters a menu to change the current setpoint without exiting
run mode.

### Error codes
* OVP: Over voltage protection. Voltage connected to P+/P- is too high. (Note: This function can only warn about voltages which are slightly to high. Large voltages will destroy the electronic load!)
* OVLD: The load can't maintain the set value. Usually this means that the source can't deliver enough current or the source's voltage is to low.
* PWR: Power required to maintain the setpoint is greater than hardware's power limit.
* TEMP: Temperature is to high. Check if the fan is working and the thermistor is connected.
* SUP: 12V input voltage is too low. Connect better power supply.
* INT: Internal error. Should not happen. Check the source code where this error is set and try to fix it.

## History
This firmware started as a project to extend the firmware written by
[soundstorm](https://github.com/ArduinoHannover/ZPB30A1_Firmware) but it turned
out as an almost complete rewrite which keeps the user interface idea.

## Schematic
Schematic can be found in [hardware/schematic.pdf].

### Schematic corrections:
* R5 = 10k
* R27 = 1k
* D6 = reversed polarity

### Component locations
![Component locations](images/components.jpg)
