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
__IO char Command[MAXSTRINGSIZE];
__IO uint8_t len=0;

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
		USBD_Init(&USB_OTG_dev,USB_OTG_HS_CORE_ID,&USR_desc,&USBD_CDC_cb,&USR_cb);
 }

 /**
   * @brief  Check if there is an character available
   * @param  None.
   * @retval 1 if there is a character available, 0 otherwise.
   */
 uint8_t USBSerial_available(void)
 {
	 return usb_cdc_kbhit();
 }

 /**
   * @brief  Send a char array through USB VCP
   * @param  s: Char array to send.
   * @retval a character.
   */
 void USBSerial_print(char *s)
 {
	 usb_cdc_printf(s);
 }

 /**
   * @brief  Send a char array through USB VCP with \n
   * @param  s: Char array to send.
   * @retval a character.
   */
 void USBSerial_println(char *s)
 {	 
	 usb_cdc_printf(s);
	 usb_cdc_printf("\n");
 }

 /**
   * @brief  return the character from USB buffer
   * @param  None.
   * @retval a character.
   */
 uint8_t USBSerial_read()
  {
	  return usb_cdc_getc();
  }



 /**
    * @brief  Read characters until receives character n.
    * 		  You should use USBSerial_StringRead() after
    * 		  this function. Example
    * 		  if(USBSerial_ReadUntil('\n')
    * 		  {
    * 		  	USBSerial_StringRead(&s);
    * 		  }
    * @param  n: Char target.
    * @retval 0 if not read char target
    * 		  1 if read char target
    * 		  2 if Char array exceeds MAXSTRINGSIZE.
    */
 uint8_t USBSerial_readUntil(char n)
 {
	 uint8_t ret=0;

	 if (usb_cdc_kbhit()>0)
	 {
		 Command[len]=usb_cdc_getc();
		 if(Command[len]==n)
			 ret=0x01;
		 else
		 {
			 len++;
			 if(len==256)
				 ret=0x02;
		 }

	 }

	 return ret;
 }

 /**
    * @brief  Return read characters.
    * 		  Example
    * 		  if(USBSerial_ReadUntil('\n')
    * 		  {
    * 		  	USBSerial_StringRead(&s);
    * 		  }
    * @param  s: Char buffer.
    * @retval None
    */
 void USBSerial_StringRead(char *s)
 {
	 uint8_t aux=0;
	 while(aux<=len)
	 {
		 s[aux]=Command[aux];
		 aux++;
	 }
	 len=0;

 }

 /**
     * @brief  Check if the strings are equals
     * @param  in: String 1 to compare. it has to finish with /n
     * @param  tocomp: String 2 to compare.
     * @retval 0x01 if are equals, 0x00 otherwise.
     */
 uint8_t receivedDataEquals(char *in, char *tocomp)
 {
	 uint8_t ret = 0x00;
	 uint8_t count = 0;

	 while(in[count]!='\n')
	 {
		 if(in[count]==tocomp[count])
			 count++;
		 else
			 break;
	 }

	 if(in[count]=='\n')
		 ret=0x01;

	 return ret;

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
 }
