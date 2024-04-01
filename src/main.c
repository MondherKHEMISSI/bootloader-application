
#include "system.h"
#include "gpio.h"
#include "usart.h"
#include "flash.h"
#include "dma.h"
//#include "scb.h"

#define page_addr       (0x0803A800)

int main(void)
{
	char *data = "HI EVERYONE!!\r\n\0";
		/*
		for (uint16_t i = 0; i < 1024; i++){
			data[i] = i & 0xff;		
		}
		*/
		
	//vector_setup();
	system_setup();
	gpio_init();
	usart2_init();
	dma_init();
	dma_config((uint32_t)data, (uint32_t)&USART2_TDR, 15);
	
	flash_erase(126);
	flash_write(page_addr, (uint8_t*)data, 16);
	
    /* Loop forever */
	for(;;){
		led_toggle_onButton();

		while(usart2_is_data_available()){
			usart2_write(usart2_read());
		}

		led_toggle();
	
	}
}
