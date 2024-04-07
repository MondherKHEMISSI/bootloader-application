
#include "system.h"
#include "gpio.h"
#include "usart.h"
#include "flash.h"
#include "dma.h"
#include "logger.h"
//#include "scb.h"

/*static char* concatenate_string(char* s, char* s1)
{
    int i;
 
    int j = strlen(s);
 
    for (i = 0; s1[i] != '\0'; i++) {
        s[i + j] = s1[i];
    }
 
    s[i + j] = '\0';
 
    return s;
}
*/

#define BUFFER_SIZE           (2048 / 32)

int main(void)
{
	logger_buffer_t bfr = {0};
	logger_event_t buffer[BUFFER_SIZE] = {0};
	
	char* data = "|12|Continental_Celad|2|FDCAN|True\r\n\0";
	
	//counter = concatenate_string(i + 0, "\r\n\0");
	/*
	uint8_t counter[32] = {0};	
	for (uint16_t i = 0; i < 32; i++){
		counter[i] = 48 + i;		
	}
	*/
	
	uint32_t counter = 0;
	

		
	//vector_setup();
	system_setup();
	gpio_init();
	usart2_init();
	/*
	dma_init();
	uint8_t data_read[34] = {0};
	flash_read(0x0807F7E0, data_read, 40);
	data_read[32] = *(uint8_t*)"\r";
	data_read[33] = *(uint8_t*)"\n";
	dma_config((uint32_t)data_read, (uint32_t)&USART2_TDR, 34);
	*/
	logger_init(&bfr, &buffer,BUFFER_SIZE);

	flash_mass_erase();
	for(uint16_t i = 0; i < BUFFER_SIZE; i++){
		flash_write((uint32_t)START_ADDR + counter, (uint8_t*)data, 40);
		counter += 40;
	}
	
	char str[8]; // Assuming a sufficiently large array to store the string
    	sprintf(str, "%ld", counter);
	flash_write((uint32_t)COUNTER_ADDR, (uint8_t*)str, 8);
	
	
	
	
	/*
	flash_write(counter_addr + 24, counter, 32);

	flash_write(0x0807F000, counter, 32);
	
	flash_write(0x0807F7E0, counter, 32);
	
	flash_write(0x0807E000, (uint8_t*)data, 24);
	
	flash_write(0x0807E000 + 24, counter, 32);
	*/
	
	//logger_write(&bfr,BUFFER_SIZE);
	
    /* Loop forever */
	for(;;){
		led_toggle_onButton();

		while(usart2_is_data_available()){
			usart2_write(usart2_read());
		}

		led_toggle();
			
	
	}
}
