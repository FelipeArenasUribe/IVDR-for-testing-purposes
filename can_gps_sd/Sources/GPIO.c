/*
 * GPIO.c
 *
 *  Created on: Aug 7, 2016
 *      Author: julianecme
 */

//#include "derivative.h"
#include <SKEAZ1284.h>
#include "GPIO.h"

void sw_init(void){
	CONFIG_PIN_AS_GPIO(PORT_D,SW1,INPUT); /* Configure BTN0 (PTD0) as an input */	
	CONFIG_PIN_AS_GPIO(PORT_D,SW2,INPUT); /* Configure BTN1 (PTD1) as an input */
	ENABLE_INPUT(PORT_D,SW1);			 /* Enable input SW1*/	
	ENABLE_INPUT(PORT_D,SW2);			/*  Enable input SW2*/
	PORT_PUE0 |= 0<<SW1; // Port: No internal pullup (default)
	PORT_PUE0 |= 0<<SW2; // Port: No internal pullup (default)
	/*GPIOA_PDDR |= ~(1<<SW1); // Port: Data Direction= input (default) 
	GPIOA_PIDR &= ~(1<<SW1); // Port: Input Disable= 0 (input enabled) 
	PORT_PUE0 |= 0<<SW1; // Port: No internal pullup (default) 
	GPIOA_PDDR |= ~(1<<SW2); // Port: Data Direction= input (default) 
	GPIOA_PIDR &= ~(1<<SW2); // Port: Input Disable= 0 (input enabled) 
	PORT_PUE0 |= 0<<SW2; // Port: No internal pullup (default) */
}

void led_init(void){
	CONFIG_PIN_AS_GPIO(PORT_C,LED1,OUTPUT); // Configure LED 0 (PTC0) as an output
	CONFIG_PIN_AS_GPIO(PORT_C,LED2,OUTPUT); // Configure LED 1 (PTC1) as an output
	CONFIG_PIN_AS_GPIO(PORT_C,LED3,OUTPUT); // Configure LED 2 (PTC2) as an output
	CONFIG_PIN_AS_GPIO(PORT_C,LED4,OUTPUT); // Configure LED 3 (PTC3) as an output
	/*GPIOA_PDDR |= 1<<LED1; // Port: Data Direction= output
	GPIOA_PIDR &= 1<<LED1; // Port: Input Disable= 1 (default)
	GPIOA_PDDR |= 1<<LED2; // Port: Data Direction= output
	GPIOA_PIDR &= 1<<LED2; // Port: Input Disable= 1 (default)
	GPIOA_PDDR |= 1<<LED3; // Port: Data Direction= output
	GPIOA_PIDR &= 1<<LED3; // Port: Input Disable= 1 (default)
	GPIOA_PDDR |= 1<<LED4; // Port: Data Direction= output
	GPIOA_PIDR &= 1<<LED4; // Port: Input Disable= 1 (default)*/
	
	led_off(LED1);
	led_off(LED2);
	led_off(LED3);
	led_off(LED4);
}
