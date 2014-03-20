/*
  ******************************************************************************
  * @file    BufferFunctions.c
  * @author  Javier Fernández Cepeda
  * @version V0.1.7
  * @date    21-August-2013
  * @brief   This file contains general functions descriptions.
  ******************************************************************************
*/

/* Includes ------------------------------------------------------------------*/
#include "BufferFunctions.h"


/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/


/**************************************************************************************************/
/*************************            FRAMES BUFFER          ************************************/
/**************************************************************************************************/

/**
  * @brief  Initializes frames buffer.
  * @param  pBuffer: pointer on the frames buffer
  * @param  BufferLength: size of the frames buffer
  * @param  FrameContainerSize: Size of the frame container
  * @retval None
  */
void Init_FBuffer(__IO FramesBuffer *pBuffer, uint32_t BufferLength)
{
	pBuffer->size=BufferLength;
	pBuffer->start=0;
	pBuffer->count=0;
	pBuffer->DataC = (FrameContainer*)malloc(BufferLength*sizeof(FrameContainer));
}


/**
  * @brief  Frees memory.
  * @param  pBuffer: pointer on the frames buffer
  * @retval None
  */
void Free_FBuffer(__IO FramesBuffer *pBuffer)
{
	free(pBuffer->DataC);
}

/**
  * @brief  Checks if frames buffer is full.
  * @param  pBuffer: pointer on the frames buffer
  * @retval 0x01 -> FULL or 0x00 if not
  */
uint8_t FBufferisFull(__IO FramesBuffer *pBuffer)
{
	return (pBuffer->count == pBuffer->size);
}

/**
  * @brief  Checks if frames buffer is empty.
  * @param  pBuffer: pointer on the frames buffer
  * @retval 0x01 -> EMPTY or 0x00 if not
  */
uint8_t FBufferisEmpty(__IO FramesBuffer *pBuffer)
{
	return (pBuffer->count == 0);
}

/**
  * @brief  Reads first Buffer's position.
  * @param  pBuffer: pointer on the frames buffer
  * @param  pContainer: pointer on frame vector (not Struct)
  * @param	bufferSize: size of frame vector
  * @retval None
  */
void Read_FBuffer(__IO FramesBuffer *pBuffer, __IO uint8_t *pContainer, uint8_t bufferSize)
{
	uint32_t ii;

	for(ii=0; ii<bufferSize; ii++)
		pContainer[ii]=Read_Container(&(pBuffer->DataC[pBuffer->start]));
	/*Frees memory reserved during write function*/
	Free_Container(&(pBuffer->DataC[pBuffer->start]));
	pBuffer->start=(pBuffer->start + 1) % pBuffer->size; //update start pointer
	pBuffer->count--;									 //Update data count

}

/**
  * @brief  Writes in the last position of frames buffer.
  * @param  pBuffer: pointer on the frames buffer
  * @param  pContainer: pointer on frame vector (not Struct)
  * @param	bufferSize: size of frame vector
  * @retval None
  */
void Write_FBuffer(__IO FramesBuffer *pBuffer, __IO uint8_t *pContainer, __IO uint8_t bufferSize)
{
	uint8_t ii;
	int end = (pBuffer->start + pBuffer->count) % pBuffer->size;

	/*Reserves memory to save pContainer vector*/
	Init_Container(&(pBuffer->DataC[end]),bufferSize);

	for(ii = 0; ii < bufferSize; ii++)
		Write_Container(&(pBuffer->DataC[end]),pContainer[ii]);
	/*OVERWRITE SUPPORTED*/
	if(pBuffer->count == pBuffer->size)
		pBuffer->start=(pBuffer->start + 1) % pBuffer->size;
	else
		pBuffer->count++;

}

/**
  * @brief  Reads first Buffer's position to FrameContainer (Struct).
  * @param  pBuffer: pointer on the frames buffer
  * @param  pContainer: pointer on frame container
  * @retval None
  */
void Read_FBufferToContainer(__IO FramesBuffer *pBuffer, __IO FrameContainer *pContainer)
{
	uint32_t ii;

	for(ii=0; ii<pBuffer->DataC[pBuffer->start].size; ii++)
		Write_Container(pContainer, Read_Container(&(pBuffer->DataC[pBuffer->start])));
	/*Frees memory reserved during write function*/
	Free_Container(&(pBuffer->DataC[pBuffer->start]));
	pBuffer->start=(pBuffer->start + 1) % pBuffer->size; //update start pointer
	pBuffer->count--;									 //Update data count

}

/**
  * @brief  Writes in the last position of circular buffer from a FrameContainer(Struct).
  * @param  pBuffer: pointer on the frames buffer
  * @param  pContainer: pointer on frame container
  * @retval None
  */
void Write_FBufferFromContainer(__IO FramesBuffer *pBuffer, __IO FrameContainer *pContainer)
{
	uint8_t ii;
	int end = (pBuffer->start + pBuffer->count) % pBuffer->size;

	if(pContainer->size <= pBuffer->DataC[end].size)
	{
		/*Reserves memory to save pContainer vector*/
		Init_Container(&(pBuffer->DataC[end]),pContainer->size);


		for(ii = 0; ii < pContainer->size; ii++)
			Write_Container(&(pBuffer->DataC[end]),Read_Container(pContainer));

		/*OVERWRITE SUPPORTED*/
		if(pBuffer->count == pBuffer->size)
			pBuffer->start=(pBuffer->start + 1) % pBuffer->size;
		else
			pBuffer->count++;
	}

}

/**
  * @brief  Writes in the last position of frames buffer more than one FrameContainer (Struct).
  * @param  pBuffer: pointer on the circular buffer
  * @param  pContainer: pointer on frame container
  * @param  datalength: number of FrameContainers to write
  * @retval None
  */
