/* ###################################################################
**     Filename    : main.c
**     Project     : can_gps_sd
**     Processor   : SKEAZ128MLK4
**     Version     : Driver 01.01
**     Compiler    : GNU C Compiler
**     Date/Time   : 2016-09-01, 21:10, # CodeGen: 0
**     Abstract    :
**         Main module.
**         This module contains user's application code.
**     Settings    :
**     Contents    :
**         No public methods
**
** ###################################################################*/
/*!
** @file main.c
** @version 01.01
** @brief
**         Main module.
**         This module contains user's application code.
*/         
/*!
**  @addtogroup main_module main module documentation
**  @{
*/         
/* MODULE main */


/* Including needed modules to compile this module/procedure */
#include "Cpu.h"
#include "Events.h"
#include "SM1.h"
#include "FAT1.h"
#include "SD1.h"
#include "SS1.h"
#include "TmDt1.h"
#include "UTIL1.h"
#include "WAIT1.h"
#include "TMOUT1.h"
#include "CS1.h"
#include "KSDK1.h"
/* Including shared modules, which are used for whole project */
#include "PE_Types.h"
#include "PE_Error.h"
#include "PE_Const.h"
#include "IO_Map.h"
#include "PDD_Includes.h"
#include "Init_Config.h"


/* User includes (#include below this line is not maintained by Processor Expert) */
#include "mcu.h"
#include "GPIO.h"
#include "PIT.h"
#include "UART.h"
#include "MSCAN.h"

static FAT1_FATFS fileSystemObject;
static FIL fp;
static uint8_t name_txt[]="./test00.txt";
UINT bw;

extern uint8_t controlGPS;
extern uint8_t  NMEA_GPGGA[100];
extern uint8_t CANbuff_tx[sizeCANbuff];
extern uint16_t i_canbuff;
uint16_t i_canbuff_tx=0, err_overbuff;
uint8_t k_gps_tx=0;
uint16_t controlSD=0;
extern uint8_t timeoutSD;
extern uint8_t ant_timeoutSD;
uint8_t CANbuff_SD[sizeCANbuff];


