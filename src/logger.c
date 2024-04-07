#include "logger.h"

void logger_init(logger_buffer_t* bfr, logger_event_t* buffer, uint32_t bufferSize){
	bfr->buffer = buffer;
	bfr->currentIndex = 0;
	
	for (uint16_t i = 0; i < bufferSize; i++){
		bfr->buffer[i].data = (uint8_t*)"CONTINENTAL/CELAD!";
		bfr->buffer[i].eventID =  i;
		bfr->buffer[i].priority = i;
		bfr->buffer[i].moduleID = i;
		bfr->buffer[i].timestamp = false; 
	}		
}



void logger_update_counter(uint32_t counter){
	flash_page_erase(COUNTER_PAGE);
	flash_write((uint32_t)COUNTER_ADDR, &counter, COUNTER_SIZE);
	
}

void logger_write(logger_buffer_t* bfr, uint32_t bufferSize) {
	uint32_t counter = 0;
	flash_read((uint32_t)COUNTER_ADDR, &counter, 4);
	for(uint16_t i = 0; i < bufferSize; i++){
		char* data = strncat(bfr->buffer[i].eventID, bfr->buffer[i].data, 16);
		
		flash_write((uint32_t)START_ADDR + (uint32_t)counter, (uint8_t*)data, EVENT_SIZE);
		counter += EVENT_SIZE;	
	}
	logger_update_counter(counter);
}


void logger_print(logger_buffer_t* bfr, uint32_t bufferSize) {
	for (uint32_t i = 0; i < bufferSize; i++){
		/*printf("|%s|%d|%d|%d|%s|", bfr->buffer[i].data,
					   bfr->buffer[i].eventID,
					   bfr->buffer[i].priority,
					   bfr->buffer[i].moduleID,
					   bfr->buffer[i].timestamp ? "true" : "false");
		
		*/
		printf("%p", bfr->buffer[i]);			   
		printf("\n");
	}
	
}

