/*
 * FLASH_DECLARATIONS.h
 *
 *  Created on: Jul 4, 2025
 *      Author: maday
 */

#ifndef INC_FLASH_DECLARATIONS_H_
#define INC_FLASH_DECLARATIONS_H_
#include"FLASH_DEFINES.h"
void RY_FLASH_Unlock(void);
void RY_FLASH_Lock(void);
RY_FLASH_Status RY_FLASH_WaitForLastOperation(void);
RY_FLASH_Status RY_FLASH_ErasePage(uint32_t address);
RY_FLASH_Status RY_FLASH_ProgramHalfWord(uint32_t address, uint16_t data);
RY_FLASH_Status RY_FLASH_ProgramBuffer(uint32_t address, const uint8_t *data, uint32_t length);
RY_FLASH_Status RY_FLASH_EraseAppRegion(void) ;

#endif /* INC_FLASH_DECLARATIONS_H_ */