/*lint -save  -e970 Disable MISRA rule (6.3) checking. */
int main(void)
/*lint -restore Enable MISRA rule (6.3) checking. */
{
  /* Write your local variable definition here */
	
	uint8_t name_count=0;
	uint8_t error_SD=0;

  /*** Processor Expert internal initialization. DON'T REMOVE THIS CODE!!! ***/
	PE_low_level_init();
  /*** End of Processor Expert internal initialization.                    ***/
	
	
  
  /* Write your code here */
  /* For example: for(;;) { } */
  	DisableInterrupts; 
  	
  	led_init();
  	sw_init();
  	
  	PIT_init();
  	IRQs_init (INT_PIT_CH0);
  	IRQs_init (INT_PIT_CH1);
  	
  	UART0_Init();
  	IRQs_init (INT_UART0);
  	UART2_Init();
  	
  	MSCAN_init();
  	IRQs_init (INT_MSCAN_RX);

  	EnableInterrupts;
  	
  	if(SDoper==1){
  		name_count=0;
  		timeoutSD++;
		error_SD=FAT1_Init();
		timeoutSD++;
		if(error_SD==FR_OK)
			error_SD=FAT1_mount(&fileSystemObject, (const TCHAR*)"0", 1);
		if(error_SD==FR_OK){
			do{
				timeoutSD++;
				name_txt[6]=(name_count/10)+48;
				name_txt[7]=(name_count%10)+48;
				error_SD=FAT1_open(&fp, name_txt, FA_CREATE_NEW);
				name_count++;
			}while(error_SD==FR_EXIST);
		}
		if(error_SD==FR_OK)
			error_SD=FAT1_open(&fp, name_txt, FA_OPEN_ALWAYS|FA_WRITE); 
		if(error_SD!=FR_OK)
			led_on(LED4);
  	}
  		
	if((velobd2msm==0)&&(modeoper<2)){
		obd2_switch(0);
	}
	
  	while(1) {	
  		
  		if (controlGPS==1){
  			uint8_t temp=0;
  			while(NMEA_GPGGA[k_gps_tx]!=13){
  				Uart_SendChar(2, NMEA_GPGGA[k_gps_tx]);
  				k_gps_tx++;
  			}
  			timeoutSD++;
  			if(SDoper==1){
  				if (timeoutSD==255){
  					timeoutSD=0;
  					ant_timeoutSD=1;
  				}
  				if(error_SD==FR_OK)
					error_SD=FAT1_lseek(&fp, fp.fsize);
				if(error_SD==FR_OK)
				{
					error_SD=FAT1_write(&fp, NMEA_GPGGA,k_gps_tx+2, &bw);
					led_toggle(LED4);
					controlSD++;
				}
				if(error_SD!=FR_OK)
					led_on(LED4);
  			}
  			temp=15-((k_gps_tx+1)%16);
  			while(temp!=0){
  				Uart_SendChar(2, 0);
  				temp--;
  			}
  			Uart_SendChar(2, 13);
  			Uart_SendChar(2, 10);
  			k_gps_tx=0;
  			controlGPS=0;
  		}
  		else{
  			err_overbuff=0;
  			err_overbuff=i_canbuff-i_canbuff_tx;
  			err_overbuff=err_overbuff&0x1FF;
  			if(err_overbuff>(sizeCANbuff_overflow)){
  				led_on(LED3); //PRENDER UN LED
  				while(1);
  			}
  			while(i_canbuff_tx!=i_canbuff){
  				Uart_SendChar(2, CANbuff_tx[i_canbuff_tx]);
  				CANbuff_SD[i_canbuff_tx]=CANbuff_tx[i_canbuff_tx];
  				i_canbuff_tx++;
  				
  				if((SDoper==1)&&(i_canbuff_tx==sizeCANbuff)){
					if(error_SD==FR_OK)
						error_SD=FAT1_lseek(&fp, fp.fsize);
					if(error_SD==FR_OK)
						error_SD=FAT1_write(&fp, CANbuff_SD,sizeCANbuff, &bw);//ojo puede sacar error
					if(error_SD!=FR_OK)
						led_on(LED4);
				}
  				
  				if(i_canbuff_tx==sizeCANbuff){
  					timeoutSD++;
  					i_canbuff_tx=0;
   				}
  					
  			}
  			if((controlSD==sizeSDfile)&&(SDoper==1)){ //si sd activa y # de segundos por archivo, vcrea un nuevo archivo
  				if(error_SD==FR_OK)
  					error_SD=FAT1_close(&fp);
  				if(error_SD==FR_OK){
  					do{
  						
						name_txt[6]=(name_count/10)+48;
						name_txt[7]=(name_count%10)+48;
						error_SD=FAT1_open(&fp, name_txt, FA_CREATE_NEW);
						name_count++;
					}while(error_SD==FR_EXIST); //crea una rchivo consecutivo
				}
				if(error_SD==FR_OK)
					error_SD=FAT1_open(&fp, name_txt, FA_OPEN_ALWAYS|FA_WRITE); //dejo abierto el archivo para escribir
				if(error_SD!=FR_OK)
					led_on(LED4);
  				controlSD=0;
  				if (name_count==100)
  				{
  					led_on(LED4	);
  					DisableInterrupts;
  					while(1);
  				}
  			}
  		}
  		if((sw_pushed(SW1)&&(SDoper==1)))
  		{
  			led_on(LED4);
  			if(error_SD==FR_OK)
				error_SD=FAT1_close(&fp);
  			DisableInterrupts;
			while(1);
  		}
  	}
  
  /*** Don't write any code pass this line, or it will be deleted during code generation. ***/
  /*** RTOS startup code. Macro PEX_RTOS_START is defined by the RTOS component. DON'T MODIFY THIS CODE!!! ***/
  #ifdef PEX_RTOS_START
    PEX_RTOS_START();                  /* Startup of the selected RTOS. Macro is defined by the RTOS component. */
  #endif
  /*** End of RTOS startup code.  ***/
  /*** Processor Expert end of main routine. DON'T MODIFY THIS CODE!!! ***/
  for(;;){}
  /*** Processor Expert end of main routine. DON'T WRITE CODE BELOW!!! ***/
} /*** End of main routine. DO NOT MODIFY THIS TEXT!!! ***/

/* END main */
/*!
** @}
*/
/*
** ###################################################################
**
**     This file was created by Processor Expert 10.3 [05.09]
**     for the Freescale Kinetis series of microcontrollers.
**
** ###################################################################
*/

