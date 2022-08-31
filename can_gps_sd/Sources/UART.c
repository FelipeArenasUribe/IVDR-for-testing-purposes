/*
 * UART.c
 *
 *  Created on: Aug 5, 2016
 *      Author: julianecme
 */
//#include "derivative.h" /* include peripheral declarations */
#include <SKEAZ1284.h>
#include "UART.h"
#include "GPIO.h"

void UART2_Init(void){
	SIM_SCGC |=  SIM_SCGC_UART2_MASK;		/* Enable bus clock in UART2*/
	UART2_BDH = 0;							/* One stop bit*/
	UART2_BDL = 11;						// Baud rate at 130-9600  11-115200 5-230400
	UART2_C1  = 0;							/* No parity enable,8 bit format*/
	UART2_C2 |= UART_C2_TE_MASK;			/* Enable Transmitter*/
	UART2_C2 |= UART_C2_RE_MASK;			/* Enable Receiver*/
	//UART2_C2 |= UART_C2_RIE_MASK;			/* Enable Receiver interrupts*/
	SIM_PINSEL1 &= ~SIM_PINSEL1_UART2PS_MASK; // UART2PS=0 (default); PTD7 PTD6
	CONFIG_PIN_AS_GPIO(PORT_D,UART2RX,INPUT); /* Configure LED 1 (PTF2) as an intput RX*/
	CONFIG_PIN_AS_GPIO(PORT_D,UART2TX,OUTPUT); /* Configure LED 1 (PTF3) as an output TX*/
}
void UART1_Init(void){
	SIM_SCGC |=  SIM_SCGC_UART1_MASK;		// Enable bus clock in UART1
	UART1_BDH = 0;							/* One stop bit*/
	UART1_BDL = 11;						// Baud rate at 130-9600  11-115200
	UART1_C1  = 0;							/* No parity enable,8 bit format*/
	UART1_C2 |= UART_C2_TE_MASK;			/* Enable Transmitter*/
	UART1_C2 |= UART_C2_RE_MASK;			/* Enable Receiver*/
	//UART1_C2 |= UART_C2_RIE_MASK;			/* Enable Receiver interrupts*/
	SIM_PINSEL1 |= SIM_PINSEL1_UART1PS_MASK; // UART1PS=1 ; PTF2 PTF3
	CONFIG_PIN_AS_GPIO(PORT_F,UART1RX,INPUT); /* Configure LED 1 (PTF2) as an intput RX*/
	CONFIG_PIN_AS_GPIO(PORT_F,UART1TX,OUTPUT); /* Configure LED 1 (PTF3) as an output TX*/

}
void UART0_Init(void){
	SIM_PINSEL0 |= SIM_PINSEL_UART0PS_MASK; // UART1PS=1 ; PTA2 PTA3
	SIM_SCGC |=  SIM_SCGC_UART0_MASK;		// Enable bus clock in UART0
	UART0_BDH = 0;							/* One stop bit*/
	UART0_BDL = 130;						// Baud rate at 130-9600  11-115200
	UART0_C1  = 0;							/* No parity enable,8 bit format*/
	UART0_C2 |= UART_C2_TE_MASK;			/* Enable Transmitter*/
	UART0_C2 |= UART_C2_RE_MASK;			/* Enable Receiver*/
	UART0_C2 |= UART_C2_RIE_MASK;			/* Enable Receiver interrupts*/
	CONFIG_PIN_AS_GPIO(PORT_A,UART0RX,INPUT); /* Configure LED 1 (PTF2) as an intput RX*/
	CONFIG_PIN_AS_GPIO(PORT_A,UART0TX,OUTPUT); /* Configure LED 1 (PTF3) as an output TX*/
}
void Uart_SendChar(uint8_t uart, uint8_t send){
	if (uart==0){
		while((UART0_S1&UART_S1_TDRE_MASK)==0);		/* Wait for transmit buffer to be empty*/
		(void)UART0_S1;								/* Read UART0_S1 register*/
		UART0_D=send;		
	}
	if (uart==1){
		while((UART1_S1&UART_S1_TDRE_MASK)==0);		/* Wait for transmit buffer to be empty*/
		(void)UART1_S1;								/* Read UART1_S1 register*/
		UART1_D=send;		
	}
	if (uart==2){
		while((UART2_S1&UART_S1_TDRE_MASK)==0);		/* Wait for transmit buffer to be empty*/
		(void)UART2_S1;								/* Read UART2_S1 register*/
		UART2_D=send;		
	}
}

uint8_t  NMEA_mss[100],NMEA_GPGGA[100];
uint8_t i_gpsbuff=0,gps_par=0,controlGPS=0;
void UART0_SCI0_IRQHandler (void){
	uint8_t RecData,tempgps=0;
	while(( UART0_S1 & UART_S1_RDRF_MASK)==0);	/* Wait for received buffer to be full*/
	RecData= UART0_D;	
	//Uart_SendChar(2, RecData);
	if(RecData==36)//$=36
	  i_gpsbuff=0;
	NMEA_mss[i_gpsbuff]=RecData;
	i_gpsbuff++;
	tempgps=NMEA_mss[i_gpsbuff-2];
	if((RecData==10)&&(tempgps==13))//\n=10
	{
	  if((NMEA_mss[3]==NMEA_mss[4])&&(NMEA_mss[5]==65)&&(NMEA_mss[4]==71))//"$GPGGA" A 65 G 71
	  {
		  uint8_t igpgga=0;
		  //led_toggle(LED4);//TOOGLE SI ESTA PRENDIDO LO APAGO, SI ESTA APAGADO LO PRENDO
		  for(igpgga=0;igpgga<i_gpsbuff;igpgga++){
			  NMEA_GPGGA[igpgga]=NMEA_mss[igpgga];
		  }
		  controlGPS=1;
		  /*if((i_gpsbuff>45)&&(i_gpsbuff<89))
		  {
			controlGPS=1;
		  }*/
	  }
	}	
	
	(void)UART0_S1;		/* Clear reception flag mechanism*/
}
