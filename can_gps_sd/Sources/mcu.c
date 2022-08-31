/*
 * mcu.c
 *
 *  Created on: Aug 5, 2016
 *      Author: julianecme
 */
//#include "derivative.h"
#include <SKEAZ1284.h>
#include "mcu.h"

void clks_init_FEE_40MHz(void) { /* FLL Enabled with External clock */
	OSC_CR = 0x96; 	/* High range & gain; select osc */
					/* OSCEN =1 ; OSC module enabled */
					/* OSCSTEN = 0; OSC clock disabled in stop mode */
					/* OSCOS = 1; OSC clock source is selected */
					/* RANGE = 1; High freq range of 4-24 MHz */
					/* HGO = 1; High-gain mode */
	while ((OSC_CR & OSC_CR_OSCINIT_MASK) == 0); /* Wait until oscillator is ready*/
	ICS_C2 = 0x20; 	/* BDIV div by 2; use default until dividers configured*/
					/* LP = 0; FLL is not disabled in bypass mode */
	ICS_C1 = 0x18; 	/* 8 Mhz ext ref clk/256 is source to FLL */
					/* CLKS = 0; Output of FLL is selected (default) */
					/* RDIV = 3; ref clk prescaled by 256 with RANGE=0 */
					/* IREFS = 0; ext clk source selected */
					/* IRCLKEN = 0; ICSIRCLK inactive */
					/* IREFSTEN = 0; Int ref clk disabled in Stop mode */
	while ((ICS_S & ICS_S_IREFST_MASK) == 1); /* Wait for external source selected */
	while ((ICS_S & ICS_S_LOCK_MASK) == 0); /* Wait for FLL to lock */
	SIM_CLKDIV = 0x01100000; /* OUTDIV1 = 0; Core/sysclk is ICSOUTCLK div by 1 */
							/* OUTDIV2 = 1 bus/flash is OUTDIV1/2 */
							/* OUTDIV3 = 1; FTMs, PWT is ICSOUTCLK div by 2 */
	ICS_C2 = 0x00; /* BDIV div by 1- increases bus/flash freq */
}

void IRQs_init (IRQInterruptIndex IRQn) {
	NVIC_ClearPendingIRQ(IRQn); /* Clear any Pending IRQ for all PIT ch0 (#22) IT_CH0_IRQn*/
	NVIC_EnableIRQ(IRQn); /* Set Enable IRQ for PIT_CH0 */
}

void NVIC_ClearPendingIRQ(uint8_t IRQn)
{
	IRQn= IRQn-16;
	NVIC_ICPR |= 1 <<(IRQn%32); 
}
void NVIC_DisableIRQ(uint8_t IRQn)
{
	IRQn= IRQn-16;
	NVIC_ICER |= 1 <<(IRQn%32);
}
void NVIC_EnableIRQ(uint8_t IRQn)
{
	IRQn= IRQn-16;
	NVIC_ISER |= 1 <<(IRQn%32);
}


