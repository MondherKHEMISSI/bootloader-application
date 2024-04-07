#ifndef LOGGER_H
#define LOGGER_H

#include <stdio.h>
#include <string.h>
#include "common-defines.h"
#include "flash.h"


#define COUNTER_PAGE        (383)
#define COUNTER_ADDR        (0x0807F800)
#define START_ADDR          (0x08040000)
#define END_ADDR            (0x0807F800)
#define EVENT_SIZE          (32U)
#define COUNTER_SIZE        (4U)


typedef struct logger_event_t{
	uint8_t* data;
	uint32_t eventID;
	uint8_t priority;
	uint32_t moduleID;
	bool timestamp;
	
}logger_event_t;



typedef struct logger_buffer_t{
	logger_event_t* buffer;
	uint32_t currentIndex;
}logger_buffer_t;


void logger_init(logger_buffer_t* bfr, logger_event_t* buffer, uint32_t bufferSize);
void logger_print(logger_buffer_t* bfr, uint32_t bufferSize);
void logger_update_counter(uint32_t counter);
void logger_write(logger_buffer_t* bfr, uint32_t bufferSize);



#endif
