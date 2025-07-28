/*
 * SYSTICK_DECLARATIONS.h
 *
 *  Created on: Jul 28, 2025
 *      Author: maday
 */

#ifndef INC_SYSTICK_DECLARATIONS_H_
#define INC_SYSTICK_DECLARATIONS_H_

typedef struct {
    void (*init)(uint32_t ticks_per_ms);
    void (*reset)(void);
    uint32_t (*get_ms)(void);
} SysTickDriver;


extern SysTickDriver systick;

#endif /* INC_SYSTICK_DECLARATIONS_H_ */
