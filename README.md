# pico-eeprom24xx01

A C library for using a 24XX01 EEPROM with the Raspberry Pi Pico

The [24XX01][24xx01] is a 1 Kbit Electrically Erasable PROM from
Microchip. It is organised as one block of 128 x 8-bit memory and a I2C
serial interface.

[24xx01]: https://ww1.microchip.com/downloads/aemDocuments/documents/MPD/ProductDocuments/DataSheets/24AA01-24LC01B-24FC01-1K-I2C-Serial-EEPROM-20001711N.pdf


## Wiring

EEPROM Pin | Connect to
-----------|-----------
1, 2, 3 | NC
4 (Vss) | GND
5 (SDA) | Pico SDA (e.g. pin 8)
6 (SCL) | Pico SCL (e.g. pin 9)
7 (WP)  | GND for r/w, or 3V3 for read-only
8 (Vcc) | 3V3

In addition, add one pull-up 10k resistor each to SDA and SCL.


## Software

1. Configure `CMakeLists.txt` in your base project to include the path
   to the **pico-eeprom24xx01** library. Add **pico-eeprom24xx01** to
   the list of target libraries. E.g. if the **pico-eeprom24xx01**
   library is located one directory above (`../`) the current one your
   `CMakeLists.txt` file should include
```cmake
.
.
.
include(pico_sdk_import.cmake)
add_subdirectory(../pico-eeprom24xx01/lib eeprom24xx01)

target_link_libraries(touch
        pico_stdlib
        hardware_i2c
        pico-eeprom24xx01
)
.
.
.
```

2. Use the library; see the examples directory.
