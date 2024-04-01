/*
 * gpio.h
 *
 *  Created on: Feb 24, 2024
 *      Author: mondher
 */

#ifndef GPIO_H_
#define GPIO_H_

#include "base.h"

#define GPIOA_MODER_OFFSET             (0x00)
#define GPIOA_MODER                    (*(volatile unsigned int *)(GPIOA_PERIPHERAL + GPIOA_MODER_OFFSET))

#define GPIOA_ODR_OFFSET               (0x14)
#define GPIOA_ODR                      (*(volatile unsigned int *)(GPIOA_PERIPHERAL + GPIOA_ODR_OFFSET))

#define GPIOC_MODER_OFFSET             (0x00)
#define GPIOC_MODER                    (*(volatile unsigned int *)(GPIOC_PERIPHERAL + GPIOC_MODER_OFFSET))

#define GPIOC_IDR_OFFSET               (0x10)
#define GPIOC_IDR                      (*(volatile unsigned int *)(GPIOC_PERIPHERAL + GPIOC_IDR_OFFSET))

#define RCC_IOPENR_OFFSET              (0x34)
#define RCC_IOPENR                     (*(volatile unsigned int *)(RCC_PERIPHERAL + RCC_IOPENR_OFFSET))

#define GPIOA_AFRL_OFFSET			   (0x20)
#define GPIOA_AFRL                     (*(volatile unsigned int *)(GPIOA_PERIPHERAL + GPIOA_AFRL_OFFSET))

//Prototype
void gpio_init(void);
void led_toggle_onButton(void);
void led_toggle(void);
//void delay(void);


#endif /* GPIO_H_ */
