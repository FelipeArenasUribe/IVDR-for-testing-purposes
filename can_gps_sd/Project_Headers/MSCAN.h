/*
 * MSCAN.h
 *
 *  Created on: Aug 6, 2016
 *      Author: julianecme
 */

#ifndef MSCAN_H_
#define MSCAN_H_

#define sizeCANbuff 512
#define sizeCANbuff_overflow sizeCANbuff-12
//#define mask_sizeCANbuff sizeCANbuff-1

#define velobd2msm 0
/* obd2 read velocity
 * vel 0 max
 * vel 1 10 mseg
 * vel 2 100 mseg
 */
#define modeoper   0
/* modo 0 sniffer+obd2
   modo 1 obd2
   modo 2 sniffer
   modo 3 id
   modo 4 id+obd2*/
#define SDoper	1
/*modo 0 off SD
  modo 1 on SD
 */
#define sizeSDfile	(2)*60

#define MSCANRX 22 //PTC6
#define MSCANTX 23 //PTC7
#define CANTRANSEIVER 16//PTG0
#define maskrxbuff_init 0xFF

void MSCAN_init(void);
void MSCAN_Tx(uint16_t ID,uint8_t DLC,uint32_t dataw1,uint32_t dataw0 );
//void conv32tobuff(uint32_t dato32,uint8_t numbytes);
void byteinbuff(uint8_t databyte);
void obd2_switch(uint8_t obd2msm);
void filluartbuff(uint16_t irdx);
void MSCAN_Rx_IRQHandler(void);

#endif /* MSCAN_H_ */
