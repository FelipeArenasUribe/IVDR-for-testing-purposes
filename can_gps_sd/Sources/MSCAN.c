/*
 * MSCAN.c
 *
 *  Created on: Aug 6, 2016
 *      Author: julianecme
 */

//#include "derivative.h" // include peripheral declarations
#include <SKEAZ1284.h>
#include "MSCAN.h"
#include "GPIO.h"
#include "mcu.h"

void MSCAN_init(void){
	CONFIG_PIN_AS_GPIO(PORT_G,CANTRANSEIVER,OUTPUT); //! MC33901 STB, Mapped from GPIOB16
	OUTPUT_CLEAR(PORT_G,CANTRANSEIVER);				//PIN STB ACTIVA CON 0
	SIM_PINSEL1 &= ~SIM_PINSEL1_MSCANPS_MASK; // SIM_PINSEL1: MSCANPS=0; PTC6 PTC7
	CONFIG_PIN_AS_GPIO(PORT_C,MSCANRX,INPUT); /* Configure (PTC6) as an intput RX*/
	CONFIG_PIN_AS_GPIO(PORT_C,MSCANTX,OUTPUT); /* Configure (PTC7) as an output TX*/
	
	SIM_SCGC |=  SIM_SCGC_MSCAN_MASK;		// Enable bus clock iN MSCAN
	
	MSCAN_CANCTL1 |= MSCAN_CANCTL1_CANE_MASK;           // Enable CAN mode
	MSCAN_CANCTL1 |= MSCAN_CANCTL1_CLKSRC_MASK;
	MSCAN_CANCTL0 |= MSCAN_CANCTL0_INITRQ_MASK;         // Enable INIT mode
	while ((MSCAN_CANCTL1&MSCAN_CANCTL1_INITAK_MASK)!=1);                    // wait for initialization mode
	
	MSCAN_CANIDAR0=maskrxbuff_init;
	MSCAN_CANIDAR1=maskrxbuff_init;
	MSCAN_CANIDAR2=maskrxbuff_init;
	MSCAN_CANIDAR3=maskrxbuff_init;
	MSCAN_CANIDAR4=maskrxbuff_init;
	MSCAN_CANIDAR5=maskrxbuff_init;
	MSCAN_CANIDAR6=maskrxbuff_init;
	MSCAN_CANIDAR7=maskrxbuff_init;
	
	MSCAN_CANIDMR0=maskrxbuff_init;
	MSCAN_CANIDMR1=maskrxbuff_init;
	MSCAN_CANIDMR2=maskrxbuff_init;
	MSCAN_CANIDMR3=maskrxbuff_init;
	MSCAN_CANIDMR4=maskrxbuff_init;
	MSCAN_CANIDMR5=maskrxbuff_init;
	MSCAN_CANIDMR6=maskrxbuff_init;
	MSCAN_CANIDMR7=maskrxbuff_init;
	
	
	MSCAN_CANBTR0 = 0x01;//0x01;       //PRESCALADOR CLKBUS/2 10MHz  SI QUIERO 100KHz PREESCALADOR DEBE SER 0x09 CLKBUS/10 2MHZ
	MSCAN_CANBTR1 = 0xDC;//0xDC;//0xBE;		//3E SG1= 15, SG2= 4 SG1+SG2+1=20   10MHz/20=500 KHz) SG2 20-25% TIME QUANTA
									//BE 1 Three samples per bit. In this case, PHASE_SEG1 must be at least 2 time quanta (Tq).
	MSCAN_CANBTR1 &= ~MSCAN_CANBTR1_SAMP_MASK;
	
	MSCAN_CANCTL1 &= ~MSCAN_CANCTL1_LISTEN_MASK;
	MSCAN_CANCTL1 &= ~MSCAN_CANCTL1_LOOPB_MASK;
	MSCAN_CANCTL0 &= ~MSCAN_CANCTL0_CSWAI_MASK;
	MSCAN_CANCTL1 &= ~MSCAN_CANCTL1_WUPM_MASK;
	MSCAN_CANCTL1 &= ~MSCAN_CANCTL1_BORM_MASK;
	MSCAN_CANIDAC = MSCAN_CANIDAC_IDAM(0);//OJO
	
	MSCAN_CANCTL0 &= ~MSCAN_CANCTL0_INITRQ_MASK;         // Disable INIT mode 
	while ((MSCAN_CANCTL1&MSCAN_CANCTL1_INITAK_MASK)!=0); 
	
	MSCAN_CANRIER=1; //|= MSCAN_CANRIER_RXFIE_MASK ;//0x01; //receive interrupt enabled
	MSCAN_CANTIER=0;
	
	MSCAN_CANCTL0 |= MSCAN_CANCTL0_TIME_MASK;
	MSCAN_CANCTL0 &= ~MSCAN_CANCTL0_WUPE_MASK;
	
	MSCAN_CANCTL1 |= MSCAN_CANCTL1_CANE_MASK;
	MSCAN_CANRFLG |= MSCAN_CANRFLG_RXF_MASK;//0x01; //receive interrupt enabled
}