void Write_DataFBuffer(__IO FramesBuffer *pBuffer, __IO FrameContainer *pContainer, uint8_t datalength)
{
	uint8_t i;

	for(i=0; i<datalength; i++)
	{
		if(FBufferisFull(pBuffer)!=FBuf_FULL)
			Write_FBufferFromContainer(pBuffer,pContainer);
		else
			break;
	}
}

/**
  * @brief  Returns how much data there are in the frames buffer.
  * @param  pBuffer: pointer on the frames buffer
  * @retval number of data in FramesBuffer
  */
uint8_t numDatainFBuffer(__IO FramesBuffer *pBuffer)
{
	return pBuffer->count;
}

/**
  * @brief  Returns the position of the new data to write.
  * @param  pBuffer: pointer on the frames buffer
  * @retval last available position
  */
uint8_t getEndPosition(__IO FramesBuffer *pBuffer)
{
	return ((pBuffer->start + pBuffer->count) % pBuffer->size);
}


/**************************************************************************************************/
/*************************            FRAME CONTAINER          ************************************/
/**************************************************************************************************/

/**
  * @brief  Initializes frame container.
  * @param  pContainer: pointer on the frame Container
  * @param  ContainerLength: size of the frame Container
  * @retval None
  */
void Init_Container(__IO FrameContainer *pContainer, uint32_t ContainerLength)
{
	pContainer->size=ContainerLength;
	pContainer->count=0;
	pContainer->start=0;
	pContainer->Data = (uint8_t*)malloc(sizeof(uint8_t)*ContainerLength);

}


/**
  * @brief  Frees memory.
  * @@param pContainer: pointer on the frame Container
  * @retval None
  */
void Free_Container(__IO FrameContainer *pContainer)
{
	free(pContainer->Data);
}

/**
  * @brief  Checks if frame Container is full.
  * @param  pContainer: pointer on the frame Container
  * @retval 0x01 -> FULL or 0x00 if not
  */
uint8_t ContainerisFull(__IO FrameContainer *pContainer)
{
	return (pContainer->count == pContainer->size);
}

/**
  * @brief  Checks if frame Container is empty.
  * @param  pContainer: pointer on the frame Container
  * @retval 0x01 -> EMPTY or 0x00 if not
  */
uint8_t ContainerisEmpty(__IO FrameContainer *pContainer)
{
	return (pContainer->count == 0);
}

/**
  * @brief  Reads first Container's position.
  * @param  pContainer: pointer on the frame Container
  * @retval data
  */
uint8_t Read_Container(__IO FrameContainer *pContainer)
{
	uint8_t temp;

	temp=pContainer->Data[pContainer->start]; 				 //get oldest data in the Container
	pContainer->start=(pContainer->start + 1) % pContainer->size; //update start pointer
	pContainer->count--; 									 //Update data count

	return temp;
}

/**
  * @brief  Reads first Container's position.
  * @param  pContainer: pointer on the frame Container
  * @retval data
  */
uint32_t Read_ContainertoBuffer(__IO FrameContainer *pContainer, uint8_t *buff )
{
	uint8_t size;


	size = pContainer->count;
	while(ContainerisEmpty(pContainer) != FC_EMPTY )
		buff[size-pContainer->count] = Read_Container(pContainer);
	return size;
}

/**
  * @brief  Reads first Container's position.
  * @param  pContainer: pointer on the frame Container
  * @retval data
  */
uint8_t Read_ContainertoInt(__IO FrameContainer *pContainer, uint32_t data )
{
	uint8_t ii;

	if(pContainer->count < 4) return 0;
	for(ii=0; ii<4; ii++)
	{
		data |= (Read_Container(pContainer)) << (8*(3-ii));

	}
	return 1;
}

/**
  * @brief  Writes in the last position of frame Container.
  * @param  @param  pContainer: pointer on the frame Container
  * @param  command: data to frame Container
  * @retval None
  */
void Write_Container(__IO FrameContainer *pContainer, uint8_t command)
{
	int end = (pContainer->start + pContainer->count) % pContainer->size;
	pContainer->Data[end]=command;
	/*OVERWRITE SUPPORTED*/
	if(pContainer->count == pContainer->size)
		pContainer->start=(pContainer->start + 1) % pContainer->size;
	else
		pContainer->count++;

}

/**
  * @brief  Writes in the last position of frame Container more than single data at once.
  * @param  pContainer: pointer on the frame Container
  * @param  data: vector data to frame Container
  * @param  datalength: size of data vector
  */
void Write_DataContainer(__IO FrameContainer *pContainer, __IO uint8_t *data, uint8_t datalength)
{
	uint8_t i;

		for(i=0; i<datalength; i++)
		{
			if(ContainerisFull(pContainer)!=FC_FULL)
				Write_Container(pContainer,data[i]);
			else
				break;
		}
}

/**
  * @brief  Writes in the last position of frame Container more than single data at once.
  * @param  pContainer: pointer on the frame Container
  * @param  data: integer to write on container
  * @retval None
  */
void Write_IntContainer(__IO FrameContainer *pContainer, uint32_t data)
{
	uint8_t i;

		for(i=0; i<4; i++)
		{
			if(ContainerisFull(pContainer)!=FC_FULL)
				Write_Container(pContainer,((data >> 8*(3-i))&0xFF));
			else
				break;
		}
}

/**
  * @brief  Returns how much data there are in the Container.
  * @param  pContainer: pointer on the Container
  * @retval size of data in container
  */
uint8_t numDatainContainer(__IO FrameContainer *pContainer)
{
	return pContainer->count;
}
