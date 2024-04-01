/*
 * scb.c
 *
 *  Created on: Feb 28, 2024
 *      Author: mondher
 */

#include "scb.h"

#define BOOTLOADER_SIZE            (0x8000U)

void vector_setup(void) {
  SCB_VTOR = BOOTLOADER_SIZE;
}