void MSCAN_Tx(uint16_t ID,uint8_t DLC,uint32_t dataw1,uint32_t dataw0){
	uint16_t can_id=0;
	uint8_t txcanbuffer=0;	
	DisableInterrupts; 
	txcanbuffer = MSCAN_CANTFLG & MSCAN_CANTFLG_TXE_MASK; // read transmit flag
	if(txcanbuffer!=0){		
		led_off(LED3); //PRENDER UN LED
		/************* select one among 3 buffers *************/
		MSCAN_CANTBSEL = txcanbuffer; /* write the value back to Can select register */

		can_id=ID>>3;
		can_id &= 0xFF;
		MSCAN_TSIDR0  = (uint8_t)can_id;//0xFB;    frame id// standard frame has 2 registers involved
		can_id=ID <<5;
		can_id &= 0xFF;
		MSCAN_TEIDR1 = (uint8_t)can_id; //7DF OBD2READ OJO EREROR EN LOS REGISTROS MSCAN_TSIDR1=
		MSCAN_TEIDR1 &= ~MSCAN_TEIDR1_TEIDE_MASK;
		MSCAN_TEIDR1 &= ~MSCAN_TSIDR1_TSIDE_MASK;
		MSCAN_TEIDR2 = 0;
		MSCAN_TEIDR3 = 0;

		MSCAN_TEDSR0 = (uint8_t) ((dataw1>>24)&0xFF);
		MSCAN_TEDSR1 = (uint8_t) ((dataw1>>16)&0xFF);
		MSCAN_TEDSR2 = (uint8_t) ((dataw1>>8)&0xFF);
		MSCAN_TEDSR3 = (uint8_t) dataw1&0xFF;
		MSCAN_TEDSR4 = (uint8_t) ((dataw0>>24)&0xFF);
		MSCAN_TEDSR5 = (uint8_t) ((dataw0>>16)&0xFF);
		MSCAN_TEDSR6 = (uint8_t) ((dataw0>>8)&0xFF);
		MSCAN_TEDSR7 = (uint8_t) dataw0&0xFF;
		
		MSCAN_TDLR = DLC;         //Data frame length 
	
		MSCAN_TBPR = 1;              // local priority 
						
		txcanbuffer = MSCAN_CANTBSEL&0x07;
		MSCAN_CANTFLG=txcanbuffer;
	}
	else{
		led_on(LED3); //PRENDER UN LED
	}
	EnableInterrupts;
}
void MSCAN_Tx_IRQHandler(void){	
	uint8_t intx=0;
	intx++;
}

