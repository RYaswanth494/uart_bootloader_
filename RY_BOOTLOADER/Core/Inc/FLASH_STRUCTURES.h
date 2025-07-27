/*
 * FLASH_STRUCTURES.h
 *
 *  Created on: Jul 9, 2025
 *      Author: maday
 */

#ifndef FLASH_REGS_H
#define FLASH_REGS_H

#include <stdint.h>

//----------------------------------
// FLASH Base Address
//----------------------------------
//----------------------------------
// FLASH Access Control Register
//----------------------------------
typedef union {
    uint32_t  RY_ALL;
    struct {
        uint32_t RY_LATENCY : 3;
        uint32_t RY_HLFCYA  : 1;
        uint32_t RY_PRFTBE  : 1;
        uint32_t RY_PRFTBS  : 1;
        uint32_t RY_RESERVED : 26;
    } BITS;
} RY_FLASH_ACR_t;

//----------------------------------
// FLASH Status Register (SR)
//----------------------------------
typedef union {
    uint32_t RY_ALL;
    struct {
        uint32_t RY_BSY      : 1;
        uint32_t RY_RESERVED1: 1;
        uint32_t RY_PGERR    : 1;
        uint32_t RY_RESERVED2: 1;
        uint32_t RY_WRPRT    : 1;
        uint32_t RY_EOP      : 1;
        uint32_t RY_RESERVED3: 26;
    } BITS;
} RY_FLASH_SR_t;

//----------------------------------
// FLASH Control Register (CR)
//----------------------------------
typedef union {
    uint32_t RY_ALL;
    struct {
        uint32_t RY_PG       : 1;
        uint32_t RY_PER      : 1;
        uint32_t RY_MER      : 1;
        uint32_t RY_RESERVED1: 1;
        uint32_t RY_OPTPG    : 1;
        uint32_t RY_OPTER    : 1;
        uint32_t RY_STRT     : 1;
        uint32_t RY_LOCK     : 1;
        uint32_t RY_RESERVED2: 1;
        uint32_t RY_OPTWRE   : 1;
        uint32_t RY_ERRIE    : 1;
        uint32_t RY_RESERVED3: 1;
        uint32_t RY_EOPIE    : 1;
        uint32_t RY_RESERVED4: 19;
    } RY_BITS;
} RY_FLASH_CR_t;

//----------------------------------
// FLASH Full Register Map
//----------------------------------
typedef struct {
	RY_FLASH_ACR_t   RY_ACR;         // 0x00: Access Control
    volatile uint32_t RY_KEYR;    // 0x04: FPEC Key Register
    volatile uint32_t RY_OPTKEYR; // 0x08: Option Byte Key Register
    RY_FLASH_SR_t    RY_SR;          // 0x0C: Status Register
    RY_FLASH_CR_t    RY_CR;          // 0x10: Control Register
    volatile uint32_t RY_AR;      // 0x14: Flash Address Register
    uint32_t RY_RESERVED;         // 0x18: Reserved
    volatile uint32_t RY_OBR;     // 0x1C: Option Byte Register
    volatile uint32_t RY_WRPR;    // 0x20: Write Protection Register
} RY_FLASH_TypeDef;
//----------------------------------
// Macro to Access Flash
//----------------------------------
#define RY_FLASH   ((RY_FLASH_TypeDef *)0x40022000UL)

//----------------------------------
// Flash Key Values
//----------------------------------
#define RY_FLASH_KEY1  0x45670123UL
#define RY_FLASH_KEY2  0xCDEF89ABUL


#endif // FLASH_REGS_H

