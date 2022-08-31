/*
 * PIT.h
 *
 *  Created on: Aug 5, 2016
 *      Author: julianecme
 */

#ifndef PIT_H_
#define PIT_H_

void PIT_init(void);
void PIT_CH0_IRQHandler (void);
void PIT_CH1_IRQHandler (void);

#endif /* PIT_H_ */
