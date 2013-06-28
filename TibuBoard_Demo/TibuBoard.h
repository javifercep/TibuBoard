/*
  ******************************************************************************
  * @file    TibuBoard.h
  * @author  Javier Fern�ndez Cepeda
  * @version V0.0.1
  * @date    27-June-2013
  * @brief   This file contains variable and functions declarations for TibuBoard.c.
  ******************************************************************************
*/


/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __TIBUBOARD_H
#define __TIBUBOARD_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx.h"
#include "stm32f4xx_conf.h"

 /* Exported define ------------------------------------------------------------*/

 typedef enum 
{
  LED1 = 0,
  LED2 = 1,
  LED3 = 2,
  LED4 = 3
} Led_TypeDef;

typedef enum
{
  USER_BUTTON1 = 0,
  USER_BUTTON3 = 1,
  USER_BUTTON4 = 2
} Button_TypeDef;

typedef struct
{

	void 		( *InitLED ) 		( Led_TypeDef ) ;
	void 		( *ToggleLED )		( Led_TypeDef );
	void 		( *LEDOn ) 			( Led_TypeDef ) ;
	void 		( *LEDOff )			( Led_TypeDef );
	void 		( *InitAllLED )		(void);
	void 		( *ToggleAllLED )	(void);
	void 		( *AllLEDOn )		(void);
	void 		( *AllLEDOff )		(void);
	void 		( *InitButton )		(Button_TypeDef);
	void 		( *ButtonInterrupt )(Button_TypeDef, void (*userFunc)(void));
	void 		( *InitAllButton )	(void);
	uint32_t 	( *GetStateButton )	(Button_TypeDef);

}TibuBoard;
 
 /* LEDx boards Interface */
 
 #define numLEDs						4
 
 #define LED1_PIN						GPIO_Pin_6
 #define LED1_GPIO_PORT					GPIOC
 #define LED1_GPIO_CLK					RCC_AHB1Periph_GPIOC
 
 #define LED2_PIN						GPIO_Pin_7
 #define LED2_GPIO_PORT					GPIOC
 #define LED2_GPIO_CLK					RCC_AHB1Periph_GPIOC
 
 #define LED3_PIN						GPIO_Pin_8
 #define LED3_GPIO_PORT					GPIOC
 #define LED3_GPIO_CLK					RCC_AHB1Periph_GPIOC
 
 #define LED4_PIN						GPIO_Pin_15
 #define LED4_GPIO_PORT					GPIOB
 #define LED4_GPIO_CLK					RCC_AHB1Periph_GPIOB


/* Buttonx boards Interface  */
#define numBUTTON                         3

/**
* @brief Wakeup push-button
*/
#define USER_BUTTON1_PIN                GPIO_Pin_2
#define USER_BUTTON1_GPIO_PORT          GPIOB
#define USER_BUTTON1_GPIO_CLK           RCC_AHB1Periph_GPIOB
#define USER_BUTTON1_EXTI_LINE          EXTI_Line2
#define USER_BUTTON1_EXTI_PORT_SOURCE   EXTI_PortSourceGPIOB
#define USER_BUTTON1_EXTI_PIN_SOURCE    EXTI_PinSource2
#define USER_BUTTON1_EXTI_IRQn          EXTI2_IRQn

#define USER_BUTTON3_PIN                GPIO_Pin_2
#define USER_BUTTON3_GPIO_PORT          GPIOA
#define USER_BUTTON3_GPIO_CLK           RCC_AHB1Periph_GPIOA
#define USER_BUTTON3_EXTI_LINE          EXTI_Line2
#define USER_BUTTON3_EXTI_PORT_SOURCE   EXTI_PortSourceGPIOA
#define USER_BUTTON3_EXTI_PIN_SOURCE    EXTI_PinSource2
#define USER_BUTTON3_EXTI_IRQn          EXTI2_IRQn

#define USER_BUTTON4_PIN                GPIO_Pin_4
#define USER_BUTTON4_GPIO_PORT          GPIOA
#define USER_BUTTON4_GPIO_CLK           RCC_AHB1Periph_GPIOA
#define USER_BUTTON4_EXTI_LINE          EXTI_Line4
#define USER_BUTTON4_EXTI_PORT_SOURCE   EXTI_PortSourceGPIOA
#define USER_BUTTON4_EXTI_PIN_SOURCE    EXTI_PinSource4
#define USER_BUTTON4_EXTI_IRQn          EXTI4_IRQn
 
 
 /* Exported types ------------------------------------------------------------*/

typedef void (*voidFuncPtr)(void);

 /* Exported constants --------------------------------------------------------*/

 /* Exported macro ------------------------------------------------------------*/
 /* Exported functions ------------------------------------------------------- */

/* LEDs functions*/
 void TibuBoard_InitLED(Led_TypeDef Led);
 void TibuBoard_LEDOn(Led_TypeDef Led);
 void TibuBoard_LEDOff(Led_TypeDef Led);
 void TibuBoard_LEDToggle(Led_TypeDef Led);
 void TibuBoard_InitAllLEDs(void);
 void TibuBoard_LEDOnAll(void);
 void TibuBoard_LEDOffAll(void);
 void TibuBoard_LEDToggleAll(void);

 /* Push Button Functions */
 void TibuBoard_InitPushButton(Button_TypeDef Button);
 void TibuBoard_attachButtonInterrupt(Button_TypeDef Button, void (*userFunc)(void));
 void TibuBoard_InitAllPushButton(void);
 uint32_t TibuBoard_GetStatePushButton(Button_TypeDef Button);

 /*Init Functions*/
 void InitTibuBoard(TibuBoard *Tibu);
 void SysTickConfig(void);

 /*Arduino functions*/
 void delay(uint32_t miliseconds);

 #ifdef __cplusplus
 }
 #endif

#endif /* __INITROUTINES_H */
