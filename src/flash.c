#include "flash.h"

#define FLASH_FKEY1 0x45670123 
#define FLASH_FKEY2 0xCDEF89AB

#define FLASH_SR_BSY1      (1U << 16)
#define FLASH_SR_BSY2      (1U << 17)
#define FLASH_CR_LOCK      (1U << 31)
#define FLASH_CR_PER       (1U << 1)
#define FLASH_CR_MER1      (1U << 2)
#define FLASH_CR_MER2      (1U << 15)
#define FLASH_CR_STRT      (1U << 16)

#define FLASH_CR_PG        (1U << 0)


#define FLASH_SR_PGSERR    (1U << 7)
#define FLASH_SR_SIZERR    (1U << 6)
#define FLASH_SR_PGAERR    (1U << 5)
#define FLASH_SR_WRPERR    (1U << 4)
#define FLASH_SR_PROGERR   (1U << 3)
#define FLASH_SR_OPERR     (1U << 1)
#define FLASH_SR_EOP       (1U << 0)


#define LOGGER_START_PAGE  (256)
#define LOGGER_END_PAGE    (383)  


void flash_unlock(void){
	//keys as described in the data-sheets
	// Wait for the flash memory not to be busy
	while ((FLASH_SR & FLASH_SR_BSY2) == FLASH_SR_BSY2);
	// Check if the controller is unlocked already
	if ((FLASH_CR & FLASH_CR_LOCK) != 0 ){ 
		// Write the first key 
		FLASH_KEYR = FLASH_FKEY1;   
	    	// Write the second key
	    	FLASH_KEYR = FLASH_FKEY2;
	}	

}

void flash_lock(void){
	FLASH_CR |= FLASH_CR_LOCK;
}

void flash_erase_page(uint32_t page){

	// Wait until page erase is done
	while ((FLASH_SR & FLASH_SR_BSY2) == FLASH_SR_BSY2);
	
	
	
	flash_clear_status_flags();
	
	FLASH_CR |= FLASH_CR_PER; // Page erase operation
	FLASH_CR |= (page << 3);   // Set the address to the page to be written
	
	FLASH_CR |= FLASH_CR_STRT;// Start the page erase
	// If the end of operation bit is set...
	if ((FLASH_SR & FLASH_SR_EOP) == 0){
    		// Clear it, the operation was successful
    		FLASH_SR |= FLASH_SR_EOP;
	}
	//Otherwise there was an error
	else{
    	// Manage the error cases
	}
	// WAIT
	while ((FLASH_SR & FLASH_SR_BSY2) == FLASH_SR_BSY2);
	
	// Get out of page erase mode
	FLASH_CR &= ~FLASH_CR_PER;
}

void flash_program_double_word(uint32_t addr, uint64_t data){
	while ((FLASH_SR & FLASH_SR_BSY2) == FLASH_SR_BSY2);
	
	FLASH_CR |= FLASH_CR_PG;                   // Programing mode
	
	//WRITE DATA
	*(volatile uint32_t*)(addr)   = (uint32_t)data;
	*(volatile uint32_t*)(addr+4) = (uint32_t)(data >> 32);
	

	// Wait until the end of the operation
	
	// If the end of operation bit is set...
	if ((FLASH_SR & FLASH_SR_EOP) == 0){
    		// Clear it, the operation was successful
     		FLASH_SR |= FLASH_SR_EOP;
	}
	//Otherwise there was an error
	else{
    	// Manage the error cases
	}
	//WAIT
	while ((FLASH_SR & FLASH_SR_BSY2) == FLASH_SR_BSY2);
	
	FLASH_CR &= ~FLASH_CR_PG;
}


void flash_page_erase(uint32_t page){
	flash_unlock();
	flash_erase_page(page);
	flash_lock();
}

void flash_program(uint32_t addr, uint8_t* data, uint32_t length){
	for (uint32_t i = 0; i < length; i+=8){
		flash_program_double_word(addr + i, *(uint64_t*)(data + i));
	}
}

void flash_write(const uint32_t addr, uint8_t* data, const uint32_t length){
	flash_unlock();
	flash_program(addr, data, length);
	flash_lock();
	
}

void flash_read(const uint32_t addr, uint8_t* data, uint32_t size){
	for(uint16_t i = 0; i < size; i += 4){
		*((uint32_t*)(data + i)) = *(volatile uint32_t*)(addr + i);
	}
}

void flash_clear_status_flags(void)
{
	FLASH_SR |= FLASH_SR_WRPERR ;// Clear write protection error flag
	FLASH_SR |= FLASH_SR_PGSERR; // Clear programming sequence error flag
	FLASH_SR |= FLASH_SR_SIZERR; // Clear size error flag
	FLASH_SR |= FLASH_SR_PGAERR; // Clear Programming alignment error flag
	FLASH_SR |= FLASH_SR_PROGERR; // Clear programming error flag
	FLASH_SR |= FLASH_SR_PGSERR; // Clear programming sequence error
	FLASH_SR |= FLASH_SR_EOP;  // Clear End of operation flag
	FLASH_SR |= FLASH_SR_OPERR; // Clear Operation error flag


}

void flash_erase_mass(void){

	// Wait until page erase is done
	while ((FLASH_SR & FLASH_SR_BSY2) == FLASH_SR_BSY2);
	
	
	
	flash_clear_status_flags();
	
	//FLASH_CR |= FLASH_CR_MER1; // BANK 1 erase operation
	FLASH_CR |= FLASH_CR_MER2; // BANK 2 erase operation
	
	FLASH_CR |= FLASH_CR_STRT;// Start the MASS erase
	// If the end of operation bit is set...
	if ((FLASH_SR & FLASH_SR_EOP) == 0){
    		// Clear it, the operation was successful
    		FLASH_SR |= FLASH_SR_EOP;
	}
	//Otherwise there was an error
	else{
    	// Manage the error cases
	}
	// WAIT
	while ((FLASH_SR & FLASH_SR_BSY2) == FLASH_SR_BSY2);
	
	// Get out of page erase mode
	FLASH_CR &= ~FLASH_CR_PER;
}

void flash_mass_erase(void){
	flash_unlock();
	flash_erase_mass();
	flash_lock();	
}


