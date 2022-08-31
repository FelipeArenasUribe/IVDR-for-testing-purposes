/*
 * PIT.c
 *
 *  Created on: Aug 5, 2016
 *      Author: julianecme
 */

//#include "derivative.h" /* include peripheral declarations */
#include <SKEAZ1284.h>
#include "Vectors_Config.h" 
#include "PIT.h"
#include "GPIO.h" // include peripheral declarations 
#include "MSCAN.h"

void PIT_init(void) {
	SIM_SCGC |= SIM_SCGC_PIT_MASK; /* Enable bus clock to PIT module */
	PIT_MCR = 0x0; /* Turn on PIT module, Freeze disabled */
	if(velobd2msm==0)
		PIT_LDVAL0 = (CLKbus/1) - 1; // PIT0: Load value to count 20M bus clocks 
	if(velobd2msm==1)
		PIT_LDVAL0 = (CLKbus/100) - 1; // PIT0: Load value to count 20M bus clocks 
	if(velobd2msm==2)
		PIT_LDVAL0 = (CLKbus/10) - 1; // PIT0: Load value to count 20M bus clocks 
	PIT_TCTRL0 |= PIT_TCTRL_TIE_MASK; /* Enable interrupt */
	PIT_TCTRL0 |= PIT_TCTRL_TEN_MASK; /* Enable (start) timer */
	
	PIT_LDVAL1 = (CLKbus*4) - 1; // PIT1: Load value to count 20M bus clocks 
	PIT_TCTRL1 |= PIT_TCTRL_TIE_MASK; // Enable interrupt
	PIT_TCTRL1 |= PIT_TCTRL_TEN_MASK; // Enable (start) timer
}

//uint32_t CAN_data_p=0x0;
//uint8_t  CAN_1=0x0,CAN_2=0x80;
extern uint8_t controlmsm;
void PIT_CH0_IRQHandler (void) {
	//led_toggle(LED1);
	
	if(velobd2msm==1){
		obd2_switch(controlmsm);
	}
	
	/*CAN_1++; CAN_2++;CAN_data_p++;
	byteinbuff(7);
	byteinbuff(CAN_2++);
	byteinbuff(44); //ASCII ,
	byteinbuff(CAN_1);
	byteinbuff(CAN_2);
	byteinbuff(CAN_1);
	byteinbuff(CAN_2);
	byteinbuff(CAN_1);
	byteinbuff(CAN_2);
	byteinbuff(CAN_1);
	byteinbuff(44); //ASCII ,
	byteinbuff(CAN_1++);
	byteinbuff(CAN_2++);	
	byteinbuff(13); //ASCII enter
	byteinbuff(10); //ASCII enter*/
	
	PIT_TFLG0 |= PIT_TFLG_TIF_MASK; // Clear PIT0 flag 
}

uint8_t timeoutSD=0, ant_timeoutSD=1;
void PIT_CH1_IRQHandler (void) {
	led_toggle(LED1);
	if((timeoutSD==ant_timeoutSD))//&&(SDoper==1))
	{
		led_on(LED1);
		while(1);
	}
	ant_timeoutSD=timeoutSD;
	PIT_TFLG1 |= PIT_TFLG_TIF_MASK; // Clear PIT1 flag 
}
