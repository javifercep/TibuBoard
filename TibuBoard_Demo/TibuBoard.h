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

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx.h"
#include "stm32f4xx_conf.h"


 /* Exported define ------------------------------------------------------------*/
 
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

class Tibuboard {

public:
	Tibuboard(void);
	~Tibuboard(void);
	void LEDOn(Led_TypeDef Led);
	void LEDOff(Led_TypeDef Led);
	void LEDToggle(Led_TypeDef Led);
	void LEDAllToggle(void);
	void LEDAllOn(void);
	void LEDAllOff(void);
	void ButtonInterrupt(Button_TypeDef button, void (*userFunc)(void));
	uint8_t GetStateButton(Button_TypeDef button);
};


 /* Exported constants --------------------------------------------------------*/

 /* Exported macro ------------------------------------------------------------*/
 /* Exported functions ------------------------------------------------------- */


 /*Init Functions*/
 //void InitTibuBoard(TibuBoard *Tibu);
 void SysTickConfig(void);

 /*Arduino functions*/
 void delay(uint32_t miliseconds);
 uint32_t millis(void);


#endif /* __INITROUTINES_H */
