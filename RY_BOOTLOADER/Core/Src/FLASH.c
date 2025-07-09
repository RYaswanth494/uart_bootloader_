/*
 * RCC_RY_FLASH.c
 *
 *  Created on: Jul 9, 2025
 *      Author: maday
 */
#include<stdint.h>
#include"FLASH_DEFINES.h"
//#define RY_FLASH_BASE 0x40022000U
#define RY_FLASH_ACR (*(volatile uint32_t *)(RY_FLASH_BASE + 0x00))
#define RY_FLASH_KEYR (*(volatile uint32_t *)(RY_FLASH_BASE + 0x04))
#define RY_FLASH_SR (*(volatile uint32_t *)(RY_FLASH_BASE + 0x0C))
#define RY_FLASH_CR (*(volatile uint32_t *)(RY_FLASH_BASE + 0x10))
#define RY_FLASH_AR (*(volatile uint32_t *)(RY_FLASH_BASE + 0x14))
#define RY_FLASH_OBR (*(volatile uint32_t *)(RY_FLASH_BASE + 0x1C))
#define RY_FLASH_WRPR (*(volatile uint32_t *)(RY_FLASH_BASE + 0x20))


static void RY_FLASH_Unlock(void) {
 if (RY_FLASH_CR & RY_FLASH_CR_LOCK) {
 RY_FLASH_KEYR = RY_FLASH_KEY1;
 RY_FLASH_KEYR = RY_FLASH_KEY2;
 }
}
static void RY_FLASH_Lock(void) {
 RY_FLASH_CR |= RY_FLASH_CR_LOCK;
}
static RY_FLASH_Status RY_FLASH_WaitForLastOperation(void) {
 uint32_t timeout = RY_FLASH_TIMEOUT;
 while ((RY_FLASH_SR & RY_FLASH_SR_BSY) && --timeout);
 if (timeout == 0) return RY_FLASH_ERR_TIMEOUT;
 if (RY_FLASH_SR & RY_FLASH_SR_WRPRTERR) return RY_FLASH_ERR_WRPRT;
 if (RY_FLASH_SR & RY_FLASH_SR_PGERR) return RY_FLASH_ERR_PG;
 if (RY_FLASH_SR & RY_FLASH_SR_EOP) RY_FLASH_SR |= RY_FLASH_SR_EOP;
 return RY_FLASH_OK;
}
RY_FLASH_Status RY_FLASH_ErasePage(uint32_t address) {
 if (address < APP_START_ADDR || address >= APP_END_ADDR || address % RY_FLASH_PAGE_SIZE != 0)
 return RY_FLASH_ERR_ADDR;
 RY_FLASH_Unlock();
 RY_FLASH_Status status = RY_FLASH_WaitForLastOperation();
 if (status != RY_FLASH_OK) return status;
 RY_FLASH_CR |= RY_FLASH_CR_PER;
 RY_FLASH_AR = address;
 RY_FLASH_CR |= RY_FLASH_CR_STRT;
 status = RY_FLASH_WaitForLastOperation();
 RY_FLASH_CR &= ~RY_FLASH_CR_PER;
 RY_FLASH_Lock();
 return status;
}
static RY_FLASH_Status RY_FLASH_ProgramHalfWord(uint32_t address, uint16_t data) {
 if ((address % 2) != 0 || address < APP_START_ADDR || address >= APP_END_ADDR)
 return RY_FLASH_ERR_ALIGN;
 RY_FLASH_Unlock();
 RY_FLASH_Status status = RY_FLASH_WaitForLastOperation();
 if (status != RY_FLASH_OK) return status;
 RY_FLASH_CR |= RY_FLASH_CR_PG;
 *(volatile uint16_t*)address = data;
 status = RY_FLASH_WaitForLastOperation();
 RY_FLASH_CR &= ~RY_FLASH_CR_PG;
 RY_FLASH_Lock();
 if (*(volatile uint16_t*)address != data) return RY_FLASH_ERR_VERIFY;
 return status;
}
RY_FLASH_Status RY_FLASH_ProgramBuffer(uint32_t address, const uint8_t *data, uint32_t length) {
 if ((address % 2) != 0 || address < APP_START_ADDR || (address + length) > APP_END_ADDR)
 return RY_FLASH_ERR_ALIGN;
 for (uint32_t i = 0; i < length; i += 2) {
 uint16_t halfword;
 if (i + 1 < length) {
 halfword = data[i] | (data[i + 1] << 8);
 } else {
 halfword = data[i] | (0xFF << 8); // Pad last byte
 }
 RY_FLASH_Status status = RY_FLASH_ProgramHalfWord(address + i, halfword);
 if (status != RY_FLASH_OK) return status;
 }
 return RY_FLASH_OK;
}
RY_FLASH_Status RY_FLASH_EraseAppRegion(void) {
 for (uint32_t addr = APP_START_ADDR; addr < APP_END_ADDR; addr += RY_FLASH_PAGE_SIZE) {
 RY_FLASH_Status status = RY_FLASH_ErasePage(addr);
 if (status != RY_FLASH_OK) return status;
 }
 return RY_FLASH_OK;
}
uint32_t RY_FLASH_CalculateCRC32(const uint8_t *data, uint32_t length) {
 uint32_t crc = 0xFFFFFFFF;
 for (uint32_t i = 0; i < length; i++) {
 crc ^= data[i];
 for (uint8_t j = 0; j < 8; j++)
 crc = (crc >> 1) ^ ((crc & 1) ? 0xEDB88320 : 0);
 }
 return ~crc;
}
RY_FLASH_Status RY_FLASH_VerifyBuffer(uint32_t address, const uint8_t *data, uint32_t length) {
 if (address < APP_START_ADDR || (address + length) > APP_END_ADDR)
 return RY_FLASH_ERR_ADDR;
for (uint32_t i = 0; i < length; i++) {
if (*(volatile uint8_t *)(address + i) != data[i])
return RY_FLASH_ERR_VERIFY;
}
return RY_FLASH_OK;
}

