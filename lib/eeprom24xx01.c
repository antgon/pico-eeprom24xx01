/*
 * Copyright (c) 2024 Antonio González
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "eeprom24xx01.h"


void eeprom_init(i2c_inst_t *i2c_port, uint8_t i2c_addr,
                 eeprom24xx01_t *eeprom){
    eeprom->i2c_port = i2c_port;
    eeprom->i2c_addr = i2c_addr;
}

void eeprom_erase(eeprom24xx01_t *eeprom){
    // Writes the value 255 to every address (which is how it is from
    // factory)
    for (uint8_t addr=0; addr<EEPROM_BLOCK_SIZE; addr++){
            eeprom_write_byte(addr, 255, eeprom);
        }
}

void eeprom_write_byte(uint8_t addr, uint8_t val,
                       eeprom24xx01_t *eeprom) {
    // addr is 0..127
    uint8_t buf[2] = {addr, val};
    i2c_write_blocking(eeprom->i2c_port, eeprom->i2c_addr, buf, 2,
                       false);
    // Without this pause, sequential write operations will fail. See
    // e.g. what happens when this function is placed in a loop without
    // this pause: not all values will be written to the EEPROM.
    sleep_ms(EEPROM_WRITE_TIME_MS);
};

void eeprom_write_page(uint8_t addr, uint8_t buf[],
                       eeprom24xx01_t *eeprom) {   
    // This function borrows from `SSD1306_send_buf` in ssd1306_i2c in
    // pico-examples.
    uint8_t *temp_buf = malloc(EEPROM_PAGE_SIZE + 1);
    temp_buf[0] = addr;
    memcpy(temp_buf+1, buf, EEPROM_PAGE_SIZE);
    i2c_write_blocking(eeprom->i2c_port, eeprom->i2c_addr, temp_buf,
                       EEPROM_PAGE_SIZE + 1, false);
    free(temp_buf);
    sleep_ms(EEPROM_WRITE_TIME_MS);
}

void eeprom_read_byte(uint8_t *addr, uint8_t *dst,
                      eeprom24xx01_t *eeprom) {    
    i2c_write_blocking(eeprom->i2c_port, eeprom->i2c_addr, addr, 1,
                       true);
    i2c_read_blocking(eeprom->i2c_port, eeprom->i2c_addr, dst, 1,
                      false);
}

void eeprom_read_page(uint8_t *addr, uint8_t dst[],
                      eeprom24xx01_t *eeprom) {
    i2c_write_blocking(eeprom->i2c_port, eeprom->i2c_addr, addr, 1,
                       true);
    i2c_read_blocking(eeprom->i2c_port, eeprom->i2c_addr, dst,
                      EEPROM_PAGE_SIZE, false);
}
