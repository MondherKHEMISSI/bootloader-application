#ifndef LOGGER_H
#define LOGGER_H

#include "logger_api.h"

#include "common-defines.h"

typedef struct logger_event_t{
	uint32_t timestamp;
	uint8_t moduleID;
	uint8_t eventID;
	uint8_t dataSize;
	uint32_t data;
	uint8_t priority;
}logger_event_t;



typedef struct logger_ring_buffer_t{
	logger_event_t* buffer;
	uint8_t writeIndex;
	uint8_t readIndex;
	bool full;
}logger_ring_buffer_t;



void logger_ring_buffer_init(logger_ring_buffer_t* lg_rb);
bool logger_ring_buffer_write(logger_ring_buffer_t* lg_rb, uint8_t moduleID, uint8_t eventID, uint8_t dataSize, uint32_t data, uint8_t priority);
bool logger_ring_buffer_read(logger_ring_buffer_t* lg_rb, logger_event_t* event);
bool logger_ring_buffer_is_empty(logger_ring_buffer_t* lg_rb);
bool logger_ring_buffer_is_full(logger_ring_buffer_t* lg_rb);
void logger_flash(logger_ring_buffer_t* lg_rb);


#endif
