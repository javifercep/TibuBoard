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

/* Private typedef -----------------------------------------------------------*/


/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/

__IO uint32_t Counter = 0;

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


/********************************************************************************************/
/******************                 LED FUNCTIONS          **********************************/
/********************************************************************************************/

/**
  * @brief  Configures LED GPIO.
  * @param  Led: Specifies the Led to be configured. 
  *   This parameter can be one of following parameters:
  *     @arg LED1
  *     @arg LED2
  *     @arg LED3
  *     @arg LED4
  * @retval None
  */
void TibuBoard_InitLED(Led_TypeDef Led)
{
  GPIO_InitTypeDef  GPIO_InitStructure;
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
void TibuBoard_LEDOn(Led_TypeDef Led)
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
void TibuBoard_LEDOff(Led_TypeDef Led)
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
void TibuBoard_LEDToggle(Led_TypeDef Led)
{
  GPIO_ToggleBits(GPIO_PORT[Led],GPIO_PIN[Led]); 
}

/**
  * @brief  Configures all LEDs GPIO.
  * @param  None
  * @retval None
  */
void TibuBoard_InitAllLEDs(void)
{
  GPIO_InitTypeDef  GPIO_InitStructure;
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
}

/**
  * @brief  Turns all LEDs On.
  * @param  None
  * @retval None
  */
void TibuBoard_LEDOnAll(void)
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
void TibuBoard_LEDOffAll(void)
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
void TibuBoard_LEDToggleAll(void)
{
  uint8_t Led;
  
  for(Led=0;Led<numLEDs; Led++)
	GPIO_ToggleBits(GPIO_PORT[Led],GPIO_PIN[Led]);
}

/********************************************************************************************/
/******************            PUSH BUTTON FUNCTIONS       **********************************/
/********************************************************************************************/

void TibuBoard_InitPushButton(Button_TypeDef Button)
{
	 GPIO_InitTypeDef GPIO_InitStructure;

	 /* Enable the BUTTON Clock */
	 RCC_AHB1PeriphClockCmd(BUTTON_CLK[Button], ENABLE);

	  /* Configure Button pin as input */
	 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
	 GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	 GPIO_InitStructure.GPIO_Pin = BUTTON_PIN[Button];
	 GPIO_Init(BUTTON_PORT[Button], &GPIO_InitStructure);

}

void TibuBoard_attachButtonInterrupt(Button_TypeDef Button, void (*userFunc)(void))
{
	 EXTI_InitTypeDef EXTI_InitStructure;
	 NVIC_InitTypeDef NVIC_InitStructure;

	 /* Connect Button EXTI Line to Button GPIO Pin */
	 RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);
     SYSCFG_EXTILineConfig(BUTTON_PORT_SOURCE[Button], BUTTON_PIN_SOURCE[Button]);

	/* Configure Button EXTI line */
	EXTI_InitStructure.EXTI_Line = BUTTON_EXTI_LINE[Button];
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	EXTI_Init(&EXTI_InitStructure);

	/* Enable and set Button EXTI Interrupt to the lowest priority */
	NVIC_InitStructure.NVIC_IRQChannel = BUTTON_IRQn[Button];
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x0F;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x0F;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;

	NVIC_Init(&NVIC_InitStructure);

	ButtonInt[Button]=userFunc;

}

void TibuBoard_InitAllPushButton(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	uint8_t Button;

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
  * @brief  Returns the selected Button state.
  * @param  Button: Specifies the Button to be checked.
  *   This parameter should be:
  *   	USER_BUTTON1
  *   	USER_BUTTON2
  *   	USER_BUTTON3
  * @retval The Button GPIO pin value.
  */

uint32_t TibuBoard_GetStatePushButton(Button_TypeDef Button)
{
	return GPIO_ReadInputDataBit(BUTTON_PORT[Button], BUTTON_PIN[Button]);
}



/********************************************************************************************/
/******************                INIT FUNCTIONS          **********************************/
/********************************************************************************************/

/**
  * @brief  Initialices TibuBoard Structure.
  * @param  Tibu: contains TibuBoard Struct
  * @retval None
  */
void InitTibuBoard(TibuBoard *Tibu)
{
  Tibu->InitLED		 	=	TibuBoard_InitLED;
  Tibu->ToggleLED	 	=	TibuBoard_LEDToggle;
  Tibu->LEDOn		 	=	TibuBoard_LEDOn;
  Tibu->LEDOff		 	=	TibuBoard_LEDOff;
  Tibu->InitAllLED	 	=	TibuBoard_InitAllLEDs;
  Tibu->ToggleAllLED 	=	TibuBoard_LEDToggleAll;
  Tibu->AllLEDOn	 	=	TibuBoard_LEDOnAll;
  Tibu->AllLEDOff	 	=	TibuBoard_LEDOffAll;
  Tibu->InitButton	 	=	TibuBoard_InitPushButton;
  Tibu->ButtonInterrupt =	TibuBoard_attachButtonInterrupt;
  Tibu->InitAllButton	=	TibuBoard_InitAllPushButton;
  Tibu->GetStateButton	=	TibuBoard_GetStatePushButton;
}



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
