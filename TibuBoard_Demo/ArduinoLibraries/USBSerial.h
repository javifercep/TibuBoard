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

#include "Stream.h"

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx.h"
#include "stm32f4xx_conf.h"
#include "usbd_cdc_vcp.h"
#include <stdio.h>
#include <string.h>
#include <inttypes.h>

/* Exported define ------------------------------------------------------------*/
#define MAXSTRINGSIZE 255
#define SERIAL_BUFFER_LENGTH 1000
/* Exported types ------------------------------------------------------------*/

 class HardwareSerial : public Stream
 {

   public:
     HardwareSerial();
     void begin(unsigned long);
     void begin(unsigned long, uint8_t);
     void end();
     virtual int available(void);
     virtual int peek(void);
     virtual int read(void);
     virtual void flush(void);
     virtual size_t write(uint8_t);
     inline size_t write(unsigned long n) { return write((uint8_t)n); }
     inline size_t write(long n) { return write((uint8_t)n); }
     inline size_t write(unsigned int n) { return write((uint8_t)n); }
     inline size_t write(int n) { return write((uint8_t)n); }
     using Print::write; // pull in write(str) and write(buf, size) from Print
     operator bool();
 };

 extern HardwareSerial Serial;

 extern void serialEventRun(void) __attribute__((weak));
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */

/*void USBSerial_begin(void);
uint8_t USBSerial_available(void);
void USBSerial_print(const char *s);
void USBSerial_println(const char *s);
uint8_t USBSerial_read(void);
uint8_t* USBSerial_readUntil(uint8_t n);*/

/*Init Functions*/
/*void InitUSBSerial(USBSerial *Serial);*/

#ifdef __cplusplus
}
#endif

#endif /* __USBSerial_H */