uint8_t controlmsm=0;
void MSCAN_Rx_IRQHandler(void){	
//	uint32_t *p_rx;
	uint16_t idrx;
	uint8_t temp8_rx=0;
	
	/**p_rx=&MSCAN_RSIDR0;
	idrx=&p_rx;*/
	
	idrx=MSCAN_RSIDR0;
	idrx<<= 3;
	idrx &= 0x7F8;
	temp8_rx=MSCAN_RSIDR1;
	temp8_rx >>= 5;
	temp8_rx &= 0x07;
	idrx+=temp8_rx;
	
	switch(modeoper){
		case(0):
			filluartbuff(idrx);
			if (idrx==0x7E8){
					controlmsm++;
					if(controlmsm==6){ //9número de parámetros del obd2
						controlmsm=0;
					}
					if(velobd2msm==0){
						obd2_switch(controlmsm);
					}
			}
			break;
		case(1):
			if (idrx==0x7E8){
					filluartbuff(idrx);
					controlmsm++;
					if(controlmsm==6){ //9número de parámetros del obd2
						controlmsm=0;
					}
					if(velobd2msm==0){
						obd2_switch(controlmsm);
					}
			}
			break;
		case(2):
			filluartbuff(idrx);
			break;
		case(3):
			if (idrx==0x201){
				filluartbuff(idrx);
			}
			break;
		case(4):
			if (idrx==0x201){
				filluartbuff(idrx);
			}
			if (idrx==0x7E8){
					filluartbuff(idrx);
					controlmsm++;
					if(controlmsm==6){ //9número de parámetros del obd2
						controlmsm=0;
					}
					if(velobd2msm==0){
						obd2_switch(controlmsm);
					}
			}
			break;
	}
	MSCAN_CANRFLG |= MSCAN_CANRFLG_RXF_MASK;//0x01; //receive interrupt enabled
}

void filluartbuff(uint16_t id_rx){
	    uint16_t temp_fub=0;
		//14
		/*temp8_rx=MSCAN_RSIDR0;
		temp8_rx >>= 5;
		temp8_rx &= 0x07;
		byteinbuff(temp8_rx);
		temp8_rx=id_rx&0xFF;
		byteinbuff(temp8_rx);*/
	    temp_fub=id_rx;
	    temp_fub>>= 8;
	    temp_fub&=0x07;
	    byteinbuff((uint8_t)temp_fub);
	    temp_fub=id_rx&0xFF;
	    byteinbuff((uint8_t)temp_fub);
		//byteinbuff(MSCAN_RSIDR0);
		//byteinbuff(MSCAN_RSIDR1);
		byteinbuff(44); //ASCII ,
		byteinbuff(MSCAN_REDSR0);
		byteinbuff(MSCAN_REDSR1);
		byteinbuff(MSCAN_REDSR2);
		byteinbuff(MSCAN_REDSR3);
		byteinbuff(MSCAN_REDSR4);
		byteinbuff(MSCAN_REDSR5);
		byteinbuff(MSCAN_REDSR6);
		byteinbuff(MSCAN_REDSR7);
		byteinbuff(44); //ASCII ,
		byteinbuff(MSCAN_RTSRH);
		byteinbuff(MSCAN_RTSRL);	
		byteinbuff(13); //ASCII enter
		byteinbuff(10); //ASCII enter
}

uint16_t i_canbuff=0;
uint8_t CANbuff_tx[sizeCANbuff];
void byteinbuff(uint8_t databyte){
	CANbuff_tx[i_canbuff]=databyte;
	i_canbuff++;
	if(i_canbuff==sizeCANbuff)
		i_canbuff=0;
}

void obd2_switch(uint8_t obd2msm){
	switch (obd2msm){
			case 0:
				MSCAN_Tx(2015, 8,0x02010400, 0); //Escribo al 7DF 04 Carga
				break;
			case 1:
				MSCAN_Tx(2015, 8,0x02010B00, 0); //Escribo al 7DF 0B MAP
				break;
			case 2:
				MSCAN_Tx(2015, 8,0x02010C00, 0); //Escribo al 7DF 0C RPM
				break;
			case 3:
				MSCAN_Tx(2015, 8,0x02010D00, 0); //Escribo al 7DF 0D V
				break;
			case 4:
				MSCAN_Tx(2015, 8,0x02011100, 0); //Escribo al 7DF 11 TPS
				break;
			case 5:
				MSCAN_Tx(2015, 8,0x02014900, 0); //Escribo al 7DF 49 APP
				break;
		}	
}
