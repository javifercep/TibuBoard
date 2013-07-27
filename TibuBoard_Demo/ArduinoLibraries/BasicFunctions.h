/*
  ******************************************************************************
  * @file    BasicFunctions.h
  * @author  Javier Fernandez Cepeda
  * @version V0.0.1
  * @date    26-July-2013
  * @brief   This file contains the Arduino basic functions.
  ******************************************************************************
*/


/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __BASICFUNCTIONS_H
#define __BASICFUNCTIONS_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx.h"
#include "stm32f4xx_conf.h"

 /* Exported define ------------------------------------------------------------*/

typedef enum
{
  OUTPUT = 0,
  INPUT = 1,
  INPUT_PULLUP = 2,
} Mode_TypeDef;

typedef enum
{
  LOW = 0,
  HIGH = 1,
} Mode_OuputState;

typedef enum
{
  PIN3_TIM4CHANNEL = 3,
  PIN5_TIM4CHANNEL = 5,
  PIN6_TIM4CHANNEL = 6,
  PIN9_TIM4CHANNEL = 9,
} Pin_TIM4Channel;

/* Max Period PWM*/
#define MAXPWMPERIOD 65535

/*Number of ADCs Channels availables*/
#define numADC 6

/* Total expansion pin */
#define numPins 20


/*analog Pins mapping*/

#define A0		14
#define A1		15
#define A2		16
#define A3		17
#define A4		18
#define A5		19

 /* digital Pins boards Interface */

#define PIN0_PIN						GPIO_Pin_1
#define PIN0_GPIO_PORT					GPIOA
#define PIN0_GPIO_CLK					RCC_AHB1Periph_GPIOA
#define PIN0_GPIO_SOURCE				GPIO_PinSource1

#define PIN1_PIN						GPIO_Pin_0
#define PIN1_GPIO_PORT					GPIOA
#define PIN1_GPIO_CLK					RCC_AHB1Periph_GPIOA
#define PIN1_GPIO_SOURCE				GPIO_PinSource0

#define PIN2_PIN						GPIO_Pin_6
#define PIN2_GPIO_PORT					GPIOA
#define PIN2_GPIO_CLK					RCC_AHB1Periph_GPIOA
#define PIN2_GPIO_SOURCE				GPIO_PinSource6

#define PIN3_PIN						GPIO_Pin_6
#define PIN3_GPIO_PORT					GPIOB
#define PIN3_GPIO_CLK					RCC_AHB1Periph_GPIOB
#define PIN3_GPIO_SOURCE				GPIO_PinSource6


#define PIN4_PIN						GPIO_Pin_7
#define PIN4_GPIO_PORT					GPIOA
#define PIN4_GPIO_CLK					RCC_AHB1Periph_GPIOA
#define PIN4_GPIO_SOURCE				GPIO_PinSource7

#define PIN5_PIN						GPIO_Pin_7
#define PIN5_GPIO_PORT					GPIOB
#define PIN5_GPIO_CLK					RCC_AHB1Periph_GPIOB
#define PIN5_GPIO_SOURCE				GPIO_PinSource7

#define PIN6_PIN						GPIO_Pin_8
#define PIN6_GPIO_PORT					GPIOB
#define PIN6_GPIO_CLK					RCC_AHB1Periph_GPIOB
#define PIN6_GPIO_SOURCE				GPIO_PinSource8

#define PIN7_PIN						GPIO_Pin_4
#define PIN7_GPIO_PORT					GPIOC
#define PIN7_GPIO_CLK					RCC_AHB1Periph_GPIOC
#define PIN7_GPIO_SOURCE				GPIO_PinSource4

#define PIN8_PIN						GPIO_Pin_5
#define PIN8_GPIO_PORT					GPIOC
#define PIN8_GPIO_CLK					RCC_AHB1Periph_GPIOC
#define PIN8_GPIO_SOURCE				GPIO_PinSource5

