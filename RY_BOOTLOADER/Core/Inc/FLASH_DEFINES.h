/*
 * FLASH.h
 *
 *  Created on: Jul 3, 2025
 *      Author: maday
 */
typedef enum {
 RY_FLASH_OK = 0,
 RY_FLASH_ERR_BUSY,
 RY_FLASH_ERR_TIMEOUT,
 RY_FLASH_ERR_ADDR,
 RY_FLASH_ERR_ALIGN,
 RY_FLASH_ERR_PG,
 RY_FLASH_ERR_WRPRT,
 RY_FLASH_ERR_VERIFY
} RY_FLASH_Status;
#define RY_FLASH_BASE      0x40022000
#define RY_FLASH_ACR_LATENCY_0WS    (0 << 0)  // 0 wait states
#define RY_FLASH_ACR_LATENCY_1WS    (1 << 0)  // 1 wait state
#define RY_FLASH_ACR_LATENCY_2WS    (2 << 0)  // 2 wait states
#define RY_FLASH_ACR_PRFTBE         (1 << 4)  // Prefetch enable
#define RY_FLASH_ACR_PRFTBS         (1 << 5)  // Prefetch status (read-only)


#define RY_FLASH_SR_BSY             (1 << 0)  // Busy
#define RY_FLASH_SR_PGERR           (1 << 2)  // Programming error
#define RY_FLASH_SR_WRPRTERR        (1 << 4)  // Write protection error
#define RY_FLASH_SR_EOP             (1 << 5)  // End of operation


#define RY_FLASH_CR_PG              (1 << 0)  // Programming
#define RY_FLASH_CR_PER             (1 << 1)  // Page erase
#define RY_FLASH_CR_MER             (1 << 2)  // Mass erase
#define RY_FLASH_CR_OPTPG           (1 << 4)  // Option byte programming
#define RY_FLASH_CR_OPTER           (1 << 5)  // Option byte erase
#define RY_FLASH_CR_STRT            (1 << 6)  // Start operation
#define RY_FLASH_CR_LOCK            (1 << 7)  // Lock


#define RY_FLASH_OBR_OPTERR         (1 << 0)  // Option byte error
#define RY_FLASH_OBR_RDPRT          (1 << 1)  // Read protection
#define RY_FLASH_OBR_USER           (0xFF << 2)  // User options bits (2-9)
#define RY_FLASH_OBR_DATA0          (0xFF << 10)
#define RY_FLASH_OBR_DATA1          (0xFF << 18)

#define RY_FLASH_OPTKEY1            0x45670123UL
#define RY_FLASH_OPTKEY2            0xCDEF89ABUL

#define RY_FLASH_KEY1               0x45670123UL
#define RY_FLASH_KEY2               0xCDEF89ABUL

#define RY_FLASH_PAGE_SIZE 1024U
#define RY_FLASH_START_ADDR 0x08000000U
#define RY_FLASH_END_ADDR 0x08020000U
#define RY_FLASH_TIMEOUT 100000U
#define BOOTLOADER_SIZE (16 * 1024U)
#define APP_START_ADDR (RY_FLASH_START_ADDR + BOOTLOADER_SIZE)
#define APP_END_ADDR RY_FLASH_END_ADDR

