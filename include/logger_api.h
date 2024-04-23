
#include "common-defines.h"

void logger_init(void);
bool DBG_LOG_EVENT(uint8_t moduleID, uint8_t eventID, uint8_t dataSize, uint32_t data, uint8_t priority);