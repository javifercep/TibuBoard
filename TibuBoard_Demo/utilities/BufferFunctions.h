/*
  ******************************************************************************
  * @file    BufferFunctions.h
  * @author  Javier Fernández Cepeda
  * @version V0.1.7
  * @date    21-August-2013
  * @brief   This file contains general functions descriptions.
  ******************************************************************************
*/

#ifndef BUFFERFUNCTIONS_H_
#define BUFFERFUNCTIONS_H_

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx.h"
#include "stm32f4xx_conf.h"
#include <malloc.h>
#include <stdlib.h>

 /* Exported define ------------------------------------------------------------*/
#define FBuf_EMPTY (uint8_t)0x01
#define FBuf_FULL  (uint8_t)0x01
#define FC_EMPTY	 (uint8_t)0x01
#define FC_FULL	 (uint8_t)0x01
 /* Exported types ------------------------------------------------------------*/
 typedef struct{
	 uint32_t size;
	 uint32_t count;
	 uint32_t start;
	 uint8_t *Data;
 }FrameContainer;

 typedef struct{
	 uint32_t size;
	 uint32_t start;
	 uint32_t count;
	 FrameContainer* DataC;
 }FramesBuffer;
 /* Exported constants --------------------------------------------------------*/

 /* Exported macro ------------------------------------------------------------*/
 /* Exported functions ------------------------------------------------------- */

/*Gets the number of packets sent*/
 uint8_t GetVar_NbrOfData(void);

/*Buffer frames Functions*/
 void Init_FBuffer(__IO FramesBuffer *pBuffer, uint32_t BufferLength);
 void Free_FBuffer(__IO FramesBuffer *pBuffer);
 uint8_t FBufferisFull(__IO FramesBuffer *pBuffer);
 uint8_t FBufferisEmpty(__IO FramesBuffer *pBuffer);
 void Read_FBuffer(__IO FramesBuffer *pBuffer, __IO uint8_t *pContainer, uint8_t bufferSize);
 void Write_FBuffer(__IO FramesBuffer *pBuffer, __IO uint8_t *pContainer, uint8_t bufferSize);
 void Read_FBufferToContainer(__IO FramesBuffer *pBuffer, __IO FrameContainer *pContainer);
 void Write_FBufferFromContainer(__IO FramesBuffer *pBuffer, __IO FrameContainer *pContainer);
 void Write_DataFBuffer(__IO FramesBuffer *pBuffer, __IO FrameContainer *pContainer, uint8_t datalength);
 uint8_t numDatainFBuffer(__IO FramesBuffer *pBuffer);
 uint8_t getEndPosition(__IO FramesBuffer *pBuffer);

 /*Container frames Fucntions*/
 void Init_Container(__IO FrameContainer *pContainer, uint32_t ContainerLength);
 void Free_Container(__IO FrameContainer *pContainer);
 uint8_t ContainerisFull(__IO FrameContainer *pContainer);
 uint8_t ContainerisEmpty(__IO FrameContainer *pContainer);
 uint8_t Read_Container(__IO FrameContainer *pContainer);
 uint32_t Read_ContainertoBuffer(__IO FrameContainer *pContainer, uint8_t *buf);
 uint8_t Read_ContainertoInt(__IO FrameContainer *pContainer, uint32_t data);
 void Write_Container(__IO FrameContainer *pContainer, uint8_t command);
 void Write_DataContainer(__IO FrameContainer *pContainer, __IO uint8_t *data, uint8_t datalength);
 void Write_IntContainer(__IO FrameContainer *pContainer, uint32_t data);
 uint8_t numDatainContainer(__IO FrameContainer *pContainer);


#ifdef __cplusplus
}
#endif

#endif /* GENERALFUNCTIONS_H_ */
