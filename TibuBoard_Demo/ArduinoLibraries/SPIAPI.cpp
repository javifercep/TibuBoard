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
__IO voidFuncPtr intSPIFunc;

SPIClass SPI;
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/*Constructors*/
SPIClass::SPIClass()
{
	mastermode = SPI_MASTER;
	bitOrder   = SPI_FirstBit_MSB;
	dataMode	 = SPI_MODE0;
	prescaler = SPI_BaudRatePrescaler_16;;
}

SPIClass::~SPIClass()
{
	//Nothing
}

/**
  * @brief  This function attaches SPI interrupt:
  * @param  userFunc: SPI interrupt function
  * @retval None
  */
void SPIClass::attachInterrupt(void (*userFunc)(void))
{

}

/**
  * @brief   This function detaches SPI interrupt:
  * @param  None
  * @retval None
  */
void SPIClass::detachInterrupt(void)
{

}


 /**
   * @brief   This function initializes SPI configuration:
   * 			- Master
   * 			- Bidirectional
   * 			- Baud rate: ?¿
   * 			- Data size: 8b MSB
   * @param  None
   * @retval None
   */
 void SPIClass::begin(uint8_t mode)
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
 	  /*set private class variables*/
 	  mastermode = mode;
 	  bitOrder   = SPI_FirstBit_MSB;
 	  dataMode	 = SPI_MODE0;
 	  prescaler = SPI_BaudRatePrescaler_16;

 	  SPI_I2S_DeInit(SPI3);
 	  SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
 	  SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;
 	  SPI_InitStructure.SPI_CPOL = SPI_CPOL_Low;
 	  SPI_InitStructure.SPI_CPHA = SPI_CPHA_1Edge;
 	  SPI_InitStructure.SPI_NSS = SPI_NSS_Hard;
 	  SPI_InitStructure.SPI_BaudRatePrescaler = prescaler;
 	  SPI_InitStructure.SPI_FirstBit = bitOrder;
 	  SPI_InitStructure.SPI_CRCPolynomial = 0;

 	  /* Initializes the SPI communication */
 	  if(mode == SPI_MASTER)
 		  SPI_InitStructure.SPI_Mode = SPI_Mode_Master;
 	  if(mode == SPI_SLAVE)
 		 SPI_InitStructure.SPI_Mode = SPI_Mode_Slave;

 	  SPI_Init(SPI3, &SPI_InitStructure);

 	  /* Enable the SPI peripheral */
 	  SPI_Cmd(SPI3, ENABLE);

 }

 /**
   * @brief  This function disables SPI bus
   * @param  None
   * @retval None
   */
 void SPIClass::end(void)
 {
	SPI_Cmd(SPI3, DISABLE);
 }

 /**
   * @brief  This function configures SPI bit Order
   * @param  bitOrder: SPI_FirstBit_MSB or SPI_FirstBit_LSB
   * @retval None
   */
 void SPIClass::setBitOrder(uint16_t bitOrder)
 {
	SPI_InitTypeDef  SPI_InitStructure;

	this->bitOrder = bitOrder;
	SPI_Cmd(SPI3, DISABLE);
	SPI_I2S_DeInit(SPI3);
	SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
	SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;
	switch(dataMode)
	{
		case SPI_MODE0:
			SPI_InitStructure.SPI_CPOL = SPI_CPOL_Low;
			SPI_InitStructure.SPI_CPHA = SPI_CPHA_1Edge;
			break;
		case SPI_MODE1:
			SPI_InitStructure.SPI_CPOL = SPI_CPOL_Low;
			SPI_InitStructure.SPI_CPHA = SPI_CPHA_2Edge;
			break;
		case SPI_MODE2:
			SPI_InitStructure.SPI_CPOL = SPI_CPOL_High;
			SPI_InitStructure.SPI_CPHA = SPI_CPHA_1Edge;
			break;
		case SPI_MODE3:
			SPI_InitStructure.SPI_CPOL = SPI_CPOL_High;
			SPI_InitStructure.SPI_CPHA = SPI_CPHA_2Edge;
			break;
	}

	SPI_InitStructure.SPI_NSS = SPI_NSS_Hard;
	SPI_InitStructure.SPI_BaudRatePrescaler = prescaler;
	SPI_InitStructure.SPI_FirstBit = bitOrder;
	SPI_InitStructure.SPI_CRCPolynomial = 0;

	/* Initializes the SPI communication */
	if(mastermode == SPI_MASTER)
		SPI_InitStructure.SPI_Mode = SPI_Mode_Master;
	if(mastermode == SPI_SLAVE)
		SPI_InitStructure.SPI_Mode = SPI_Mode_Slave;

	SPI_Init(SPI3, &SPI_InitStructure);

	/* Enable the SPI peripheral */
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
 void SPIClass::setClockDivider(uint16_t Prescaler)
 {
	SPI_InitTypeDef  SPI_InitStructure;

	prescaler=Prescaler;
	SPI_Cmd(SPI3, DISABLE);
	SPI_I2S_DeInit(SPI3);
	SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
	SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;
	switch(dataMode)
	{
		case SPI_MODE0:
			SPI_InitStructure.SPI_CPOL = SPI_CPOL_Low;
			SPI_InitStructure.SPI_CPHA = SPI_CPHA_1Edge;
			break;
		case SPI_MODE1:
			SPI_InitStructure.SPI_CPOL = SPI_CPOL_Low;
			SPI_InitStructure.SPI_CPHA = SPI_CPHA_2Edge;
			break;
		case SPI_MODE2:
			SPI_InitStructure.SPI_CPOL = SPI_CPOL_High;
			SPI_InitStructure.SPI_CPHA = SPI_CPHA_1Edge;
			break;
		case SPI_MODE3:
			SPI_InitStructure.SPI_CPOL = SPI_CPOL_High;
			SPI_InitStructure.SPI_CPHA = SPI_CPHA_2Edge;
			break;
	}

	SPI_InitStructure.SPI_NSS = SPI_NSS_Hard;
	SPI_InitStructure.SPI_BaudRatePrescaler = prescaler;
	SPI_InitStructure.SPI_FirstBit = bitOrder;
	SPI_InitStructure.SPI_CRCPolynomial = 0;

	/* Initializes the SPI communication */
	if(mastermode == SPI_MASTER)
		SPI_InitStructure.SPI_Mode = SPI_Mode_Master;
	if(mastermode == SPI_SLAVE)
		SPI_InitStructure.SPI_Mode = SPI_Mode_Slave;

	SPI_Init(SPI3, &SPI_InitStructure);

	/* Enable the SPI peripheral */
	SPI_Cmd(SPI3, ENABLE);

 }

 /**
   * @brief  This function configures SPI Mode
   * @param  CPOL: SPI_CPOL_Low or SPI_CPOL_High
   * @param  CPHA: SPI_CPHA_1Edge or SPI_CPHA_2Edge
   * @retval None
   */
 void SPIClass::setDataMode(uint16_t SPImode)
 {
	SPI_InitTypeDef  SPI_InitStructure;

	dataMode = SPImode;
	SPI_Cmd(SPI3, DISABLE);
	SPI_I2S_DeInit(SPI3);
	SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
	SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;
	switch(dataMode)
	{
		case SPI_MODE0:
			SPI_InitStructure.SPI_CPOL = SPI_CPOL_Low;
			SPI_InitStructure.SPI_CPHA = SPI_CPHA_1Edge;
			break;
		case SPI_MODE1:
			SPI_InitStructure.SPI_CPOL = SPI_CPOL_Low;
			SPI_InitStructure.SPI_CPHA = SPI_CPHA_2Edge;
			break;
		case SPI_MODE2:
			SPI_InitStructure.SPI_CPOL = SPI_CPOL_High;
			SPI_InitStructure.SPI_CPHA = SPI_CPHA_1Edge;
			break;
		case SPI_MODE3:
			SPI_InitStructure.SPI_CPOL = SPI_CPOL_High;
			SPI_InitStructure.SPI_CPHA = SPI_CPHA_2Edge;
			break;
	}

	SPI_InitStructure.SPI_NSS = SPI_NSS_Hard;
	SPI_InitStructure.SPI_BaudRatePrescaler = prescaler;
	SPI_InitStructure.SPI_FirstBit = bitOrder;
	SPI_InitStructure.SPI_CRCPolynomial = 0;

	/* Initializes the SPI communication */
	if(mastermode == SPI_MASTER)
		SPI_InitStructure.SPI_Mode = SPI_Mode_Master;
	if(mastermode == SPI_SLAVE)
		SPI_InitStructure.SPI_Mode = SPI_Mode_Slave;

	SPI_Init(SPI3, &SPI_InitStructure);

	/* Enable the SPI peripheral */
	SPI_Cmd(SPI3, ENABLE);

 }

 /**
    * @brief  This function sends data through SPI BUS
    * @param  data to send
    * @retval data received from slave
    */
  uint16_t SPIClass::transfer(uint16_t data)
  {

	  if(mastermode == SPI_MASTER)
	  {
		  while(SPI_I2S_GetFlagStatus(SPI3, SPI_I2S_FLAG_TXE) == RESET);

		  SPI_I2S_SendData(SPI3, data);

		  while(SPI_I2S_GetFlagStatus(SPI3, SPI_I2S_FLAG_RXNE) == RESET);

		  return  SPI_I2S_ReceiveData(SPI3);
	  }
	  else
	  {
		  while(SPI_I2S_GetFlagStatus(SPI3, SPI_I2S_FLAG_RXNE) == RESET);

		  uint16_t data = SPI_I2S_ReceiveData(SPI3);

		  while(SPI_I2S_GetFlagStatus(SPI3, SPI_I2S_FLAG_TXE) == RESET);

		  SPI_I2S_SendData(SPI3, data);

		  return data;
	  }

  }



