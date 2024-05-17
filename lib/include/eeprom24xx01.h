/*
 * Copyright (c) 2024 Antonio González
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef _EEPROM24XX01_H_
#define _EEPROM24XX01_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pico.h"
#include "hardware/i2c.h"

/** \file eeprom24xx01.h
 * \brief Library for using a EEPROM 24xx01 with the Raspberry Pi Pico
 * 
*/


/*
1 Kbit EEPROM

One block of 128 x 8-bit memory (= 128 x 1 byte)
*/

#define EEPROM_I2C_ADDRESS 0x50
#define EEPROM_BLOCK_SIZE 128
#define EEPROM_PAGE_SIZE 8
#define EEPROM_WRITE_TIME_MS 5

typedef struct eeprom24xx01 {
    i2c_inst_t *i2c_port;
    uint8_t i2c_addr;
} eeprom24xx01_t;

/*! \brief Initialise the EEPROM
 * 
 * \param i2c_port The I2C instance, either i2c0 or i2c1
 * \param i2c_addr The I2C address of the EEPROM device
 * \param eeprom Pointer to the structure that stores the EEPROM info
 */
void eeprom_init(i2c_inst_t *i2c_port, uint8_t i2c_addr,
                 eeprom24xx01_t *eeprom);

/*! \brief Erase the EEPROM
 * 
 * \param eeprom Pointer to the structure that stores the EEPROM info
 */
void eeprom_erase(eeprom24xx01_t *eeprom);

/*! \brief Byte write
 * 
 * \param addr The EEPROM's address byte (0..127)
 * \param val The value to write
 * \param eeprom Pointer to the structure that stores the EEPROM info
 */
void eeprom_write_byte(uint8_t addr, uint8_t val,
                       eeprom24xx01_t *eeprom);

/*! \brief Page write
 * 
 * Writes one page (i.e. 8 bytes for the 24xx01) at once.
 *
 * \param addr The address of the first data byte within the block. Must
 * be a multiple of the page size.
 * \param buf Data array to send, up to 8 bytes in size
 * \param eeprom Pointer to the structure that stores the EEPROM info
 */
void eeprom_write_page(uint8_t addr, uint8_t buf[],
                       eeprom24xx01_t *eeprom);

/*! \brief Byte read
 *
 * \param addr The EEPROM's address byte (0..127)
 * \param dst Pointer to byte to receive data
 * \param eeprom Pointer to the structure that stores the EEPROM info
 */
void eeprom_read_byte(uint8_t *addr, uint8_t *dst,
                      eeprom24xx01_t *eeprom);

/*! \brief Page read
 *
 * \param addr The address of the first data byte within the block. Must
 * be a multiple of the page size.
 * \param dst Pointer to buffer to receive data
 * \param eeprom Pointer to the structure that stores the EEPROM info
 */
void eeprom_read_page(uint8_t *addr, uint8_t dst[],
                      eeprom24xx01_t *eeprom);

#endif
