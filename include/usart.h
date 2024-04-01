/*
 * usart.h
 *
 *  Created on: Feb 24, 2024
 *      Author: mondher
 */

#ifndef USART_H_
#define USART_H_

#include "base.h"
#include "common-defines.h"

#define USART2_CR1_OFFSET        (0x00)
#define USART2_CR1               (*(volatile unsigned int *)(USART2_PERIPHERAL + USART2_CR1_OFFSET))

#define USART2_CR3_OFFSET        (0x08)
#define USART2_CR3               (*(volatile unsigned int *)(USART2_PERIPHERAL + USART2_CR3_OFFSET))

#define USART2_BRR_OFFSET        (0x0C)
#define USART2_BRR               (*(volatile unsigned int *)(USART2_PERIPHERAL + USART2_BRR_OFFSET))

#define USART2_ISR_OFFSET        (0x1C)
#define USART2_ISR               (*(volatile unsigned int *)(USART2_PERIPHERAL + USART2_ISR_OFFSET))

#define USART2_RDR_OFFSET        (0x24)
#define USART2_RDR               (*(volatile unsigned int *)(USART2_PERIPHERAL + USART2_RDR_OFFSET))

#define USART2_TDR_OFFSET        (0x28)
#define USART2_TDR               (*(volatile unsigned int *)(USART2_PERIPHERAL + USART2_TDR_OFFSET))

#define RCC_APBENR1_OFFSET       (0x3C)
#define RCC_APBENR1              (*(volatile unsigned int *)(RCC_PERIPHERAL + RCC_APBENR1_OFFSET))



/*Prototypes*/
void usart2_init(void);
void usart2_it_config(void);
void usart_set_baudrate(uint32_t peripheral_clock, uint32_t baudrate);
void usart2_write(uint8_t data);
uint8_t usart2_read(void);
bool usart2_is_data_available(void);


#endif /* USART_H_ */
