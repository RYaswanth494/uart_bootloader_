/*
 * FLASH.h
 *
 *  Created on: Jul 3, 2025
 *      Author: maday
 */

#define FLASH_BASE      0x40022000

#define FLASH_ACR       (*(volatile uint32_t *)(FLASH_BASE + 0x00))
