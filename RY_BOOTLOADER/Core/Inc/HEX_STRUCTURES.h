/*
 * HEX_STRUCTURES.h
 *
 *  Created on: Jul 23, 2025
 *      Author: maday
 */

#ifndef INC_HEX_STRUCTURES_H_
#define INC_HEX_STRUCTURES_H_

#include<stdint.h>
uint16_t record_index = 0;
#define MAX_RECORDS 858

#pragma pack(1)
typedef struct{
	uint8_t Byte_count;
	uint8_t data[16];
	uint8_t check_sum;
	uint32_t address;
}__attribute__((packed))HEX_STRUCTURE;

#endif /* INC_HEX_STRUCTURES_H_ */
