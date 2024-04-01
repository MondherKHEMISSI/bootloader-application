/*
 * base.h
 *
 *  Created on: Feb 24, 2024
 *      Author: mondher
 */

#ifndef BASE_H_
#define BASE_H_

#define PERIPHERAL_BASE                    (0x40000000)

#define APB_PERIPHERAL_OFFSET              (0x0000)
#define APB_PERIPHERAL                     (PERIPHERAL_BASE + APB_PERIPHERAL_OFFSET)

#define AHB_PERIPHERAL_OFFSET              (0x00020000)
#define AHB_PERIPHERAL                     (PERIPHERAL_BASE + AHB_PERIPHERAL_OFFSET)

#define IOPORT_PERIPHERAL_OFFSET           (0x10000000)
#define IOPORT_PERIPHERAL                  (PERIPHERAL_BASE + IOPORT_PERIPHERAL_OFFSET)

#define GPIOA_PERIPHERAL_OFFSET            (0x0000)
#define GPIOA_PERIPHERAL                   (IOPORT_PERIPHERAL + GPIOA_PERIPHERAL_OFFSET)

#define GPIOC_PERIPHERAL_OFFSET            (0x00000800)
#define GPIOC_PERIPHERAL                   (IOPORT_PERIPHERAL + GPIOC_PERIPHERAL_OFFSET)

#define USART2_PERIPHERAL_OFFSET           (0x00004400)
#define USART2_PERIPHERAL                  (APB_PERIPHERAL + USART2_PERIPHERAL_OFFSET)

#define RCC_PERIPHERAL_OFFSET              (0x00001000)
#define RCC_PERIPHERAL                     (AHB_PERIPHERAL + RCC_PERIPHERAL_OFFSET)

#define FLASH_PERIPHERAL_OFFSET            (0x00002000)
#define FLASH_PERIPHERAL                   (AHB_PERIPHERAL + FLASH_PERIPHERAL_OFFSET)

#define CORE_CM0PLUS                       (0xE0000000)

#define NVIC_BASE_OFFSET                   (0x0000E100)
#define NVIC_BASE                          (CORE_CM0PLUS + NVIC_BASE_OFFSET)

#define SYSTICK_BASE                       (0xE000E010)

#define DMA1_PERIPHERAL_OFFSET             (0x0000)
#define DMA1_PERIPHERAL                    (AHB_PERIPHERAL + DMA1_PERIPHERAL_OFFSET)

#define DMAMUX_PERIPHERAL_OFFSET           (0x00000800)
#define DMAMUX_PERIPHERAL                  (AHB_PERIPHERAL + DMAMUX_PERIPHERAL_OFFSET)

#define SYS_FREQ            16000000
#define PERIPHERAL_CLOCK    SYS_FREQ

#endif /* BASE_H_ */


