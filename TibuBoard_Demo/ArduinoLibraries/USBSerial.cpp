/*
  ******************************************************************************
  * @file    SPIAPI.c
  * @author  Javier Fernandez Cepeda
  * @version V0.0.1
  * @date    06-August-2013
  * @brief   This file contains functions descriptions which help users develop
  * 		 USB VCP apps.
  ******************************************************************************
*/


/*
  HardwareSerial.cpp - Hardware serial library for Wiring
  Copyright (c) 2006 Nicholas Zambetti.  All right reserved.

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA

  Modified 23 November 2006 by David A. Mellis
  Modified 28 September 2010 by Mark Sproul
  Modified 14 August 2012 by Alarus
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <inttypes.h>
#include "ArduinoStyle.h"
#include "wiring_private.h"

// this next line disables the entire HardwareSerial.cpp,
// this is so I can support Attiny series and any other chip without a uart

/* Includes ------------------------------------------------------------------*/
#include "USBSerial.h"


/* Private typedef -----------------------------------------------------------*/

/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/

 __IO FrameContainer USB_DataReceived;
__ALIGN_BEGIN USB_OTG_CORE_HANDLE  USB_OTG_dev __ALIGN_END;

/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

void serialEvent() __attribute__((weak));
void serialEvent() {}

#define serialEvent_implemented


void serialEventRun(void)
{
#ifdef serialEvent_implemented
if (Serial.available()) serialEvent();
#endif
}

// Constructors ////////////////////////////////////////////////////////////////

HardwareSerial::HardwareSerial()
{
	Init_Container(&USB_DataReceived, SERIAL_BUFFER_LENGTH);
}

HardwareSerial::~HardwareSerial()
{
	Free_Container(&USB_DataReceived);
}

// Public Methods //////////////////////////////////////////////////////////////

void HardwareSerial::begin(unsigned long baud)
{
	/*TODO check how to change transmition speed*/
	USBD_Init(&USB_OTG_dev,USB_OTG_HS_CORE_ID,&USR_desc,&USBD_CDC_cb,&USR_cb);
}

void HardwareSerial::begin(unsigned long baud, uint8_t config)
{
  /*TODO*/
}

void HardwareSerial::end()
{
	USBD_DeInit(&USB_OTG_dev);
}

int HardwareSerial::available(void)
{
	 return numDatainContainer(&USB_DataReceived);
}

int HardwareSerial::peek(void)
{
  /*TODO*/
	return 0;
}

int HardwareSerial::read(void)
{
  // if the head isn't ahead of the tail, we don't have any characters
	if(ContainerisEmpty(&USB_DataReceived)==FC_EMPTY)
			 return 0;
		 else
			 return Read_Container(&USB_DataReceived);
}

void HardwareSerial::flush()
{
	while(ContainerisEmpty(&USB_DataReceived)!=FC_EMPTY)
	{
		Read_Container(&USB_DataReceived);
	}
}

size_t HardwareSerial::write(uint8_t c)
{
	vcp_sendBytes(&c,1);

  return 1;
}

HardwareSerial::operator bool() {
	return true;
}

HardwareSerial Serial;





