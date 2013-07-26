/*
  ******************************************************************************
  * @file    BasicFunctions.c
  * @author  Javier Fernandez Cepeda
  * @version V0.0.1
  * @date    26-July-2013
  * @brief   This file contains functions descriptions which let program Tibuboard
  * 		 like an Arduino.
  ******************************************************************************
*/

/* Includes ------------------------------------------------------------------*/
#include "BasicFunctions.h"

/* Private typedef -----------------------------------------------------------*/


/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/

const uint16_t GPIOPIN_PIN[numPins] = {PIN0_PIN, PIN1_PIN, PIN2_PIN, PIN3_PIN, PIN4_PIN,
									PIN5_PIN, PIN6_PIN, PIN7_PIN, PIN8_PIN, PIN9_PIN,
									PIN10_PIN, PIN11_PIN, PIN12_PIN, PIN13_PIN,
									PINA0_PIN, PINA1_PIN, PINA2_PIN, PINA3_PIN,
									PINA4_PIN, PINA5_PIN};
GPIO_TypeDef* GPIOPIN_PORT[numPins] = {PIN0_GPIO_PORT, PIN1_GPIO_PORT, PIN2_GPIO_PORT,
									PIN3_GPIO_PORT, PIN4_GPIO_PORT, PIN5_GPIO_PORT,
									PIN6_GPIO_PORT, PIN7_GPIO_PORT, PIN8_GPIO_PORT,
									PIN9_GPIO_PORT, PIN10_GPIO_PORT, PIN11_GPIO_PORT,
									PIN12_GPIO_PORT, PIN13_GPIO_PORT,PINA0_GPIO_PORT,
									PINA1_GPIO_PORT, PINA2_GPIO_PORT, PINA3_GPIO_PORT,
									PINA4_GPIO_PORT, PINA5_GPIO_PORT};
const uint32_t GPIOPIN_CLK[numPins] = {PIN0_GPIO_CLK, PIN1_GPIO_CLK, PIN2_GPIO_CLK,
									PIN3_GPIO_CLK, PIN4_GPIO_CLK, PIN5_GPIO_CLK,
									PIN6_GPIO_CLK, PIN7_GPIO_CLK, PIN8_GPIO_CLK,
									PIN9_GPIO_CLK, PIN10_GPIO_CLK, PIN11_GPIO_CLK,
									PIN12_GPIO_CLK, PIN13_GPIO_CLK,PINA0_GPIO_CLK,
									PINA1_GPIO_CLK, PINA2_GPIO_CLK, PINA3_GPIO_CLK,
									PINA4_GPIO_CLK, PINA5_GPIO_CLK};

const uint32_t GPIO_SOURCE[numPins] = {PIN0_GPIO_SOURCE, PIN1_GPIO_SOURCE, PIN2_GPIO_SOURCE,
									PIN3_GPIO_SOURCE, PIN4_GPIO_SOURCE, PIN5_GPIO_SOURCE,
									PIN6_GPIO_SOURCE, PIN7_GPIO_SOURCE, PIN8_GPIO_SOURCE,
									PIN9_GPIO_SOURCE, PIN10_GPIO_SOURCE, PIN11_GPIO_SOURCE,
									PIN12_GPIO_SOURCE, PIN13_GPIO_SOURCE,PINA0_GPIO_SOURCE,
									PINA1_GPIO_SOURCE, PINA2_GPIO_SOURCE, PINA3_GPIO_SOURCE,
									PINA4_GPIO_SOURCE, PINA5_GPIO_SOURCE};



TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
TIM_OCInitTypeDef  TIM_OCInitStructure;


/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/********************************************************************************************/
/*****************                 DIGITAL PIN FUNCTIONS          ***************************/
/********************************************************************************************/

/**
  * @brief  Configures GPIO.
  * @param  pinNumber: Specifies the pin to be configured.
  * @param  Mode: Specifies the mode of the specified pin
  *   This parameter can be one of following parameters:
  *     @arg OUTPUT
  *     @arg INPUT
  *     @arg INPUT_PULLUP
  * @retval None
  */
void pinMode(uint32_t pinNumber, Mode_TypeDef Mode)
{
	 GPIO_InitTypeDef  GPIO_InitStructure;
	 /* Enable the GPIO_LED Clock */
	 RCC_AHB1PeriphClockCmd(GPIOPIN_CLK[pinNumber], ENABLE);

	 /* Configure the GPIO_LED pin */
	 GPIO_InitStructure.GPIO_Pin = GPIOPIN_PIN[pinNumber];
	 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;

	 if(pinNumber==PIN3_TIM4CHANNEL || pinNumber == PIN5_TIM4CHANNEL ||
				pinNumber == PIN6_TIM4CHANNEL || pinNumber == PIN9_TIM4CHANNEL)
	 {
		 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
		 GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
		 GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
		 GPIO_Init(GPIOPIN_PORT[pinNumber], &GPIO_InitStructure);

		 GPIO_PinAFConfig(GPIOPIN_PORT[pinNumber],GPIO_SOURCE[pinNumber], GPIO_AF_TIM4);

	 }

	 else
	 {
		 switch(Mode)
		 {
		 case OUTPUT:
			 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
			 GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
			 GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
			 break;

		 case INPUT:
			 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
			 GPIO_InitStructure.GPIO_OType = GPIO_OType_OD;
			 GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
			 break;

		 case INPUT_PULLUP:
			 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
			 GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
			 GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
			 break;
		 default:
			 break;
		 }
		 GPIO_Init(GPIOPIN_PORT[pinNumber], &GPIO_InitStructure);
	 }

}