#define PIN9_PIN						GPIO_Pin_9
#define PIN9_GPIO_PORT					GPIOB
#define PIN9_GPIO_CLK					RCC_AHB1Periph_GPIOB
#define PIN9_GPIO_SOURCE				GPIO_PinSource9

#define PIN10_PIN						GPIO_Pin_15
#define PIN10_GPIO_PORT					GPIOA
#define PIN10_GPIO_CLK					RCC_AHB1Periph_GPIOA
#define PIN10_GPIO_SOURCE				GPIO_PinSource15

#define PIN11_PIN						GPIO_Pin_12
#define PIN11_GPIO_PORT					GPIOC
#define PIN11_GPIO_CLK					RCC_AHB1Periph_GPIOC
#define PIN11_GPIO_SOURCE				GPIO_PinSource12

#define PIN12_PIN						GPIO_Pin_11
#define PIN12_GPIO_PORT					GPIOC
#define PIN12_GPIO_CLK					RCC_AHB1Periph_GPIOC
#define PIN12_GPIO_SOURCE				GPIO_PinSource11

#define PIN13_PIN						GPIO_Pin_10
#define PIN13_GPIO_PORT					GPIOC
#define PIN13_GPIO_CLK					RCC_AHB1Periph_GPIOC
#define PIN13_GPIO_SOURCE				GPIO_PinSource10

#define PINA0_PIN						GPIO_Pin_13
#define PINA0_GPIO_PORT					GPIOC
#define PINA0_GPIO_CLK					RCC_AHB1Periph_GPIOC
#define PINA0_GPIO_SOURCE				GPIO_PinSource13

#define PINA1_PIN						GPIO_Pin_14
#define PINA1_GPIO_PORT					GPIOC
#define PINA1_GPIO_CLK					RCC_AHB1Periph_GPIOC
#define PINA1_GPIO_SOURCE				GPIO_PinSource14

#define PINA2_PIN						GPIO_Pin_15
#define PINA2_GPIO_PORT					GPIOC
#define PINA2_GPIO_CLK					RCC_AHB1Periph_GPIOC
#define PINA2_GPIO_SOURCE				GPIO_PinSource15

#define PINA3_PIN						GPIO_Pin_1
#define PINA3_GPIO_PORT					GPIOC
#define PINA3_GPIO_CLK					RCC_AHB1Periph_GPIOC
#define PINA3_GPIO_SOURCE				GPIO_PinSource1

#define PINA4_PIN						GPIO_Pin_9
#define PINA4_GPIO_PORT					GPIOC
#define PINA4_GPIO_CLK					RCC_AHB1Periph_GPIOC
#define PINA4_GPIO_SOURCE				GPIO_PinSource9

#define PINA5_PIN						GPIO_Pin_8
#define PINA5_GPIO_PORT					GPIOA
#define PINA5_GPIO_CLK					RCC_AHB1Periph_GPIOA
#define PINA5_GPIO_SOURCE				GPIO_PinSource8


 /* Exported types ------------------------------------------------------------*/

 /* Exported constants --------------------------------------------------------*/

 /* Exported macro ------------------------------------------------------------*/
 /* Exported functions ------------------------------------------------------- */


/* Digital functions*/
 void pinMode(uint32_t pinNumber, Mode_TypeDef Mode);
 void digitalWrite(uint32_t pinNumber, Mode_OuputState State);
 uint32_t digitalRead(uint32_t pinNumber);
 void analogWrite(uint32_t pinNumber, uint32_t pwm);
 void Init_PWMPins();

 /* Analog Functions */
 void InitADC();
 uint16_t analogRead();

 /* Useful Functions*/
 uint16_t mapInt16(uint16_t value, uint16_t minInput, uint16_t maxInput,
		 	 	 	 	 uint16_t minOutput, uint16_t maxOutput);



 #ifdef __cplusplus
 }
 #endif

#endif /* __INITROUTINES_H */
