#ifndef LOGGER_API_H
#define LOGGER_API_H
#include "common-defines.h"


typedef enum {
    E_LOGGER_MODULE_BBSTARTUP = 0,
    E_LOGGER_MODULE_BBCORE,
    E_LOGGER_MODULE_BBFLASH
}E_LOGGER_MODULE_ID;


void logger_init(void);
bool DBG_LOG_EVENT(uint8_t moduleID, uint8_t eventID, uint8_t dataSize, uint32_t data, uint8_t priority);





#endif /* !LOGGER_API_H */