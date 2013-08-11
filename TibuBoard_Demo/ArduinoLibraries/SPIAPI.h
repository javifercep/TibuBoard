/*
  ******************************************************************************
  * @file    SPIAPI.h
  * @author  Javier Fernandez Cepeda
  * @version V0.0.1
  * @date    05-August-2013
  * @brief   This file contains constants definitions which help users develop
  * 		 with SPI3.
  ******************************************************************************
*/

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __SPIAPI_H
#define __SPIAPI_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx.h"
#include "stm32f4xx_conf.h"

 /* Exported define ------------------------------------------------------------*/

 /* SPIx Communication boards Interface */

 #define SPI3_SCK_PIN                   GPIO_Pin_10
 #define SPI3_SCK_GPIO_PORT             GPIOC
 #define SPI3_SCK_GPIO_CLK              RCC_AHB1Periph_GPIOC
 #define SPI3_SCK_SOURCE                GPIO_PinSource10
 #define SPI3_SCK_AF                    GPIO_AF_SPI3

 #define SPI3_MISO_PIN                  GPIO_Pin_11
 #define SPI3_MISO_GPIO_PORT            GPIOC
 #define SPI3_MISO_GPIO_CLK             RCC_AHB1Periph_GPIOC
 #define SPI3_MISO_SOURCE               GPIO_PinSource11
 #define SPI3_MISO_AF                   GPIO_AF_SPI3

 #define SPI3_MOSI_PIN                  GPIO_Pin_12
 #define SPI3_MOSI_GPIO_PORT            GPIOC
 #define SPI3_MOSI_GPIO_CLK             RCC_AHB1Periph_GPIOC
 #define SPI3_MOSI_SOURCE               GPIO_PinSource12
 #define SPI3_MOSI_AF                   GPIO_AF_SPI3


/* Exported types ------------------------------------------------------------*/

/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */

void SPI_begin(void);
void SPI_end(void);
void SPI_setBitOrder(uint16_t bitOrder);
void SPI_setClockDivider(uint16_t Preescaler);
void SPI_setDataMode(uint16_t CPOL ,uint16_t CPHA);
uint16_t SPI_transfer(uint16_t data);



#ifdef __cplusplus
}
#endif

#endif /* __SPIAPI_H */
