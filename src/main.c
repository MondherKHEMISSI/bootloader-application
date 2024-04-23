
#include "system.h"
#include "gpio.h"
#include "usart.h"
#include "flash.h"
#include "dma.h"
#include "logger.h"
// #include "scb.h"


int main(void)
{

	// char* data = "|12|Continental_Celad|2|FDCAN|True\n\0";

	// counter = concatenate_string(i + 0, "\r\n\0");
	/*
	uint8_t counter[32] = {0};
	for (uint16_t i = 0; i < 32; i++){
		counter[i] = 48 + i;
	}
	*/

	// uint32_t counter = 0;

	// vector_setup();
	system_setup();
	gpio_init();
	usart2_init();
	/*
	uint8_t data_read[34] = {0};
	flash_read(0x0807F7E0, data_read, 40);
	data_read[32] = *(uint8_t*)"\r";
	data_read[33] = *(uint8_t*)"\n";
	*/

	flash_mass_erase();

	logger_init();

	/*
	dma_init();
	uint32_t ctr = 0;
	dma_config((uint32_t)&ctr, (uint32_t)&USART2_TDR, 4);
	flash_read(counter_addr, (uint8_t *)&ctr, 4);

	ctr += sizeof(logger_event_t) * 10;

	flash_mass_erase();
	flash_write(counter_addr, (uint8_t *)&ctr, 4);

	flash_read(counter_addr, (uint8_t *)&ctr, 4);

	ctr += sizeof(logger_event_t) * 10;

	flash_mass_erase();
	flash_write(counter_addr, (uint8_t *)&ctr, 4);

	*/

	uint32_t counter = 0;
	/* Loop forever */
	for (;;)
	{
		led_toggle_onButton();

		while (usart2_is_data_available())
		{
			usart2_write(usart2_read());
			DBG_LOG_EVENT(7, 1, sizeof(usart2_read()), usart2_read(), 1);
		}

		DBG_LOG_EVENT(5, 3, sizeof(counter), counter, 2);
		counter += 10;

		led_toggle();
	}
}
