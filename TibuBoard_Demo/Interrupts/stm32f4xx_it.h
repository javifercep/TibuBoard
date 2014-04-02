/*
  ******************************************************************************
  * @file    stm32f4xx_it.h
  * @author  Javier Fern�ndez Cepeda
  * @version V0.0.1
  * @date    12-April-2013
  * @brief   Main Interrupt Service Routines.
  *         This file provides template for all exceptions handler and
  *         peripherals interrupt service routine.
  ******************************************************************************
*/

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __STM32F4xx_IT_H
#define __STM32F4xx_IT_H

#include "TibuBoard.h"

#ifdef __cplusplus
 extern "C" {
#endif 

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx.h"
#include "stm32f4xx_conf.h"
#include "usb_core.h"
#include "usbd_core.h"
#include "usbd_cdc_core.h"
#include "usb_dcd_int.h"

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */

void NMI_Handler(void); //not used
void HardFault_Handler(void); //not used
void MemManage_Handler(void); //not used
void BusFault_Handler(void); //not used
void UsageFault_Handler(void); //not used
void SVC_Handler(void); //not used
void DebugMon_Handler(void); //not used
void PendSV_Handler(void); //not used
void SysTick_Handler(void);
void EXTI0_IRQHandler(void);
void EXTI2_IRQHandler(void);
void EXTI4_IRQHandler(void);
void OTG_HS_WKUP_IRQHandler(void);
void OTG_HS_IRQHandler(void);
void OTG_HS_EP1_IN_IRQHandler(void);
void OTG_HS_EP1_OUT_IRQHandler(void);



#ifdef __cplusplus
}
#endif

#endif /* __STM32F4xx_IT_H */
