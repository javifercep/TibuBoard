/*
  ******************************************************************************
  * @file    InterruptManager.h
  * @author  Javier Fernandez Cepeda
  * @brief   Management of Interrupt callbacks and ISR services.
  ******************************************************************************
*/

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __INTERRUPTMANAGER_H
#define __INTERRUPTMANAGER_H

#ifdef __cplusplus
 extern "C" {
#endif

 /* Includes ------------------------------------------------------------------*/
#include "stm32f4xx.h"
 /* Exported types ------------------------------------------------------------*/

 typedef struct
 {
	void (*userFunc)(void);
 }ISR_Callback;

 typedef struct
 {
	 uint16_t InstanceCounter;
	 uint16_t MaxInstances;
	 ISR_Callback *Callbacks;
 }PeriphInstance;

 /* Hardware dependent defines & types */

 typedef enum
  {
 	 TIMER_1 = 0,
 	 TIMER_2,
 	 SPI_1,
 	 EXTI_2
  }Peripheral_Instances;

 /* Exported constants --------------------------------------------------------*/
#define NUMBER_PERIPHERALS	4
#define INSTANCE_ISR 		uint16_t

 /* Exported macro ------------------------------------------------------------*/
#define CURRENT_PERIPH_INSTANCES(Instance)		Periph_ISR[Instance].InstanceCounter
#define MAX_PERIPH_INSTANCES(Instace)			Periph_ISR[Instance].MaxInstances
#define ADD_CALLBACK_INSTANCE(AppFunc)			Periph_ISR[Instance].Callbacks[Periph_ISR[Instance].InstanceCounter].userFunc = AppFunc
#define REMOVE_CALLBACK_INSTANCE(Instance)		Periph_ISR[Instance].Callbacks[Periph_ISR[Instance].InstanceCounter].userFunc = 0
#define CALL_CALLBACK_INSTANCE(Instance, Id)	Periph_ISR[Instance].Callbacks[Id].userFunc
#define ADD_PERIPH_CB(Instance, periph)			Periph_ISR[Instance].Callbacks = CB_##periph

#define CREATE_PERIPH_INSTANCE(size)			volatile PeriphInstance Periph_ISR[size]
#define ADD_PERIPH_INSTANCE(Instance, size)		ISR_Callback	CB_##Instance[size]

 /* Exported functions ------------------------------------------------------- */
void InitInterruptManager(void);
void attachInterrupt(void (*userFunc)(void), INSTANCE_ISR Instance);
void dettachInterrupt(void (*userFunc)(void), INSTANCE_ISR Instance);


#ifdef __cplusplus
}
#endif

#endif /* __INTERRUPTMANAGER_H */
