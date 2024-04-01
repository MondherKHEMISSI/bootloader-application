#include <stdint.h>

#define SRAM_START 0x20000000U
#define SRAM_SIZE (144U * 1024U) // 144KB
#define SRAM_END ((SRAM_START) + (SRAM_SIZE))

#define STACK_START SRAM_END

extern uint32_t _etext;
extern uint32_t _sdata;
extern uint32_t _edata;
extern uint32_t _sbss;
extern uint32_t _ebss;

// Prototype of main
int main(void);

/* Function prototypes of STM32G0x1 system exception and IRQ handlers*/

void Reset_Handler                            (void);

void NMI_Handler                              (void) __attribute__((weak, alias("Default_Handler")));
void HardFault_Handler                        (void) __attribute__((weak, alias("Default_Handler")));
void SVC_Handler                              (void) __attribute__((weak, alias("Default_Handler")));
void PendSV_Handler                           (void) __attribute__((weak, alias("Default_Handler")));
void SysTick_Handler                          (void) __attribute__((weak, alias("Default_Handler")));

void WWDG_IRQHandler                          (void) __attribute__((weak, alias("Default_Handler")));
void PVD_IRQHandler                           (void) __attribute__((weak, alias("Default_Handler")));
void RTC_TAMP_IRQHandler                      (void) __attribute__((weak, alias("Default_Handler")));
void FLASH_IRQHandler                          (void) __attribute__((weak, alias("Default_Handler")));
void RCC_CRS_IRQHandler                          (void) __attribute__((weak, alias("Default_Handler")));
void EXTI0_1_IRQHandler                          (void) __attribute__((weak, alias("Default_Handler")));
void EXTI2_3_IRQHandler                          (void) __attribute__((weak, alias("Default_Handler")));
void EXTI4_15_IRQHandler                          (void) __attribute__((weak, alias("Default_Handler")));
void UCPD1_UCPD2_USB_IRQHandler                          (void) __attribute__((weak, alias("Default_Handler")));
void DMA1_Channel1_IRQHandler                          (void) __attribute__((weak, alias("Default_Handler")));
void DMA1_Channel2_3_IRQHandler                          (void) __attribute__((weak, alias("Default_Handler")));
void DMA1_Channel4_5_6_7_DMAMUX_DMA2_Channel1_2_3_4_5_IRQHandler   (void) __attribute__((weak, alias("Default_Handler")));
void ADC_COMP_IRQHandler                          (void) __attribute__((weak, alias("Default_Handler")));
void TIM1_BRK_UP_TRG_COM_IRQHandler                          (void) __attribute__((weak, alias("Default_Handler")));
void TIM1_CC_IRQHandler                          (void) __attribute__((weak, alias("Default_Handler")));
void TIM2_IRQHandler                          (void) __attribute__((weak, alias("Default_Handler")));
void TIM3_TIM4_IRQHandler                          (void) __attribute__((weak, alias("Default_Handler")));
void TIM6_DAC_LPTIM1_IRQHandler                          (void) __attribute__((weak, alias("Default_Handler")));
void TIM7_LPTIM2_IRQHandler                          (void) __attribute__((weak, alias("Default_Handler")));
void TIM14_IRQHandler                          (void) __attribute__((weak, alias("Default_Handler")));
void TIM15_IRQHandler                          (void) __attribute__((weak, alias("Default_Handler")));
void TIM16_FDCAN_IT0_IRQHandler                          (void) __attribute__((weak, alias("Default_Handler")));
void TIM17_FDCAN_IT1_IRQHandler                          (void) __attribute__((weak, alias("Default_Handler")));
void I2C1_IRQHandler                          (void) __attribute__((weak, alias("Default_Handler")));
void I2C2_I2C3_IRQHandler                          (void) __attribute__((weak, alias("Default_Handler")));
void SPI1_IRQHandler                          (void) __attribute__((weak, alias("Default_Handler")));
void SPI2_SPI3_IRQHandler                          (void) __attribute__((weak, alias("Default_Handler")));
void USART1_IRQHandler                          (void) __attribute__((weak, alias("Default_Handler")));
void USART2_LPUART2_IRQHandler                          (void) __attribute__((weak, alias("Default_Handler")));
void USART3_USART4_USART5_USART6_LPUART1__IRQHandler                          (void) __attribute__((weak, alias("Default_Handler")));
void CEC_IRQHandler                          (void) __attribute__((weak, alias("Default_Handler")));
void AES_RNG_IRQHandler                          (void) __attribute__((weak, alias("Default_Handler")));

