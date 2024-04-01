/*
 * usart.c
 *
 *  Created on: Feb 24, 2024
 *      Author: mondher
 */

#include "usart.h"
#include "gpio.h"
#include "it.h"
#include "ring-buffer.h"

/*Enable bits*/
#define CR1_UE              (1U << 0)
#define CR1_RE              (1U << 2)
#define CR1_TE              (1U << 3)

#define ISR_RXNE            (1U << 5)
#define ISR_TXE             (1U << 7)

#define BAUDRATE            115200

#define CR1_RXNEIE          (1U << 5)
#define CR1_TXEIE           (1U << 7)

#define CR3_DMAR            (1U << 6)
#define CR3_DMAT            (1U << 7)

#define RING_BUFFER_SIZE     (128)

ring_buffer_t rb = {0U};
uint8_t data_buffer[RING_BUFFER_SIZE] = {0U};

void usart2_it_config(void){
	USART2_CR1 |= CR1_RXNEIE;
	NVIC_ISER  |= (1U << 28);
}

void usart2_init(void){
	/*Clock*/
	RCC_APBENR1 |= (1U << 17);

	/*Alternate function*/
		//DONE

	// DMA Receive/Transmit
	USART2_CR3 |= CR3_DMAT;
	
	/*Configure baudrate*/
	usart_set_baudrate(PERIPHERAL_CLOCK, BAUDRATE);

	/*Enable RX and TX*/
	USART2_CR1 |= CR1_TE;
	USART2_CR1 |= CR1_RE;

	/*Configure interrupt*/
	usart2_it_config();

	/*Enable USART*/
	USART2_CR1 |= CR1_UE;

	/*Ring buffer setup*/
	ring_buffer_setup(&rb, data_buffer, RING_BUFFER_SIZE);

}

void usart_set_baudrate(uint32_t peripheral_clock, uint32_t baudrate){
	USART2_BRR = ((peripheral_clock + (baudrate/2U)) / baudrate);
}

void usart2_write(uint8_t data){
	while(!(USART2_ISR & ISR_TXE));
	USART2_TDR = data + 1;

}


uint8_t usart2_read(void){
	uint8_t byte = 0;
	(void)ring_buffer_read(&rb, &byte);
	return byte;
}


void USART2_LPUART2_IRQHandler(void){
	GPIOA_ODR ^= (1U << 5); //GREEN_LED;
	(void)ring_buffer_write(&rb, USART2_RDR);
}


bool usart2_is_data_available(void){
	return !ring_buffer_is_empty(&rb);
}
