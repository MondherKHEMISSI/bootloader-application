#ifndef FLASH_H_
#define FLASH_H_

#include "base.h"
#include "common-defines.h"

#define FLASH_ACR_OFFSET           (0x000)
#define FLASH_ACR                  (*(volatile unsigned int*) (FLASH_PERIPHERAL + FLASH_ACR_OFFSET))

#define FLASH_KEYR_OFFSET          (0x008)
#define FLASH_KEYR                 (*(volatile unsigned int*) (FLASH_PERIPHERAL + FLASH_KEYR_OFFSET))

#define FLASH_SR_OFFSET            (0x010)
#define FLASH_SR                   (*(volatile unsigned int*) (FLASH_PERIPHERAL + FLASH_SR_OFFSET))

#define FLASH_CR_OFFSET            (0x014)
#define FLASH_CR                   (*(volatile unsigned int*) (FLASH_PERIPHERAL + FLASH_CR_OFFSET))


/*Prototypes*/
void flash_unlock(void);
void flash_lock(void);
void flash_erase_page(uint32_t page);
void flash_program_double_word(uint32_t addr, uint64_t data);
void flash_program(uint32_t addr, uint8_t* data, uint32_t length);

void flash_page_erase(uint32_t page);
void flash_write(const uint32_t addr, uint8_t* data, const uint32_t length);
void flash_read(const uint32_t addr, uint8_t* data, uint32_t size);
void flash_clear_status_flags(void);
void flash_erase_mass(void);
void flash_mass_erase(void);





#endif
