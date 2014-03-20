/*
  ******************************************************************************
  * @file    USBSerial.h
  * @author  Javier Fernandez Cepeda
  * @version V0.0.1
  * @date    06-August-2013
  * @brief   This file contains constants definitions which help users develop
  * 		 USB VCP applications.
  ******************************************************************************
*/

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __USBSERIAL_H
#define __USBSERIAL_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx.h"
#include "stm32f4xx_conf.h"
#include "usbd_cdc_vcp.h"
#include <stdio.h>
#include <string.h>

/* Exported define ------------------------------------------------------------*/
#define MAXSTRINGSIZE 255
#define SERIAL_BUFFER_LENGTH 1000
/* Exported types ------------------------------------------------------------*/
 typedef struct
 {

 	void 		( *begin	 ) 		( void );
 	uint8_t 	( *available )		( void );
 	void 		( *print ) 			( const char* );
 	void 		( *println )		( const char* );
 	uint8_t		( *read )			( void );
 	uint8_t*	( *readUntil )		( uint8_t );

 }USBSerial;

/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */

void USBSerial_begin(void);
uint8_t USBSerial_available(void);
void USBSerial_print(const char *s);
void USBSerial_println(const char *s);
uint8_t USBSerial_read(void);
uint8_t* USBSerial_readUntil(uint8_t n);

/*Init Functions*/
void InitUSBSerial(USBSerial *Serial);

#ifdef __cplusplus
}
#endif

#endif /* __USBSerial_H */
