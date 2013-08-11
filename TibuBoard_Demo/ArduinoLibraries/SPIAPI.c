/*
  ******************************************************************************
  * @file    SPIAPI.c
  * @author  Javier Fernandez Cepeda
  * @version V0.0.1
  * @date    06-August-2013
  * @brief   This file contains functions descriptions which help users develop
  * 		 with SPI3.
  ******************************************************************************
*/

/* Includes ------------------------------------------------------------------*/
#include "SPIAPI.h"

/* Private typedef -----------------------------------------------------------*/

/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/


 /**
   * @brief   This function initializes SPI configuration:
   * 			- Master
   * 			- Bidirectional
   * 			- Baud rate: ?¿
   * 			- Data size: 8b MSB
   * @param  None
   * @retval None
   */
 void SPI_begin(void)
 {
 	GPIO_InitTypeDef GPIO_InitStructure;
 	SPI_InitTypeDef  SPI_InitStructure;


 	/* Peripheral Clock Enable -------------------------------------------------*/

 	  /* Enable the SPI clock */
      RCC_APB1PeriphClockCmd(RCC_APB1Periph_SPI3 ,ENABLE);

 	  /* Enable GPIO clocks */
 	  RCC_AHB1PeriphClockCmd(SPI3_SCK_GPIO_CLK | SPI3_MISO_GPIO_CLK | SPI3_MOSI_GPIO_CLK, ENABLE);

 	/* SPI GPIO Configuration --------------------------------------------------*/

 	  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
 	  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
 	  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
 	  GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_DOWN;

 	  /* SPI SCK pin configuration */
 	  GPIO_InitStructure.GPIO_Pin = SPI3_SCK_PIN;
 	  GPIO_Init(SPI3_SCK_GPIO_PORT, &GPIO_InitStructure);

 	  /* SPI  MOSI pin configuration */
 	  GPIO_InitStructure.GPIO_Pin =  SPI3_MOSI_PIN;
 	  GPIO_Init(SPI3_MOSI_GPIO_PORT, &GPIO_InitStructure);

 	  /* SPI  MISO pin configuration */
 	  GPIO_InitStructure.GPIO_Pin =  SPI3_MISO_PIN;
 	  GPIO_Init(SPI3_MISO_GPIO_PORT, &GPIO_InitStructure);

 	  /* Connect SPI pins to AF6 */
 	  GPIO_PinAFConfig(SPI3_SCK_GPIO_PORT,  SPI3_SCK_SOURCE,  SPI3_SCK_AF);
 	  GPIO_PinAFConfig(SPI3_MOSI_GPIO_PORT, SPI3_MOSI_SOURCE, SPI3_MOSI_AF);
 	  GPIO_PinAFConfig(SPI3_MISO_GPIO_PORT, SPI3_MISO_SOURCE, SPI3_MISO_AF);

 	/* SPI configuration -------------------------------------------------------*/
 	  SPI_I2S_DeInit(SPI3);
 	  SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
 	  SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;
 	  SPI_InitStructure.SPI_CPOL = SPI_CPOL_Low;
 	  SPI_InitStructure.SPI_CPHA = SPI_CPHA_1Edge;
 	  SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;
 	  SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_64;
 	  SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;
 	  SPI_InitStructure.SPI_CRCPolynomial = 7;

 	  /* Initializes the SPI communication */
 	  SPI_InitStructure.SPI_Mode = SPI_Mode_Master;
 	  SPI_Init(SPI3, &SPI_InitStructure);

 	  /* Enable the SPI peripheral */
 	  SPI_Cmd(SPI3, ENABLE);

 }

 /**
   * @brief  This function disables SPI bus
   * @param  None
   * @retval None
   */
 void SPI_end(void)
 {
	SPI_Cmd(SPI3, DISABLE);
 }

 /**
   * @brief  This function configures SPI bit Order
   * @param  bitOrder: SPI_FirstBit_MSB or SPI_FirstBit_LSB
   * @retval None
   */
 void SPI_setBitOrder(uint16_t bitOrder)
 {
	SPI_InitTypeDef  SPI_InitStructure;

	SPI_Cmd(SPI3, DISABLE);
	SPI_InitStructure.SPI_FirstBit = bitOrder;
	SPI_Init(SPI3, &SPI_InitStructure);
	SPI_Cmd(SPI3, ENABLE);

 }

 /**
   * @brief  This function configures SPI baud rate
   * @param Preescaler:
   * SPI_BaudRatePrescaler_2
   * SPI_BaudRatePrescaler_4
   * SPI_BaudRatePrescaler_8
   * SPI_BaudRatePrescaler_16
   * SPI_BaudRatePrescaler_32
   * SPI_BaudRatePrescaler_64
   * SPI_BaudRatePrescaler_128
   * SPI_BaudRatePrescaler_256
   * @retval None
   */
 void SPI_setClockDivider(uint16_t Preescaler)
 {
	SPI_InitTypeDef  SPI_InitStructure;

	SPI_Cmd(SPI3, DISABLE);
	SPI_InitStructure.SPI_BaudRatePrescaler = Preescaler;
	SPI_Init(SPI3, &SPI_InitStructure);
	SPI_Cmd(SPI3, ENABLE);

 }

 /**
   * @brief  This function configures SPI Mode
   * @param  CPOL: SPI_CPOL_Low or SPI_CPOL_High
   * @param  CPHA: SPI_CPHA_1Edge or SPI_CPHA_2Edge
   * @retval None
   */
 void SPI_setDataMode(uint16_t CPOL ,uint16_t CPHA)
 {
	SPI_InitTypeDef  SPI_InitStructure;

	SPI_Cmd(SPI3, DISABLE);
	SPI_InitStructure.SPI_CPOL = CPOL;
	SPI_InitStructure.SPI_CPHA = CPHA;
	SPI_Init(SPI3, &SPI_InitStructure);
	SPI_Cmd(SPI3, ENABLE);

 }

 /**
    * @brief  This function sends data through SPI BUS
    * @param  data to send
    * @retval data received from slave
    */
  uint16_t SPI_transfer(uint16_t data)
  {

	  while(SPI_I2S_GetFlagStatus(SPI3, SPI_I2S_FLAG_TXE) == RESET);

	  SPI_I2S_SendData(SPI3, data);

	  while(SPI_I2S_GetFlagStatus(SPI3, SPI_I2S_FLAG_RXNE) == RESET);

	  return  SPI_I2S_ReceiveData(SPI3);

  }



