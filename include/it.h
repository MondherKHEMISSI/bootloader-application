/*
 * it.h
 *
 *  Created on: Feb 25, 2024
 *      Author: mondher
 */

#ifndef IT_H_
#define IT_H_

#include "base.h"

#define NVIC_ISER_OFFSET       (0x00)
#define NVIC_ISER              (*(volatile unsigned int *)(NVIC_BASE + NVIC_ISER_OFFSET))

#endif /* IT_H_ */
