/*
  ******************************************************************************
  * @file    TibuBoard.c
  * @author  Javier Fern�ndez Cepeda
  * @version V0.0.1
  * @date    27-June-2013
  * @brief   This file contains functions descriptions which initialize some chip
  * 		 peripherals.
  ******************************************************************************
*/

/* Includes ------------------------------------------------------------------*/
#include "TibuBoard.h"
#include "InterruptManager.h"

/* Private typedef -----------------------------------------------------------*/


/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/

extern __IO uint32_t Counter;

__IO voidFuncPtr  ButtonInt[numBUTTON ];

GPIO_TypeDef* GPIO_PORT[numLEDs] = {LED1_GPIO_PORT, LED2_GPIO_PORT, LED3_GPIO_PORT,
                                 LED4_GPIO_PORT};
const uint16_t GPIO_PIN[numLEDs] = {LED1_PIN, LED2_PIN, LED3_PIN,
                                 LED4_PIN};
const uint32_t GPIO_CLK[numLEDs] = {LED1_GPIO_CLK, LED2_GPIO_CLK, LED3_GPIO_CLK,
                                 LED4_GPIO_CLK};

GPIO_TypeDef* BUTTON_PORT[numBUTTON ] = {USER_BUTTON1_GPIO_PORT, USER_BUTTON3_GPIO_PORT,
								   USER_BUTTON4_GPIO_PORT};

const uint16_t BUTTON_PIN[numBUTTON ] = {USER_BUTTON1_PIN, USER_BUTTON3_PIN, USER_BUTTON4_PIN };

const uint32_t BUTTON_CLK[numBUTTON ] = {USER_BUTTON1_GPIO_CLK,USER_BUTTON3_GPIO_CLK,
									USER_BUTTON4_GPIO_CLK };

const uint16_t BUTTON_EXTI_LINE[numBUTTON ] = {USER_BUTTON1_EXTI_LINE,USER_BUTTON3_EXTI_LINE,
											USER_BUTTON4_EXTI_LINE};

const uint8_t BUTTON_PORT_SOURCE[numBUTTON ] = {USER_BUTTON1_EXTI_PORT_SOURCE,
						USER_BUTTON3_EXTI_PORT_SOURCE, USER_BUTTON4_EXTI_PORT_SOURCE};

const uint8_t BUTTON_PIN_SOURCE[numBUTTON ] = {USER_BUTTON1_EXTI_PIN_SOURCE,
						USER_BUTTON3_EXTI_PIN_SOURCE, USER_BUTTON4_EXTI_PIN_SOURCE};

const uint8_t BUTTON_IRQn[numBUTTON ] = {USER_BUTTON1_EXTI_IRQn, USER_BUTTON3_EXTI_IRQn,
										USER_BUTTON4_EXTI_IRQn};
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/**
  * @brief  Initializes Tibuboard LEDs and Buttons.
  * @param  None
  * @retval None
  */
Tibuboard::Tibuboard()
{
	GPIO_InitTypeDef  GPIO_InitStructure;
	uint8_t Button;
	uint8_t Led;

	for(Led=0;Led<numLEDs; Led++)
	{
		/* Enable the GPIO_LED Clock */
		RCC_AHB1PeriphClockCmd(GPIO_CLK[Led], ENABLE);

		/* Configure the GPIO_LED pin */
		GPIO_InitStructure.GPIO_Pin = GPIO_PIN[Led];
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
		GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
		GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_Init(GPIO_PORT[Led], &GPIO_InitStructure);
	}

	for(Button=0; Button<numBUTTON; Button++)
	{
		/* Enable the BUTTON Clock */
		RCC_AHB1PeriphClockCmd(BUTTON_CLK[Button], ENABLE);
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);

		/* Configure Button pin as input */
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
		GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
		GPIO_InitStructure.GPIO_Pin = BUTTON_PIN[Button];
		GPIO_Init(BUTTON_PORT[Button], &GPIO_InitStructure);
	}
}

/**
  * @brief  Tibuboard class destructor.
  * @param  None
  * @retval None
  */
Tibuboard::~Tibuboard()
{

}

/********************************************************************************************/
/******************                 LED FUNCTIONS          **********************************/
/********************************************************************************************/


/**
  * @brief  Turns selected LED On.
  * @param  Led: Specifies the Led to be set on. 
  *   This parameter can be one of following parameters:
  *     @arg LED1
  *     @arg LED2
  *     @arg LED3
  *     @arg LED4  
  * @retval None
  */
