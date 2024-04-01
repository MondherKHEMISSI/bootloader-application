/*
 * gpio.c
 *
 *  Created on: Feb 24, 2024
 *      Author: mondher
 */

#include "gpio.h"
#include "system.h"

#define GPIOA  (1U << 0)
#define GPIOC  (1U << 2)

#define USER_BUTTON (1U << 13)
#define GREEN_LED   (1U << 5)

void gpio_init(void){

	//Clocks
	RCC_IOPENR |= GPIOA;
	RCC_IOPENR |= GPIOC;

	//MODES
		//PA5
	GPIOA_MODER |=  (1U << 10);
	GPIOA_MODER &= ~(1U << 11);
		//PC13
	GPIOC_MODER &= ~(1U << 26);
	GPIOC_MODER &= ~(1U << 27);

	/*AF1, USART2_TX = PA2, USART2_RX = PA3*/
	  //Mode
	GPIOA_MODER |=  (1U << 5); //PA2
	GPIOA_MODER &= ~(1U << 4);

	GPIOA_MODER |=  (1U << 7);//PA3
	GPIOA_MODER &= ~(1U << 6);
		//PA2
	GPIOA_AFRL |=  (1U << 8);
	GPIOA_AFRL &= ~(1U << 9);
	GPIOA_AFRL &= ~(1U << 10);
	GPIOA_AFRL &= ~(1U << 11);

		//PA3
	GPIOA_AFRL |=  (1U << 12);
	GPIOA_AFRL &= ~(1U << 13);
	GPIOA_AFRL &= ~(1U << 14);
	GPIOA_AFRL &= ~(1U << 15);
}

/*
void delay(void){
	for (unsigned int i = 0; i < 250000; i++){
		__asm__("nop");
	}
}
*/
void led_toggle_onButton(void){
	if (!(GPIOC_IDR & USER_BUTTON)){
		GPIOA_ODR ^= GREEN_LED;
		//delay(500);
	}
}


void led_toggle(void){
	GPIOA_ODR ^= GREEN_LED;
	delay(1000);
	GPIOA_ODR ^= GREEN_LED;
	delay(1000);
}