uint32_t vectors[] __attribute__((section(".isr_vector"))) = {
  STACK_START,
  (uint32_t)Reset_Handler,
  (uint32_t)NMI_Handler,
  (uint32_t)HardFault_Handler,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  (uint32_t)SVC_Handler,
  0,
  0,
  (uint32_t)PendSV_Handler,
  (uint32_t)SysTick_Handler,

  (uint32_t)WWDG_IRQHandler,
  (uint32_t)PVD_IRQHandler,
  (uint32_t)RTC_TAMP_IRQHandler,
  (uint32_t)FLASH_IRQHandler,
  (uint32_t)RCC_CRS_IRQHandler,
  (uint32_t)EXTI0_1_IRQHandler,
  (uint32_t)EXTI2_3_IRQHandler,
  (uint32_t)EXTI4_15_IRQHandler,
  (uint32_t)UCPD1_UCPD2_USB_IRQHandler,
  (uint32_t)DMA1_Channel1_IRQHandler,
  (uint32_t)DMA1_Channel2_3_IRQHandler,
  (uint32_t)DMA1_Channel4_5_6_7_DMAMUX_DMA2_Channel1_2_3_4_5_IRQHandler,
  (uint32_t)ADC_COMP_IRQHandler,
  (uint32_t)TIM1_BRK_UP_TRG_COM_IRQHandler,
  (uint32_t)TIM1_CC_IRQHandler,
  (uint32_t)TIM2_IRQHandler,
  (uint32_t)TIM3_TIM4_IRQHandler,
  (uint32_t)TIM6_DAC_LPTIM1_IRQHandler,
  (uint32_t)TIM7_LPTIM2_IRQHandler,
  (uint32_t)TIM14_IRQHandler,
  (uint32_t)TIM15_IRQHandler,
  (uint32_t)TIM16_FDCAN_IT0_IRQHandler,
  (uint32_t)TIM17_FDCAN_IT1_IRQHandler,
  (uint32_t)I2C1_IRQHandler,
  (uint32_t)I2C2_I2C3_IRQHandler,
  (uint32_t)SPI1_IRQHandler,
  (uint32_t)SPI2_SPI3_IRQHandler,
  (uint32_t)USART1_IRQHandler,
  (uint32_t)USART2_LPUART2_IRQHandler,
  (uint32_t)USART3_USART4_USART5_USART6_LPUART1__IRQHandler,
  (uint32_t)CEC_IRQHandler,
  (uint32_t)AES_RNG_IRQHandler,
};

void Default_Handler(void) {
  while (1)
    ;
}

void Reset_Handler(void) {
  // Copy .data section to SRAM
  uint32_t size = (uint32_t)&_edata - (uint32_t)&_sdata;

  uint8_t* pDst = (uint8_t*)&_sdata; //sram
  uint8_t* pSrc = (uint8_t*)&_etext; //flash

  for (uint32_t i = 0; i < size; i++)
  {
    *pDst++ = *pSrc++;
  }

  // Init. the .bss section to zero in SRAM
  size = (uint32_t)&_ebss - (uint32_t)&_sbss;
  pDst = (uint8_t*)&_sbss;
  for (uint32_t i = 0; i < size; i++)
  {
    *pDst++ = 0;
  }
   
  // Call init function of std. library

  // Call main()
  main();
}
