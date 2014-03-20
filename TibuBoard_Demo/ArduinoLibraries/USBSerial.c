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


 /**
   * @brief   This functions initializes USB VCP
   * @param  None
   * @retval None
   */
 void USBSerial_begin(void)
 {
	 	Init_Container(&USB_DataReceived, SERIAL_BUFFER_LENGTH);
		USBD_Init(&USB_OTG_dev,USB_OTG_HS_CORE_ID,&USR_desc,&USBD_CDC_cb,&USR_cb);
 }

 /**
   * @brief  Check if there is an character available
   * @param  None.
   * @retval 1 if there is a character available, 0 otherwise.
   */
 uint8_t USBSerial_available(void)
 {
	 return numDatainContainer(&USB_DataReceived);
 }

 /**
   * @brief  Send a char array through USB VCP
   * @param  s: Char array to send.
   * @retval a character.
   */
 void USBSerial_print(const char *s)
 {
	 vcp_sendBytes((uint8_t *)s,strlen(s));
 }

 /**
   * @brief  Send a char array through USB VCP with \n
   * @param  s: Char array to send.
   * @retval a character.
   */
 void USBSerial_println(const char *s)
 {	 
	 char temp[MAXSTRINGSIZE];

	 strcpy(temp,s);
	 strcat(temp, "\n");
	 vcp_sendBytes((uint8_t *)temp, strlen(temp));
 }

 /**
   * @brief  return the character from USB buffer
   * @param  None.
   * @retval a character.
   */
 uint8_t USBSerial_read()
  {
	 if(ContainerisEmpty(&USB_DataReceived)==FC_EMPTY)
		 return 0;
	 else
		 return Read_Container(&USB_DataReceived);
  }



 /**
    * @brief  Read characters until receives character n.
    * @param  n: Char target.
    * @retval Pointer to data readed or Null.
    */
 uint8_t* USBSerial_readUntil(uint8_t n)
 {
	 uint8_t readed = 0;
	 uint8_t *s;
	 uint32_t ii = 0;

	 s = malloc(sizeof(uint8_t)*MAXSTRINGSIZE);
	 while(readed != n)
	 {
		 if(numDatainContainer(&USB_DataReceived) > 0)
		 {
			 readed = Read_Container(&USB_DataReceived);
			 s[ii++] = readed;
			 if(ii == MAXSTRINGSIZE)
				 return 0;
		 }

	 }
	 s[ii] = '\0';

	 return s;
 }



 /********************************************************************************************/
 /******************                INIT FUNCTIONS          **********************************/
 /********************************************************************************************/

 /**
   * @brief  Initialices USBSerial Structure.
   * @param  Serial: contains USBSerial Struct
   * @retval None
   */
 void InitUSBSerial(USBSerial *Serial)
 {
   Serial->begin 	 = USBSerial_begin;
   Serial->available = USBSerial_available;
   Serial->print	 = USBSerial_print;
   Serial->println 	 = USBSerial_println;
   Serial->read		 = USBSerial_read;
   Serial->readUntil = USBSerial_readUntil;
 }
