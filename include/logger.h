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



bool logger_ring_buffer_write(uint8_t moduleID, uint8_t eventID, uint8_t dataSize, uint32_t data, uint8_t priority);
bool logger_ring_buffer_read(logger_event_t* event);
bool logger_ring_buffer_is_empty();
bool logger_ring_buffer_is_full();


#endif