/**
  * @brief  Puts selected Output Pin HIGH or LOW.
  * @param  pinNumber: Specifies the pin to be configured.
  * @param  State: Specifies the state of the specified pin
  *   This parameter can be one of following parameters:
  *     @arg HIGH
  *     @arg LOW
  * @retval None
  */
void digitalWrite(uint32_t pinNumber, Mode_OuputState State)
{
	if(pinNumber==PIN3_TIM4CHANNEL || pinNumber == PIN5_TIM4CHANNEL ||
			pinNumber == PIN6_TIM4CHANNEL || pinNumber == PIN9_TIM4CHANNEL)
	{
		switch(pinNumber)
		{
		case PIN3_TIM4CHANNEL:
			if(State == HIGH)TIM4->CCR1=MAXPWMPERIOD;
						else TIM4->CCR1=0;
			break;
		case PIN5_TIM4CHANNEL:
			if(State == HIGH)TIM4->CCR2=MAXPWMPERIOD;
						else TIM4->CCR2=0;
			break;
		case PIN6_TIM4CHANNEL:
			if(State == HIGH)TIM4->CCR3=MAXPWMPERIOD;
						else TIM4->CCR3=0;
			break;
		case PIN9_TIM4CHANNEL:
			if(State == HIGH)TIM4->CCR4=MAXPWMPERIOD;
						else TIM4->CCR4=0;
			break;

		}

	}
	else
	{
		if(State == HIGH)
			GPIO_SetBits(GPIOPIN_PORT[pinNumber],GPIOPIN_PIN[pinNumber]);
		else
			GPIO_ResetBits(GPIOPIN_PORT[pinNumber],GPIOPIN_PIN[pinNumber]);
	}

}

/**
  * @brief  Returns the selected pin state.
  * @param  pinNumber: Specifies the pin to be read.
  * @retval The GPIO pin value.
  */
uint32_t digitalRead(uint32_t pinNumber)
{
	return GPIO_ReadInputDataBit(GPIOPIN_PORT[pinNumber], GPIOPIN_PIN[pinNumber]);
}

/**
  * @brief  Set PWM on the specified pin.
  * @param  pinNumber: Specifies the pin to be configured.
  * @param  pwm: a value between 0 and 65535.
  * @retval None.
  */
void analogWrite(uint32_t pinNumber, uint32_t pwm)
{
	if(pinNumber==PIN3_TIM4CHANNEL || pinNumber == PIN5_TIM4CHANNEL ||
				pinNumber == PIN6_TIM4CHANNEL || pinNumber == PIN9_TIM4CHANNEL)
	{
		switch(pinNumber)
		{
		case PIN3_TIM4CHANNEL:
			TIM4->CCR1=pwm;
			break;

		case PIN5_TIM4CHANNEL:
			TIM4->CCR2=pwm;
			break;

		case PIN6_TIM4CHANNEL:
			TIM4->CCR3=pwm;
			break;

		case PIN9_TIM4CHANNEL:
			TIM4->CCR4=pwm;
			break;

		}
	}
}


/********************************************************************************************/
/*******************            ANALOG PIN FUNCTIONS       **********************************/
/********************************************************************************************/

/**
  * @brief  Returns the selected pin state.
  * @param  pinNumber: Specifies the pin to be read.
  * @retval The GPIO pin value.
  */
void analogReference(Button_TypeDef Button)
{
 /* TODO*/
}


/**
  * @brief  Returns the selected pin state.
  * @param  pinNumber: Specifies the pin to be read.
  * @retval The GPIO pin value.
  */
uint32_t analogRead(uint32_t pinNumber)
{
	//TODO
	return 0;
}



/********************************************************************************************/
/******************                INIT FUNCTIONS          **********************************/
/********************************************************************************************/

/* TODO Function that initializes ADC */

/**
  * @brief  Initialize PWM Pins.
  * @param  None.
  * @retval None.
  */
void Init_PWMPins()
{
	//TIM4 clock enable
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);


	/* Time base configuration */
	TIM_TimeBaseStructure.TIM_Period = 65535;
	TIM_TimeBaseStructure.TIM_Prescaler = 0;
	TIM_TimeBaseStructure.TIM_ClockDivision = 0;
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;

	TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure);

	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;

	/* Output Compare Timing Mode configuration: Channel1 */
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCInitStructure.TIM_Pulse = 0;

	TIM_OC1Init(TIM4, &TIM_OCInitStructure);

	TIM_OC1PreloadConfig(TIM4, TIM_OCPreload_Enable);

	/* Output Compare Timing Mode configuration: Channel2 */
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCInitStructure.TIM_Pulse = 0;

	TIM_OC2Init(TIM4, &TIM_OCInitStructure);

	TIM_OC2PreloadConfig(TIM4, TIM_OCPreload_Enable);

	/* Output Compare Timing Mode configuration: Channel3 */
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCInitStructure.TIM_Pulse = 0;

	TIM_OC3Init(TIM4, &TIM_OCInitStructure);

	TIM_OC3PreloadConfig(TIM4, TIM_OCPreload_Enable);

	/* Output Compare Timing Mode configuration: Channel4 */
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCInitStructure.TIM_Pulse = 0;

	TIM_OC4Init(TIM4, &TIM_OCInitStructure);

	TIM_OC4PreloadConfig(TIM4, TIM_OCPreload_Enable);


	TIM_ARRPreloadConfig(TIM4,ENABLE);

	TIM_Cmd(TIM4,ENABLE);

}
