/*
 * mcu.h
 *
 *  Created on: Aug 5, 2016
 *      Author: julianecme
 */

#ifndef MCU_H_
#define MCU_H_

#define CLKbus 20000000
#define EnableInterrupts __asm("CPSIE i")
#define DisableInterrupts __asm("CPSID i")

void clks_init_FEE_40MHz(void);

void IRQs_init (IRQInterruptIndex IRQn);
void NVIC_SetPriority(IRQInterruptIndex IRQn, uint32_t priority);
void NVIC_ClearPendingIRQ(IRQInterruptIndex IRQn);
void NVIC_DisableIRQ(IRQInterruptIndex IRQn);
void NVIC_EnableIRQ(IRQInterruptIndex IRQn);

#endif /* MCU_H_ */
