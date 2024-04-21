


#ifndef SYSTEM_H_
#define SYSTEM_H_


#include "base.h"
#include "common-defines.h"

/*
#define FLASH_ACR_OFFSET              (0x00)
#define FLASH_ACR                     (*(volatile unsigned int *) (FLASH_PERIPHERAL + FLASH_ACR_OFFSET))
*/
#define RCC_CR_OFFSET                 (0x00)
#define RCC_CR                        (*(volatile unsigned int *) (RCC_PERIPHERAL + RCC_CR_OFFSET))


#define RCC_CFGR_OFFSET               (0x08)
#define RCC_CFGR                      (*(volatile unsigned int *) (RCC_PERIPHERAL + RCC_CFGR_OFFSET))

#define RCC_PLLCFGR_OFFSET            (0x0C)
#define RCC_PLLCFGR                   (*(volatile unsigned int *) (RCC_PERIPHERAL + RCC_PLLCFGR_OFFSET))


#define STK_CSR_OFFSET                (0x00)
#define STK_CSR                       (*(volatile unsigned int *) (SYSTICK_BASE + STK_CSR_OFFSET))

#define STK_RVR_OFFSET                (0x04)
#define STK_RVR                       (*(volatile unsigned int *) (SYSTICK_BASE + STK_RVR_OFFSET))

#define STK_CVR_OFFSET                (0x08)
#define STK_CVR                       (*(volatile unsigned int *) (SYSTICK_BASE + STK_CVR_OFFSET))

#define STK_CALIB_OFFSET              (0x0C)
#define STK_CALIB                     (*(volatile unsigned int *) (SYSTICK_BASE + STK_CALIB_OFFSET))              


/*Prototypes*/

void rcc_setup(void);
void configure_systick(uint32_t ticks);
void system_setup(void);
uint32_t getSysTick(void);
void delay(int ms);




#endif /* SYSTEM_H_ */
