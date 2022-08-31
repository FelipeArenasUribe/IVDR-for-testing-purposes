/*
 * UART.h
 *
 *  Created on: Aug 5, 2016
 *      Author: julianecme
 */

#ifndef UART_H_
#define UART_H_

#define UART0RX 2 //PTA2
#define UART0TX 3 //PTA3
#define UART1RX 10 //PTF2
#define UART1TX 11 //PTF3
#define UART2RX 30 //PTD6
#define UART2TX 31 //PTD7

#define UART0RX_PIN 2 //PTA2
#define UART0TX_PIN 3 //PTA3
#define UART1RX_PIN 2 //PTF2
#define UART1TX_PIN 3 //PTF3
#define UART2RX_PIN 6 //PTD6
#define UART2TX_PIN 7 //PTD7


void UART2_Init(void);
void UART1_Init(void);
void UART0_Init(void);
void Uart_SendChar(uint8_t uart, uint8_t send);
void UART0_SCI0_IRQHandler (void);

#endif /* UART_H_ */
