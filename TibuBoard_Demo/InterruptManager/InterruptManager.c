/*
  ******************************************************************************
  * @file    InterruptManager.c
  * @author  Javier Fernandez Cepeda
  * @brief   Management of Interrupt callbacks and ISR services.
  ******************************************************************************
*/

/* Includes ------------------------------------------------------------------*/
#include "InterruptManager.h"

/* Private typedef -----------------------------------------------------------*/

/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
ADD_PERIPH_INSTANCE(Timer_1,1);
ADD_PERIPH_INSTANCE(Timer_2,1);
ADD_PERIPH_INSTANCE(Spi_1, 	1);
ADD_PERIPH_INSTANCE(Exti_2, 2);

CREATE_PERIPH_INSTANCE(NUMBER_PERIPHERALS)= {
/* Current Instances, Max Instantces, Callback array*/
{				0, 		1, 				CB_Timer_1},
{				0, 		1, 				CB_Timer_2},
{				0, 		1, 				CB_Spi_1},
{				0, 		1, 				CB_Exti_2}
};



/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/**
  * @brief  This function attaches an Interrupt to a peripheral Instance OTG_HS Handler.
  * @param  None
  * @retval None
  */
void InitInterruptManager(void)
{
	ADD_PERIPH_CB(TIMER_1, Timer_1);
	ADD_PERIPH_CB(TIMER_2, Timer_2);
	ADD_PERIPH_CB(SPI_1, Spi_1);
	ADD_PERIPH_CB(EXTI_2, Exti_2);
}

/**
  * @brief  This function attaches an Interrupt to a peripheral Instance.
  * @param  userFunc: pointer to application callback
  * 		Instance: peripheral Instance
  * @retval None
  */
 void attachInterrupt(void (*userFunc)(void), INSTANCE_ISR Instance)
 {
	 if(++CURRENT_PERIPH_INSTANCES(Instance) < MAX_PERIPH_INSTANCES(Instace))
	 {
		 ADD_CALLBACK_INSTANCE(userFunc);
	 }
 }

 /**
   * @brief  This function dettaches an Interrupt to a peripheral Instance.
   * @param  userFunc: pointer to application callback
   * 		Instance: peripheral Instance
   * @retval None
   */
 void dettachInterrupt(void (*userFunc)(void), INSTANCE_ISR Instance)
 {
	 uint16_t count;
	 for(count = 0; count < CURRENT_PERIPH_INSTANCES(Instance); count++)
	 {
		 if(CALL_CALLBACK_INSTANCE(Instance, count) == userFunc)
		 {
			 REMOVE_CALLBACK_INSTANCE(Instance);
			 CURRENT_PERIPH_INSTANCES(Instance)--;
		 }
	 }
 }
