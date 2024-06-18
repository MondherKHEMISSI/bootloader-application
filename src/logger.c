#include "logger.h"
#include "common-defines.h"
#include "flash.h"
#include "system.h"

#define BUFFER_SIZE         (10)

#define COUNTER_PAGE        (383)
#define COUNTER_ADDR        (0x0807FBF0)
#define START_ADDR          (0x08000A00)
#define PAGE_SIZE           (0x800)



logger_ring_buffer_t lg_rb         = {0};
logger_event_t buffer[BUFFER_SIZE] = {0};
uint32_t counter = 0;


void logger_init(void){
    logger_ring_buffer_init(&lg_rb);
}
void logger_ring_buffer_init(logger_ring_buffer_t* lg_rb ){
	lg_rb->buffer = buffer;
    lg_rb->writeIndex = 0;
    lg_rb->readIndex = 0;
    lg_rb->full = false;

    uint32_t counter = 0;

    flash_write(COUNTER_ADDR, (uint8_t*)&counter, 4);

}

bool logger_ring_buffer_write(logger_ring_buffer_t* lg_rb , uint8_t moduleID, uint8_t eventID, uint8_t dataSize, uint32_t data, uint8_t priority){
    uint8_t local_write_index = lg_rb->writeIndex;
    uint8_t local_read_index = lg_rb->readIndex;

    uint8_t next_write_index = (lg_rb->writeIndex + 1) % BUFFER_SIZE;

    if (logger_ring_buffer_is_full(lg_rb)){
        return false;
    }


    lg_rb->buffer[local_write_index].timestamp = getSysTick();
    lg_rb->buffer[local_write_index].moduleID = moduleID;
    lg_rb->buffer[local_write_index].eventID = eventID;
    lg_rb->buffer[local_write_index].dataSize = dataSize;
    lg_rb->buffer[local_write_index].data = data;
    lg_rb->buffer[local_write_index].priority = priority;

    lg_rb->writeIndex = next_write_index;

    if (next_write_index == local_read_index){
        lg_rb->full = true;
    }
    return true;
}


bool logger_ring_buffer_read(logger_ring_buffer_t* lg_rb, logger_event_t* event){
    /* uint8_t local_write_index = lg_rb->writeIndex; */
    uint8_t local_read_index= lg_rb->readIndex;

    if (logger_ring_buffer_is_empty(lg_rb))
        return false;


    event->timestamp  = lg_rb->buffer[local_read_index].timestamp;
    event->moduleID   = lg_rb->buffer[local_read_index].moduleID;
    event->eventID    = lg_rb->buffer[local_read_index].eventID;
    event->dataSize   = lg_rb->buffer[local_read_index].dataSize;
    event->data       = lg_rb->buffer[local_read_index].data;
    event->priority   = lg_rb->buffer[local_read_index].priority;

    lg_rb->buffer[local_read_index].timestamp  = 0;
    lg_rb->buffer[local_read_index].moduleID   = 0;
    lg_rb->buffer[local_read_index].eventID    = 0;
    lg_rb->buffer[local_read_index].dataSize   = 0;
    lg_rb->buffer[local_read_index].data       = 0;
    lg_rb->buffer[local_read_index].priority   = 0;




    lg_rb->readIndex = (local_read_index + 1) % BUFFER_SIZE;

    lg_rb->full = false;

    return true;

}

bool logger_ring_buffer_is_empty(logger_ring_buffer_t* lg_rb){
    return (lg_rb->writeIndex == lg_rb->readIndex) && (!logger_ring_buffer_is_full(lg_rb));
}

bool logger_ring_buffer_is_full(logger_ring_buffer_t* lg_rb){
    return lg_rb->full;
}

bool DBG_LOG_EVENT(uint8_t moduleID, uint8_t eventID, uint8_t dataSize, uint32_t data, uint8_t priority){

	bool lub_Ret = logger_ring_buffer_write(&lg_rb, moduleID, eventID, dataSize, data, priority);

	if (logger_ring_buffer_is_full(&lg_rb) == true){
		logger_flash(&lg_rb);
	}


	return lub_Ret;
}

void logger_flash(logger_ring_buffer_t* lg_rb){
    uint32_t counter = 0;
	flash_read(COUNTER_ADDR, (uint8_t*)&counter, 4);
	flash_write(START_ADDR + counter, (uint8_t*)lg_rb->buffer, sizeof(logger_event_t) * BUFFER_SIZE);
	counter += sizeof(logger_event_t) * BUFFER_SIZE;

	flash_mass_erase();
	flash_write(COUNTER_ADDR, (uint8_t*)&counter, 4);

	lg_rb->full = false;
}