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


#define SPI_MODE0 0x00
#define SPI_MODE1 0x04
#define SPI_MODE2 0x08
#define SPI_MODE3 0x0C

#define SPI_MODE_MASK 0x0C  // CPOL = bit 3, CPHA = bit 2 on SPCR
#define SPI_CLOCK_MASK 0x03  // SPR1 = bit 1, SPR0 = bit 0 on SPCR
#define SPI_2XCLOCK_MASK 0x01  // SPI2X = bit 0 on SPSR

#define SPI_MASTER 0x00
#define SPI_SLAVE  0x01

 typedef void (*voidFuncPtr)(void);

/* Exported types ------------------------------------------------------------*/

/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */

class SPIClass {
private:
	 uint8_t mastermode;
	 uint16_t bitOrder;
	 uint16_t dataMode;
	 uint16_t prescaler;
public:
	 SPIClass();
	 ~SPIClass();
	 uint16_t  transfer(uint16_t data);
	 void attachInterrupt(void (*userFunc)(void));
	 void detachInterrupt(void); // Default

	 void begin(uint8_t); // Default
	 void end();

	 void setBitOrder(uint16_t);
	 void setDataMode(uint16_t);
	 void setClockDivider(uint16_t);

 };

extern SPIClass SPI;

/*void SPI_begin(void);
void SPI_end(void);
void SPI_setBitOrder(uint16_t bitOrder);
void SPI_setClockDivider(uint16_t Preescaler);
void SPI_setDataMode(uint16_t CPOL ,uint16_t CPHA);
uint16_t SPI_transfer(uint16_t data);*/



#ifdef __cplusplus
}
#endif

#endif /* __SPIAPI_H */
