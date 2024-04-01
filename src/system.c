

#include "system.h"

#define FLASH_ACR_LATENCY_2      (1U << 1)
#define RCC_CFGR_HPRE1_2         (1U << 11)
//#define RCC_CFGR_PLLXTPRE_HSE    ()

#define RCC_CR_HSEON             (1U << 16)
#define RCC_CR_HSERDY            (1U << 17)
#define RCC_PLLCFGR_PLLSRC       (3U << 0)
#define RCC_CFGR_PLLMULL9        (9U << 8)
#define RCC_CR_PLLON             (1U << 24)
#define RCC_CR_PLLRDY            (1U << 25)
#define RCC_CFGR_SW_PLL          (1U << 1)
#define RCC_CFGR_SWS_PLL         (1U << 4)

 
#define STK_CSR_ENABLE           (1U << 0)
#define STK_CSR_TICKINT          (1U << 1)
#define STK_CSR_CLKSOURCE        (1U << 2)

volatile uint32_t msTicks = 0;

void SysTick_Handler(void){
	msTicks++;
}

void delay(int ms){
	uint32_t expected_ticks = msTicks + ms;
	while(msTicks < expected_ticks) {
		__asm__("nop");
	}
}

/*
void rcc_setup(void){

	FLASH_ACR |= FLASH_ACR_LATENCY_2;
	
	RCC_CFGR  |= RCC_CFGR_HPRE1_2;
	//RCC_CFGR  |= RCC_CFGR_PLLXTPRE_HSE;
	
	RCC_CR    |= RCC_CR_HSEON;
	while (!(RCC_CR & RCC_CR_HSERDY));
    
    	RCC_PLLCFGR |= RCC_PLLCFGR_PLLSRC;
	RCC_PLLCFGR |= RCC_CFGR_PLLMULL9;
	RCC_CR      |= RCC_CR_PLLON;
	while (!(RCC_CR & RCC_CR_PLLRDY));
	
	RCC_CFGR   |= RCC_CFGR_SW_PLL;
	while (!(RCC_CFGR & RCC_CFGR_SWS_PLL));
}
*/
void configure_systick(uint32_t ticks){

	STK_RVR = (uint32_t)(ticks - 1UL);
	
	STK_CVR = 0UL;

	STK_CSR = STK_CSR_CLKSOURCE |
                  STK_CSR_TICKINT   |
                  STK_CSR_ENABLE;

}

void system_setup(void){
	//rcc_setup();
	configure_systick(PERIPHERAL_CLOCK / 1000);

}