void Tibuboard::LEDOn(Led_TypeDef Led)
{
  GPIO_SetBits(GPIO_PORT[Led],GPIO_PIN[Led]);
}

/**
  * @brief  Turns selected LED Off.
  * @param  Led: Specifies the Led to be set off. 
  *   This parameter can be one of following parameters:
  *     @arg LED1
  *     @arg LED2
  *     @arg LED3
  *     @arg LED4 
  * @retval None
  */
void Tibuboard::LEDOff(Led_TypeDef Led)
{
  GPIO_ResetBits(GPIO_PORT[Led],GPIO_PIN[Led]); 
}

/**
  * @brief  Toggles the selected LED.
  * @param  Led: Specifies the Led to be toggled. 
  *   This parameter can be one of following parameters:
  *     @arg LED1
  *     @arg LED2
  *     @arg LED3
  *     @arg LED4  
  * @retval None
  */
void Tibuboard::LEDToggle(Led_TypeDef Led)
{
  GPIO_ToggleBits(GPIO_PORT[Led],GPIO_PIN[Led]); 
}

/**
  * @brief  Turns all LEDs On.
  * @param  None
  * @retval None
  */
void Tibuboard::LEDAllOn(void)
{
  uint8_t Led;
  
  for(Led=0;Led<numLEDs; Led++)
	GPIO_SetBits(GPIO_PORT[Led],GPIO_PIN[Led]);
  
}

/**
  * @brief  Turns all LEDs Off.
  * @param  None
  * @retval None
  */
void Tibuboard::LEDAllOff(void)
{
  uint8_t Led;
  
  for(Led=0;Led<numLEDs; Led++)
	GPIO_ResetBits(GPIO_PORT[Led],GPIO_PIN[Led]);
  
}

/**
  * @brief  Toggle all LEDs.
  * @param  None
  * @retval None
  */
void Tibuboard::LEDAllToggle(void)
{
  uint8_t Led;
  
  for(Led=0;Led<numLEDs; Led++)
	GPIO_ToggleBits(GPIO_PORT[Led],GPIO_PIN[Led]);
}

/********************************************************************************************/
/******************            PUSH BUTTON FUNCTIONS       **********************************/
/********************************************************************************************/



void Tibuboard::ButtonInterrupt(Button_TypeDef button, void (*userFunc)(void))
{
	 EXTI_InitTypeDef EXTI_InitStructure;
	 NVIC_InitTypeDef NVIC_InitStructure;

	 /* Connect Button EXTI Line to Button GPIO Pin */
	 RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);
     SYSCFG_EXTILineConfig(BUTTON_PORT_SOURCE[button], BUTTON_PIN_SOURCE[button]);

	/* Configure Button EXTI line */
	EXTI_InitStructure.EXTI_Line = BUTTON_EXTI_LINE[button];
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	EXTI_Init(&EXTI_InitStructure);

	/* Enable and set Button EXTI Interrupt to the lowest priority */
	NVIC_InitStructure.NVIC_IRQChannel = BUTTON_IRQn[button];
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x0F;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x0F;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;

	NVIC_Init(&NVIC_InitStructure);

	//ButtonInt[button]=userFunc;
	attachInterrupt(userFunc, EXTI_2);

}



/**
  * @brief  Returns the selected Button state.
  * @param  Button: Specifies the Button to be checked.
  *   This parameter should be:
  *   	USER_BUTTON1
  *   	USER_BUTTON2
  *   	USER_BUTTON3
  * @retval The Button GPIO pin value.
  */

uint8_t Tibuboard::GetStateButton(Button_TypeDef button)
{
	return GPIO_ReadInputDataBit(BUTTON_PORT[button], BUTTON_PIN[button]);
}



/********************************************************************************************/
/******************                INIT FUNCTIONS          **********************************/
/********************************************************************************************/

/**
  * @brief   This function initializes Systick configuration:
  * @param  None
  * @retval None
  */
void SysTickConfig(void)
{
  /* Setup SysTick Timer for 1ms interrupts  */
  if (SysTick_Config(SystemCoreClock / 100))
  {
    /* Capture error */
    while (1);
  }

  /* Configure the SysTick handler priority */
  NVIC_SetPriority(SysTick_IRQn, 0x0);
}


/********************************************************************************************/
/******************                ARDUINO FUNCTIONS          *********************************/
/********************************************************************************************/


void delay(uint32_t miliseconds)
{
	uint32_t start_time;

	start_time=Counter;
	while(Counter-start_time < miliseconds/10)
	{
		if(start_time>Counter)break;
	}
}

uint32_t millis(void)
{
	return Counter;
}
