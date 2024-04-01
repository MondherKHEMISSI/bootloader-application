/*
 * scb.h
 *
 *  Created on: Feb 28, 2024
 *      Author: mondher
 */

#ifndef SCB_H_
#define SCB_H_

#include "common-defines.h"

#define SCB_VTOR          (*(volatile uint32_t *)((((0xE0000000U) + 0xE000) + 0x0D00) + 0x08))

/*Prototypes*/
void vector_setup(void);

#endif /* SCB_H_ */
